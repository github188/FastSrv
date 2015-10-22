/*
//
//	Last Modify Date: 2015-10-22
//	Author: zengpw
//	History:
//					2015-10-20 zengpw created
//	File Property: private
//	Future:
//					I. tlv 消息处理
//
//
*/

#ifndef _TLV_HANDLE_H_
#define _TLV_HANDLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include "common/redis.h"
#include "common/log.h"
#include "protocol/putil.h"
#include "protocol/protocol_tlv.h"
#include "http_interface.h"
#include "tlv_handle_data.h"

using namespace std;

class TlvHandle
{
public:
	TLV_HANDLE_RTN basic_data_handle(BasicData& bd, HANDLE_BasicData& hbd);
public:
	TLV_HANDLE_RTN tlv_gps_handle(TLV_GPS& gps, TLV_HANDLE_GPS& gps_handle);
	TLV_HANDLE_RTN tlv_lbs_handle(TLV_LBS& lbs, TLV_HANDLE_LBS& lbs_handle);
};

#endif