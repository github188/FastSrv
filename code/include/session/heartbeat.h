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

#ifndef _SESSION_HEARTBEAT_H_
#define _SESSION_HEARTBEAT_H_

#include <vector>
#include "common/net.h"
#include "common/thread.h"
#include "protocol/protocol_pb.h"

using namespace std;

namespace session
{
	typedef struct node
	{
		string ip;
		unsigned int port;
		unsigned int load;
	}node;
	typedef vector<node> nodeVec;


	class HeartBeatMsg
	{
	public:
		static HeartBeatMsg* instance();
		static void release();
	public:
		node n;
	public:
		// master
		node getSlave();
		void setSlave(node& n);
		// slave
		unsigned int getLoad();		
		void setLoad(unsigned int load);
	private:
		static HeartBeatMsg* hbm;
		static unsigned int ref;
		static pthread_mutex_t lock;
	private:
		HeartBeatMsg(){}
	};


	class HeartBeat
	{
	public:
		unsigned int interval;
		string addr;
		unsigned int port;
		unsigned int load;
		nodeVec vecNode;
	public:
		HeartBeatMsg* hbm;
	public:
		explicit HeartBeat(HeartBeatMsg* hbm);
		static void* master(void* self);
		static void* slave(void* self);
	public:
		static void OnMasterReadCb(struct bufferevent *bev, void *conn);
		static void OnSlaveConnCb(struct bufferevent *bev, void *conn);
		static void OnSlaveTimingCb(struct bufferevent *bev, void *conn);
		static void OnSlaveReadCb(struct bufferevent *bev, void *conn);
	public:
		static void sendHB(struct bufferevent *bev, void *conn);
	};
};// namespace session

#endif