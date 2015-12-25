/*
//
//	Last Modify Date: 2015-12-01
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

#define LOAD_INCR(p) session::HeartBeat::instance()->incr(p)
#define LOAD_DECR(p) session::HeartBeat::instance()->decr(p)

namespace session
{
	class node
	{
	public:
		string ip;
		unsigned int port;
		unsigned int load;
		long long live_time;
	public:
		node& operator=(const node& n);
		bool operator!=(const node& n) const;
		bool operator==(const node& n) const;
		bool operator<(const node& n) const;
	};
	typedef vector<node> nodeVec;
	typedef multimap<int, node> nodeMap;

	class HeartBeat
	{
	public:
		char ip[64];
		unsigned int port;
		unsigned int interval;
		unsigned int self_port;
		common::Thread* th;
	public:
		//---------slave
		pthread_mutex_t lock;
		unsigned int load;
		//---------master
		nodeVec vn;
	public:
		static HeartBeat* create(const unsigned int port, common::Thread* th);
		static HeartBeat* create(const char* ip, const unsigned int port, const unsigned int interval, const unsigned int self_port, common::Thread* th);
		static HeartBeat* instance();
	public:
		static void* master(void* self);
		static void* slave(void* self);
		static void OnMasterReadCb(struct bufferevent *bev, void *conn);
		static void OnSlaveConnCb(struct bufferevent *bev, void *conn);
		static void OnSlaveTimingCb(struct bufferevent *bev, void *conn);
		static void OnSlaveReadCb(struct bufferevent *bev, void *conn);
	public:
		//---------slave
		void incr(unsigned int load);
		void decr(unsigned int load);
		unsigned int get();
		//---------master
		void push(node& n);
		node pop();
	protected:
		HeartBeat(){}
	private:
		static HeartBeat* hb;
	};
};// namespace session

#endif