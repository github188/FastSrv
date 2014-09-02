////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//	File Property : private （此头文件是私有的）
//	Description :	I. PS_FW::protocol 的子类，实现具体的协议
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "ps_net_as_protocol.h"

namespace PS_NET
{
	AsProtocol::AsProtocol()
	{
		strncpy(m_szAllowLogon,"<?xml version=\"1.0\"?><cross-domain-policy><site-control permitted-cross-domain-policies=\"all\"/><allow-access-from domain=\"*\" to-ports=\"*\"/></cross-domain-policy>",512);
	}
}	//PS_NET
