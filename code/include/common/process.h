/*
//
//	Last Modify Date: 2015-09-11
//	Author: zengpw
//	History:
//					2015-08-27 zengpw created
//	File Property: public
//	Future:
//					I. 进程
//
//
*/

#ifndef _COMMON_PROCESS_H_
#define _COMMON_PROCESS_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <map>
#include "util.h"

using namespace std;

namespace common
{
	typedef map<string, string> StringMap;
	typedef StringMap ConfigMap;
	// key : "c:C:l:L:p:P:m:M:"
	void getConfigMap(int argc, char* argv[], string key, ConfigMap& mapConfig);

	class Process
	{
		//TODO
	};
};// namespace common

#endif