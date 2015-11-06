/*
//
//	Last Modify Date: 2015-11-06
//	Author: zengpw
//	History:
//					2015-11-04 zengpw created
//	File Property: private
//	Future:
//					I. 数据库操作
//
//
*/

#ifndef _DB_BASIC_H_
#define _DB_BASIC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include "common/db.h"
#include "common/log.h"
#include "protocol/protocol_tlv.h"

using namespace std;

namespace session
{
	class DbPublic
	{
	public:
		bool public_get_order_id(common::DB* db, const string dev_id, string& order_id);
		bool public_get_parameter_request(common::DB* db, const string dev_id, TLV_PARAMETER& para);
	};
};// namespace session

#endif