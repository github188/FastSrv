/*
//
//	Last Modify Date: 2015-10-22
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
	TLV_HANDLE_RTN lbs2gps(LbsData* pLD, string& latitude, string& longitude);
};

#endif