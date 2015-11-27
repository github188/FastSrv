/*
//
//	Last Modify Date: 2015-11-12
//	Author: zengpw
//	History:
//					2015-11-05 zengpw created
//	File Property: public
//	Future:
//					I. task 单元测试
//
//
*/

#include "terminal_ut_login.h"

TerminalUtLogin::TerminalUtLogin()
{
	ip = "";
	port = 0;
}


session::HANDLE_RTN TerminalUtLogin::conn(protocol::PacketOut* out)
{
	return cidLogin_build(out);
}


session::HANDLE_RTN TerminalUtLogin::cidLogin_build(protocol::PacketOut* out)
{
	out->setDevId("201506140223");
	out->setCID(CID_LOGIN);

	TLV_DEV_FIRM tdf;

	tdf.version = 0;

	memset(tdf.imei, 0, sizeof(tdf.imei));
	strncpy((char*)tdf.imei, "866104021101384", 15);

	memset(tdf.iccid, 0, sizeof(tdf.iccid));
	strncpy((char*)tdf.iccid, "89860112453700206680", 20);

	out->add(TID_DEV_FIRM, sizeof(TLV_DEV_FIRM), (char*)&tdf);
	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtLogin::cidLogin(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	stringstream ss;

	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_TIME)
		{
			TLV_TIME tt;

			memcpy(&tt, iter->value, iter->len);

			printDateTimeSec(tt);
			LOG_DEBUG("cidLogin - TID_TIME - " << DateTime2StringSec(tt));
		}

		if(iter->type == TID_PARAMETER)
		{
			TLV_PARAMETER para;

			memcpy(&para, iter->value, iter->len);

			LOG_DEBUG("---------- TLV_PARAMETER content : ");
			LOG_DEBUG("addr = " << para.addr << \
					", port = " << para.port << \
					", apn = " << para.apn << \
					", user = " << para.user << \
					", pass = " << para.pass << \
					", net = " << (int)para.net << \
					", band = " << (int)para.band << \
					", led = " << (int)para.led);
			LOG_DEBUG("---------- end.");

			ss << para.addr;
			this->ip = ss.str();
			ss.str("");
			ss.clear();

			ss << para.port;
			ss >> this->port;
			ss.str("");
			ss.clear();
		}
	}

	return session::HANDLE_RTN_STOP;
}