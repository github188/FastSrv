/*
//
//	Last Modify Date: 2015-11-03
//	Author: zengpw
//	History:
//					2015-10-28 zengpw created
//	File Property: private
//	Future:
//					I. 实现 ICE 的接口
//
//
*/

#ifndef _SENDING_IMPL_H_
#define _SENDING_IMPL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include "common/redis.h"
#include "common/process.h"
#include "common/log.h"
#include "Ice/Ice.h"
#include "Ice/Service.h"
#include "interface4j.h"

using namespace std;
using namespace sending;
using namespace sending::server;

class SendingImpl : public sending::server::Api
{
public:
	common::Redis* rc;
public:
	void setRedis(common::Redis* rc);
	::sending::server::Rtn buildRtn(int e, string str);
public:
	::sending::server::Rtn push(const ::sending::server::Command& cmd, const ::Ice::Current& c = ::Ice::Current());
};

#endif