/*
//
//	Last Modify Date: 2015-11-03
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


	void HeartBeatMsg::addLoad()
	{
		pthread_mutex_lock(&this->lock);
		this->n.load++;
		pthread_mutex_unlock(&this->lock);
	}


	void HeartBeatMsg::setSlave(node& n)
	{
		pthread_mutex_lock(&this->lock);
		this->n = n;
		pthread_mutex_unlock(&this->lock);
	}


	HeartBeat::HeartBeat(unsigned int hb_type, const char* ip, unsigned int port_peer, unsigned int interval, unsigned int port_self, common::Thread* th, HeartBeatMsg* hbm)
	{
		this->hb_type = hb_type;

		if(ip != NULL)
			strcpy(addr, ip);

		this->port_peer = port_peer;
		this->port_self = port_self;
		this->interval = interval;
		this->th = th;
		this->hbm = hbm;
	}


	void HeartBeat::start()
	{
		if(hb_type == HB_MASTER)
			th->create(master, (void*)this);

		if(hb_type == HB_SLAVE)
			th->create(slave, (void*)this);
	}


	void* HeartBeat::master(void* self)
	{
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		HeartBeat* se = (HeartBeat*)self;

		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_LISTENER, NULL, se->port_self);
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
		conn->init(common::CONN_TYPE_CONNECTER, se->addr, se->port_peer);
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
			LOG_DEBUG("Heartbeat : Master not find. Slave sleep 5 Seconds.");
			sleep(5);
		}

		google::protobuf::ShutdownProtobufLibrary();
	}


	void HeartBeat::OnMasterReadCb(struct bufferevent *bev, void *conn)
	{
		// LOG_DEBUG("Heartbeat : OnMasterReadCb!");

		common::Conn* cn = (common::Conn*)conn;
		HeartBeat* se = (HeartBeat*)cn->extra;

		for(;;)
		{
			protocol::pb::PacketPB *in = new protocol::pb::PacketPB;

			int len = sizeof(protocol::pb::Head);

			if(cn->recvMsg(bev, (void*)in->setHead(), len) == 0)
			{
				len = in->parseHead();

				if(len > 0)
				{
					if(cn->recvMsg(bev, (void*)in->setBody(len), len) == 0)
					{
						string input;

						if(!in->parseBody(input))
						{
							protocol::pb::HeartBeat hb;
							hb.ParseFromString(input);
							LOG_DEBUG("Heartbeat : New accepter reporting : ip = " << cn->connAddr << ", port = " << hb.port() << ", load = " << hb.load());
							// TODO 调用算法，将节点信息记入数组
							// TODO 设置最新的最少负载节点信息
							node n = {ip:cn->connAddr, port:hb.port(), load:hb.load()};
							se->hbm->setSlave(n);
						}
						else
							return;
					}
					else
						return;
				}
				else
					return;
			}
			else
				return;

			delete in;
		}

		return;
	}


	void HeartBeat::OnSlaveConnCb(struct bufferevent *bev, void *conn)
	{
		// LOG_DEBUG("Heartbeat : OnSlaveConnCb!");
		sendHB(bev, conn);
	}


	void HeartBeat::OnSlaveTimingCb(struct bufferevent *bev, void *conn)
	{
		// LOG_DEBUG("Heartbeat : OnSlaveTimingCb!");
		sendHB(bev, conn);
	}


	void HeartBeat::OnSlaveReadCb(struct bufferevent *bev, void *conn)
	{
		// LOG_DEBUG("Heartbeat : OnSlaveReadCb!");
	}


	void HeartBeat::sendHB(struct bufferevent *bev, void *conn)
	{
		// LOG_DEBUG("Heartbeat : sendHB!");

		common::Conn* cn = (common::Conn*)conn;

		HeartBeat* se = (HeartBeat*)cn->extra;
		se->load = se->hbm->getLoad();

		protocol::pb::HeartBeat hb;
		hb.set_port(se->port_self);
		hb.set_load(se->load);

		string output;
		if(hb.SerializeToString(&output))
		{
			protocol::pb::PacketPB *out = new protocol::pb::PacketPB;
			out->build(output, output.length());
			cn->sendMsg(bev, (void*)out->getMsg(), out->getMsgLen());
			delete out;
		}
	}
};// namespace session
