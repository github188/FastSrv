/*
//
//	Last Modify Date: 2015-10-15
//	Author: zengpw
//	History:
//					2015-09-02 zengpw created
//	File Property: private
//	Future:
//					I. 消息入队
//
//
*/

#ifndef _TASK_HANDLE_H_
#define _TASK_HANDLE_H_

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

using namespace std;

class TaskHandle : public session::HandleBasic
{
public:
	common::Redis* rc;
public:
	void shortResponse(protocol::PacketOut* out, int success);
	session::HANDLE_RTN flashPush(const protocol::PacketIn* in, protocol::PacketOut* out);
public:
	session::HANDLE_RTN cidDataGps(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidDataLbs(const protocol::PacketIn* in, protocol::PacketOut* out);
};

#endif