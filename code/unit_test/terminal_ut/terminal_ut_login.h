/*
//
//	Last Modify Date: 2015-11-05
//	Author: zengpw
//	History:
//					2015-11-05 zengpw created
//	File Property: public
//	Future:
//					I. task 单元测试
//
//
*/

#ifndef _TERMINAL_UT_LOGIN_H_
#define _TERMINAL_UT_LOGIN_H_

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
#include "protocol/protocol_tlv.h"
#include "session/handle_basic.h"

using namespace std;

class TerminalUtLogin : public session::HandleBasic
{
public:
	string ip;
	int port;
public:
	TerminalUtLogin();
public:
	session::HANDLE_RTN conn(protocol::PacketOut* out);
	session::HANDLE_RTN cidLogin_build(protocol::PacketOut* out);
	session::HANDLE_RTN cidLogin(const protocol::PacketIn* in, protocol::PacketOut* out);
};

#endif