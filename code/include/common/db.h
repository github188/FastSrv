/*
//
//	Last Modify Date: 2015-12-10
//	Author: zengpw
//	History:
//					2015-10-20 zengpw created
//	File Property: public
//	Future:
//					I. 封装 otl
//
//
*/

#ifndef _COMMON_DB_H_
#define _COMMON_DB_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <vector>
#include "log.h"
#include "util.h"

// otl head
#define OTL_ORA11G_R2
#include "otl/otlv4.h"

using namespace std;

namespace common
{
	class DB
	{
	public:
		string conn_info;
		otl_connect* conn;
		bool status;
	public:
		explicit DB(string conn_info);
		~DB();
	public:
		otl_connect* getConn();
		bool check();
	public:
		bool insert(const string& sql);
		bool update(const string& sql);
	};
};// namespace common

#endif