/*
//
//	Last Modify Date: 2015-10-30
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
#include "common/log.h"
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
		void addLoad();
	private:
		static HeartBeatMsg* hbm;
		static unsigned int ref;
		static pthread_mutex_t lock;
	private:
		HeartBeatMsg(){}
	};


	enum HEARTBEAT_TYPE
	{
		HB_MASTER = 0x01,
		HB_SLAVE = 0x02
	};


	class HeartBeat
	{
	public:
		unsigned int hb_type;
		char addr[64];
		unsigned int port_self;
		unsigned int port_peer;
		unsigned int interval;
	public:
		common::Thread* th;
		HeartBeatMsg* hbm;
	public:
		unsigned int load;
		nodeVec vecNode;
	public:
		explicit HeartBeat(unsigned int hb_type, const char* ip, unsigned int port_peer, unsigned int interval, unsigned int port_self, common::Thread* th, HeartBeatMsg* hbm);
		void start();
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