/*
//
//	Last Modify Date: 2015-09-25
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
#include "common/log.h"

using namespace std;

namespace session
{
	// 应用层返回给 session 的指示
	typedef enum SESSION_RTN
	{
		SESSION_RTN_SEND = 0x01,				//发送 out 报文
		SESSION_RTN_CONTINUE = 0x02,			//忽略 out 报文并继续
		SESSION_RTN_STOP = 0x04					//关闭 session
	}SESSION_RTN;

	class SessionHandle
	{
	public:
		virtual SESSION_RTN dispatch(const protocol::Packet* in, protocol::Packet* out);
		virtual SESSION_RTN conn(protocol::Packet* out);
		virtual SESSION_RTN msg_cutover(const protocol::Packet* in, protocol::Packet* out);
		virtual SESSION_RTN msg_time(const protocol::Packet* in, protocol::Packet* out);
		virtual SESSION_RTN msg_upload(const protocol::Packet* in, protocol::Packet* out);
	};
};// namespace session

#endif