/*
//
//	Last Modify Date: 2015-09-02
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
	void* HeartBeat::master(void*)
	{
		nodeVec vecNode;

		common::Conn* conn = new common::Conn;

		conn->init(common::CONN_TYPE_LISTENER, NULL, 21099);
		conn->setReadCb(OnMasterReadCb);
		conn->run();
	}


	void* HeartBeat::slave(void*)
	{
		node n;

		common::Conn* conn = new common::Conn;

		conn->init(common::CONN_TYPE_CONNECTER, NULL, 21099);
		conn->setConnCb(OnSlaveConnCb);
		conn->setReadCb(OnSlaveReadCb);

		while(true)
		{
			conn->run();
			printf("\n Heartbeat : Master not find. Slave sleep 30 Seconds. \n");
			sleep(30);
		}
	}


	void HeartBeat::OnMasterReadCb(struct bufferevent *bev, void *conn)
	{
		printf("\n Heartbeat : OnMasterReadCb! \n");
	}


	void HeartBeat::OnSlaveConnCb(struct bufferevent *bev, void *conn)
	{
		printf("\n Heartbeat : OnSlaveConnCb! \n");
		//TODO 客户端发送自己的端口及负载信息
	}


	void HeartBeat::OnSlaveReadCb(struct bufferevent *bev, void *conn)
	{
		printf("\n Heartbeat : OnSlaveReadCb! \n");
	}
};// namespace common
