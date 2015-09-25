/*
//
//	Last Modify Date: 2015-09-18
//	Author: zengpw
//	History:
//					2015-09-18 zengpw created
//	File Property: public
//	Future:
//					I. 负载均衡测试
//
//
*/

#ifndef _TEST_BALANCE_HANDLE_H_
#define _TEST_BALANCE_HANDLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include "common/log.h"
#include "protocol/putil.h"
#include "protocol/protocol.h"
#include "session/session_handle.h"

using namespace std;

class BalanceHandle : public session::SessionHandle
{
public:
	session::SESSION_RTN dispatch(const protocol::Packet* in, protocol::Packet* out);
	session::SESSION_RTN conn(protocol::Packet* out);
	session::SESSION_RTN msg_cutover_rep(const protocol::Packet* in, protocol::Packet* out);
};

#endif