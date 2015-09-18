/*
//
//	Last Modify Date: 2015-09-18
//	Author: zengpw
//	History:
//					2015-09-15 zengpw created
//	File Property: public
//	Future:
//					I. TLV 公共消息处理
//
//
*/

#ifndef _SESSION_HANDLE_H_
#define _SESSION_HANDLE_H_

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
#include "heartbeat.h"

using namespace std;

namespace session
{
	class SessionHandle
	{
	public:
		virtual bool dispatch(const protocol::Packet* in, protocol::Packet* out);
		virtual bool msg_cutover(const protocol::Packet* in, protocol::Packet* out);
		virtual bool msg_time(const protocol::Packet* in, protocol::Packet* out);
		virtual bool msg_upload(const protocol::Packet* in, protocol::Packet* out);
	};
};// namespace session

#endif