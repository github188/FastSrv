/*
//
//	Last Modify Date: 2015-11-12
//	Author: zengpw
//	History:
//					2015-10-22 zengpw created
//	File Property: private
//	Future:
//					I. http 操作
//
//
*/

#ifndef _HTTP_INTERFACE_H_
#define _HTTP_INTERFACE_H_

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
#include "common/py_call.h"
#include "common/log.h"
#include "protocol/protocol_tlv.h"
#include "tlv_handle_data.h"

using namespace std;

class HttpInterface
{
public:
	common::PyCall python_call;
public:
	TLV_HANDLE_RTN lbs2gps(TLV_LBS& lbs, string& latitude, string& longitude);
	TLV_HANDLE_RTN lbs2gps(TLV_MANAGE_LBS& m_lbs, string& latitude, string& longitude);
	TLV_HANDLE_RTN lbs2gpsAmap(vector<LbsData> &vLbs, string& latitude, string& longitude);
	TLV_HANDLE_RTN gps2addrAmap(const string& latitude, const string& longitude, string& addr);
};

#endif