/*
//
//	Last Modify Date: 2015-11-12
//	Author: zengpw
//	History:
//					2015-08-26 zengpw created
//	File Property: public
//	Future:
//					I. 负载均衡消息处理
//
//
*/

#ifndef _BALANCE_HANDLE_H_
#define _BALANCE_HANDLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include "common/redis.h"
#include "common/log.h"
#include "protocol/putil.h"
#include "protocol/protocol_tlv.h"
#include "session/handle_basic.h"
#include "session/db_public.h"

using namespace std;

class BalanceHandle : public session::HandleBasic
{
public:
	common::Redis* rc;
public:
	explicit BalanceHandle(string db_conn_info):HandleBasic(db_conn_info){}
public:
	session::HANDLE_RTN reject(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidLogin(const protocol::PacketIn* in, protocol::PacketOut* out);
};

#endif