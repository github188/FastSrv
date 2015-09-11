/*
//
//	Last Modify Date: 2015-09-11
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

namespace common
{
	void* HeartBeat::master(void* self)
	{
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_LISTENER, NULL, 21099);
		conn->setReadCb(OnMasterReadCb);
		conn->extra = self;
		conn->run();

		google::protobuf::ShutdownProtobufLibrary();
	}


	void* HeartBeat::slave(void* self)
	{
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		common::HeartBeat* se = (common::HeartBeat*)self;
		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_CONNECTER, NULL, 21099);
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
						printf("\n Heartbeat : hb.port = %d \n", hb.port());
						printf("\n Heartbeat : hb.load = %d \n", hb.load());
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
		common::HeartBeat* se = (common::HeartBeat*)cn->extra;

		protocol::pb::PacketPB *out = new protocol::pb::PacketPB;
		out->setHead();

		protocol::pb::HeartBeat hb;
		hb.set_port(se->port);
		// TODO : operation on the load must add lock
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
};// namespace common
