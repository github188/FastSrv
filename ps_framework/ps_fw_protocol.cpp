////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//	File Property : private （此头文件是私有的）
//	Description :	I. 所有子协议的基类，framework提供此头文件供 protocol 层使用
//					II. 作为协议的基类，同时提供一些通用的字符操作方法
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "ps_fw_protocol.h"

namespace PS_FW
{
	int Protocol::verifyPacket(const char* szBegin,const char* szEnd,int& flag,int& pos)
	{
		/* 在协议的基类里，所有包都是完整包 */
		flag = 1;

		return 0;
	}
}	//PS_FW
