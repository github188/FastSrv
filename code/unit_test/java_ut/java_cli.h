/*
//
//	Last Modify Date: 2015-11-05
//	Author: zengpw
//	History:
//					2015-11-05 zengpw created
//	File Property: private
//	Future:
//					I. ICE 客户端
//
//
*/

#ifndef _JAVA_CLI_H_
#define _JAVA_CLI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "common/process.h"
#include "common/log.h"
#include "Ice/Ice.h"
#include "Ice/Service.h"
#include "interface4j.h"

using namespace std;
using namespace sending;
using namespace sending::server;

class JavaCli
{
public:
	string ip;
	string port;
	ApiPrx ap;
public:
	void setIp(string ip);
	void setPort(string port);
public:
	void push(string id, int type);
	bool run(int argc, char* argv[]);
};

#endif