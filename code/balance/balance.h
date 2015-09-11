/*
//
//	Last Modify Date: 2015-09-02
//	Author: zengpw
//	History:
//					2015-08-26 zengpw created
//	File Property: private
//	Future:
//					I. 负载均衡
//
//
*/

#ifndef _BALANCE_H_
#define _BALANCE_H_

#include "common/net.h"
#include "common/thread.h"
#include "common/heartbeat.h"
#include "balance_handle.h"

using namespace std;

void* threadCb(void* arg);
void OnReadCb(struct bufferevent *bev, void *conn);

#endif