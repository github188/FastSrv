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

#ifndef _HEARTBEAT_H_
#define _HEARTBEAT_H_

#include <vector>
#include "net.h"
#include "protocol/protocol_data_heartbeat.pb.h"

using namespace std;

namespace common
{
	typedef struct node
	{
		string ip;
		unsigned int port;
		unsigned int load;
	}node;
	typedef vector<node> nodeVec;

	class HeartBeat
	{
	public:
		static void* master(void*);
		static void* slave(void*);
	public:
		static void OnMasterReadCb(struct bufferevent *bev, void *conn);
		static void OnSlaveConnCb(struct bufferevent *bev, void *conn);
		static void OnSlaveReadCb(struct bufferevent *bev, void *conn);
	};

};// namespace common

#endif