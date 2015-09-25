/*
//
//	Last Modify Date: 2015-09-25
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. accepter 测试
//
//
*/

#ifndef _TEST_ACCEPTER_HANDLE_H_
#define _TEST_ACCEPTER_HANDLE_H_

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

class AccepterHandle : public session::SessionHandle
{
public:
	session::SESSION_RTN dispatch(const protocol::Packet* in, protocol::Packet* out);
	session::SESSION_RTN conn(protocol::Packet* out);
	session::SESSION_RTN msg_upload_rep(const protocol::Packet* in, protocol::Packet* out);
};

#endif