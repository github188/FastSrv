/*
//
//	Last Modify Date: 2015-10-30
//	Author: zengpw
//	History:
//					2015-10-29 zengpw created
//	File Property: private
//	Future:
//					I. 启动 ICE 服务端
//
//
*/

#ifndef _SENDING_SRV_H_
#define _SENDING_SRV_H_

#include "sending_impl.h"

using namespace std;
using namespace sending;
using namespace sending::server;

class SendingSrv : public Ice::Application
{
public:
	string port;
	common::Redis* rc;
public:
	void setPort(string port);
	void setRedis(common::Redis* rc);
public:
	int run(int argc, char* argv[]);
};

#endif