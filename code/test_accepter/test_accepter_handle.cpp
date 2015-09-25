/*
//
//	Last Modify Date: 2015-09-25
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. accepter 测试
//
//
*/

#include "test_accepter_handle.h"

session::SESSION_RTN AccepterHandle::dispatch(const protocol::Packet* in, protocol::Packet* out)
{
	out->copyHead(in);

	if(in->ptrHead->command_id == protocol::data::MSG_UPLOAD_REP)
	{
		return msg_cutover(in, out);
	}

	return session::SESSION_RTN_CONTINUE;
}


session::SESSION_RTN AccepterHandle::conn(protocol::Packet* out)
{
	LOG_DEBUG("AccepterHandle conn");

	out->setHead();
	out->ptrHead->command_id = protocol::data::MSG_UPLOAD;

	//生成本地时间
	struct timeval tv;
	gettimeofday(&tv, NULL);

	struct tm* pst;
	pst = localtime(&tv.tv_sec);

	char buf[64];
	memset(buf,0,sizeof(buf));
	strftime(buf, sizeof(buf), "%Y %m %d %H %M %S", pst);
	LOG_DEBUG("LOCAL TIME : " << buf);

	protocol::data::DateTimePtr ptrDateTime = protocol::data::cDateTime(pst->tm_year - 100, pst->tm_mon + 1, pst->tm_mday, pst->tm_hour, pst->tm_min, pst->tm_sec);

	// 发送时间
	out->setTLV(protocol::data::DATA_SENDING_TIME, sizeof(protocol::data::DateTime), (char*)ptrDateTime);
	out->setCRC();

	return session::SESSION_RTN_SEND;
}


session::SESSION_RTN AccepterHandle::msg_upload_rep(const protocol::Packet* in, protocol::Packet* out)
{
	// TODO 打印收到的 time 即可

	return session::SESSION_RTN_CONTINUE;
}

