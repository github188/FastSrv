/*
//
//	Last Modify Date: 2015-11-11
//	Author: zengpw
//	History:
//					2015-11-05 zengpw created
//	File Property: private
//	Future:
//					I. ICE 客户端
//
//
*/

#include "java_cli.h"

void JavaCli::setIp(string ip)
{
	this->ip = ip;
}

void JavaCli::setPort(string port)
{
	this->port = port;
}

void JavaCli::push(string id, int type)
{
	Command m;
	m.id = id;
	m.type = type;

	LOG_DEBUG("send : m.id = " << m.id << ", m.type = " << m.type);
	Rtn r = ap->push(m);
	LOG_DEBUG("receive : r.e = " << r.e << ", r.str = " << r.str);
}

bool JavaCli::run(int argc, char* argv[])
{
	try
	{
		Ice::CommunicatorPtr ic = Ice::initialize(argc, argv);

		string conn = "sending:tcp -h " + ip;
		conn += " -p " + port;
		LOG_DEBUG("conn to : " << conn);

		Ice::ObjectPrx op = ic->stringToProxy(conn.c_str());
		ap = ApiPrx::checkedCast(op);

		// //解绑
		// this->push("201506140223", 3);

		//运行参数下发
		// this->push("201506140223", 6);

		// //版本升级
		this->push("201506140223", 8);

		// //初始化
		// this->push("201506140223", 9);
	}
	catch(const Ice::Exception& e)
	{
		LOG_DEBUG("Ice Exception!");
		return false;
	}
	catch(...)
	{
		LOG_DEBUG("Ice Initialize error!");
		return false;
	}

	return true;
}