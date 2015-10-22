/*
//
//	Last Modify Date: 2015-10-22
//	Author: zengpw
//	History:
//					2015-10-09 zengpw created
//	File Property: private
//	Future:
//					I. 消息分析和入库
//
//
*/

#ifndef _UPLOAD_HANDLE_H_
#define _UPLOAD_HANDLE_H_

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
#include "common/db.h"
#include "common/log.h"
#include "protocol/putil.h"
#include "protocol/protocol_tlv.h"
#include "session/handle_basic.h"
#include "tlv_handle.h"
#include "db_interface.h"

using namespace std;

class UploadHandle : public session::HandleBasic
{
public:
	UploadHandle(string db_conn_info):HandleBasic(db_conn_info){}
public:
	session::HANDLE_RTN cidDataGps(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidDataLbs(const protocol::PacketIn* in, protocol::PacketOut* out);
};

#endif