/*
//
//	Last Modify Date: 2015-08-28
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
#include "balance_handle.h"

using namespace std;

void OnDataHandleCb(void* conn, struct bufferevent* pEvbuf, int conn_event);

#endif