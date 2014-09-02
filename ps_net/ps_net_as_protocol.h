#ifndef __PS_NET_AS_PROTOCOL__
#define __PS_NET_AS_PROTOCOL__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//	File Property : public （此头文件是对外公开的）
//	Description :	I. PS_FW::protocol 的子类，实现具体的协议
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "ps_framework/ps_fw_protocol.h"

namespace PS_NET
{
	class AsProtocol : public PS_FW::Protocol
	{
	public:
		AsProtocol();
		virtual ~AsProtocol(){}
	public:
		char m_szAllowLogon[512];
	};
}	//PS_NET

#endif //__PS_NET_AS_PROTOCOL__
