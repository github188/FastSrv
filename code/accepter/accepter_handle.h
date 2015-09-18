/*
//
//	Last Modify Date: 2015-09-17
//	Author: zengpw
//	History:
//					2015-09-02 zengpw created
//	File Property: private
//	Future:
//					I. 消息预处理
//
//
*/

#ifndef _ACCEPTER_HANDLE_H_
#define _ACCEPTER_HANDLE_H_

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
#include "common/redis.h"

using namespace std;

class AccepterHandle : public session::SessionHandle
{
public:
	common::Redis* r;
public:
	bool redis_init(string ip, unsigned int port);
public:
	bool msg_upload(const protocol::Packet* in, protocol::Packet* out);
};

#endif