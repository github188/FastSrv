/*
//
//	Last Modify Date: 2015-09-18
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
#include "protocol/putil.h"
#include "protocol/protocol.h"
#include "session/session_handle.h"

using namespace std;

class BalanceHandle : public session::SessionHandle
{
public:
	bool msg_cutover(const protocol::Packet* in, protocol::Packet* out);
};

#endif