/*
//
//	Last Modify Date: 2015-09-17
//	Author: zengpw
//	History:
//					2015-09-17 zengpw created
//	File Property: public
//	Future:
//					I. redis 接口
//
//
*/

#ifndef _COMMON_REDIS_H_
#define _COMMON_REDIS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <vector>
#include "hiredis/hiredis.h"

using namespace std;

namespace common
{
	class Redis
	{
	public:
		string ip;
		unsigned int port;
		redisContext* c;
	public:
		explicit Redis(string ip, unsigned int port);
	public:
		int redis_conn();
		int redis_hset(const std::string& key, const std::string& field, const std::string& value);
		int redis_expire(const std::string& key, const std::string& second);
		int redis_hget(const std::string& key, const std::string& field, std::string& value);
		int redis_keys(const std::string& vkey, std::vector<std::string>& value);
	};
};// namespace common

#endif
