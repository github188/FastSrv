/*
//
//	Last Modify Date: 2015-08-28
//	Author: zengpw
//	History:
//					2015-08-12 zengpw created
//	File Property: public
//	Future:
//					I. 部分工具
//
//
*/

#ifndef _COMMON_UTIL_H_
#define _COMMON_UTIL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

namespace common
{
	class Error
	{
	public:
		string id;
		string msg;
	public:
		Error();
		Error(string eId,string eMsg);
		void set(string eId,string eMsg);
		string getId();
		string getMsg();
		void print();
	};// class Error
};// namespace common

#endif
