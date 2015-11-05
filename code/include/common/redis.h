/*
//
//	Last Modify Date: 2015-11-02
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
#include "log.h"
#include "util.h"

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
		int redis_lpush(const char* key, const char* value, const int length);
		int redis_rpoplpush(const char* key_src, const char* key_dest, char* value, int* len);
		int redis_hset(const string& key, const string& field, const string& value);
		int redis_select(const int db);
		int redis_hmset4sending(const char* key, const char* begin, const char* end, const char* sts);
		int redis_hmset4update(const char* key, const char* end, const char* sts);
		int redis_move(const char* key, const int db);
		int redis_rename(const char* old_key, const char* new_key);
		int redis_expire(const string& key, const string& second);
		int redis_hget(const string& key, const string& field, string& value);
		int redis_keys(const string& vkey, vector<string>& value);
		int redis_exists(const char* key);
	};
};// namespace common

#endif
