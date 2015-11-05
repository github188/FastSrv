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

#include "sending_srv.h"

void SendingSrv::setPort(string port)
{
	this->port = port;
}

void SendingSrv::setRedis(common::Redis* rc)
{
	this->rc = rc;
}

int SendingSrv::run(int argc, char* argv[])
{
	string srv = "default -p " + port;
	LOG_DEBUG("service on : sending:" << srv);

	Ice::CommunicatorPtr ic = Ice::initialize(argc, argv);
	Ice::ObjectAdapterPtr ap = ic->createObjectAdapterWithEndpoints("sending", srv.c_str());

	SendingImpl* si = new SendingImpl;
	si->setRedis(rc);
	ap->add(si, ic->stringToIdentity("sending"));
	ap->activate();
	ic->waitForShutdown();

	return 0;
}
