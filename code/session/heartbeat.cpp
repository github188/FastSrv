/*
//
//	Last Modify Date: 2015-09-16
//	Author: zengpw
//	History:
//					2015-09-01 zengpw created
//	File Property: private
//	Future:
//					I. 心跳线程，报文基于 protobuf
//
//
*/

#include "heartbeat.h"

namespace session
{
	HeartBeatMsg* HeartBeatMsg::hbm = NULL;
	unsigned int HeartBeatMsg::ref = 0;
	pthread_mutex_t HeartBeatMsg::lock = PTHREAD_MUTEX_INITIALIZER;

	HeartBeatMsg* HeartBeatMsg::instance()
	{
		if(hbm == NULL)
		{
			hbm = new HeartBeatMsg;
		}

		ref++;
		return hbm;
	}


	void HeartBeatMsg::release()
	{
		if(ref > 0)
			ref--;
		else
			delete hbm;
	}


	node HeartBeatMsg::getSlave()
	{
		return this->n;
	}


	unsigned int HeartBeatMsg::getLoad()
	{
		return this->n.load;
	}


	void HeartBeatMsg::setLoad(unsigned int load)
	{
		pthread_mutex_lock(&this->lock);
		this->n.load = load;
		pthread_mutex_unlock(&this->lock);
	}


	void HeartBeatMsg::setSlave(node& n)
	{
		pthread_mutex_lock(&this->lock);
		this->n = n;
		pthread_mutex_unlock(&this->lock);
	}


	HeartBeat::HeartBeat(HeartBeatMsg* hbm)
	{
		this->hbm = hbm;
	}


	void* HeartBeat::master(void* self)
	{
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		HeartBeat* se = (HeartBeat*)self;

		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_LISTENER, NULL, se->port);
		conn->setReadCb(OnMasterReadCb);
		conn->extra = self;
		conn->run();

		google::protobuf::ShutdownProtobufLibrary();
	}


	void* HeartBeat::slave(void* self)
	{
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		HeartBeat* se = (HeartBeat*)self;

		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_CONNECTER, se->addr.c_str(), se->port);
		conn->setConnCb(OnSlaveConnCb);
		conn->setReadCb(OnSlaveReadCb);

		struct timeval tv;
		tv.tv_sec = se->interval;
		tv.tv_usec = 0;
		conn->setTiming(tv);
		conn->setTimingCb(OnSlaveTimingCb);
		conn->extra = self;

		while(true)
		{
			conn->run();
			printf("\n Heartbeat : Master not find. Slave sleep 5 Seconds. \n");
			sleep(5);
		}

		google::protobuf::ShutdownProtobufLibrary();
	}


	void HeartBeat::OnMasterReadCb(struct bufferevent *bev, void *conn)
	{
		printf("\n Heartbeat : OnMasterReadCb! \n");

		common::Conn* cn = (common::Conn*)conn;
		HeartBeat* se = (HeartBeat*)cn->extra;
		protocol::pb::PacketPB *in = new protocol::pb::PacketPB;

		unsigned int len = sizeof(protocol::pb::Head);

		if(!cn->recvMsg(bev, (void*)in->setBuffer(len), len))
		{
			len = in->parseHead();

			if(len > 0)
			{
				if(!cn->recvMsg(bev, (void*)in->setBuffer(len), len))
				{
					if(!in->parse())
					{
						string input;
						in->getPB(input);

						protocol::pb::HeartBeat hb;
						hb.ParseFromString(input);
						printf("\n Heartbeat : New accepter reporting : ip = %s, port = %d, load = %d \n", \
							cn->connAddr.c_str(), hb.port(), hb.load());
						// TODO 调用算法，将节点信息记入数组
						// TODO 设置最新的最少负载节点信息
						node n = {ip:cn->connAddr, port:hb.port(), load:hb.load()};
						se->hbm->setSlave(n);
					}
				}
			}
		}

		delete in;

		return;
	}


	void HeartBeat::OnSlaveConnCb(struct bufferevent *bev, void *conn)
	{
		printf("\n Heartbeat : OnSlaveConnCb! \n");
		sendHB(bev, conn);
	}


	void HeartBeat::OnSlaveTimingCb(struct bufferevent *bev, void *conn)
	{
		printf("\n Heartbeat : OnSlaveTimingCb! \n");
		sendHB(bev, conn);
	}


	void HeartBeat::OnSlaveReadCb(struct bufferevent *bev, void *conn)
	{
		printf("\n Heartbeat : OnSlaveReadCb! \n");
	}


	void HeartBeat::sendHB(struct bufferevent *bev, void *conn)
	{
		printf("\n Heartbeat : sendHB! \n");

		common::Conn* cn = (common::Conn*)conn;
		HeartBeat* se = (HeartBeat*)cn->extra;

		protocol::pb::PacketPB *out = new protocol::pb::PacketPB;
		out->setHead();

		protocol::pb::HeartBeat hb;
		hb.set_port(se->port);
		se->load = se->hbm->getLoad();
		hb.set_load(se->load);

		string* output = new string;
		if(hb.SerializeToString(output))
		{
			out->setPB(output->c_str(), output->length());
		}

		out->setCRC();
		cn->sendMsg(bev, (void*)out->raw(), out->len());

		delete output;
		delete out;
	}
};// namespace session
