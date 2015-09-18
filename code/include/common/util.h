/*
//
//	Last Modify Date: 2015-09-11
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
#include <set>

using namespace std;

namespace common
{
	typedef set<string> StringSet;
	void split(const string& in, const string delimiter, StringSet& out);
};// namespace common

#endif
