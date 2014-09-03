////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//					2014年9月3日 zengpw 修改定义
//	File Property : public
//	Description :	
//					I.控制连接，编写数据交互规则
//					II. 所有子协议的基类，framework提供此头文件供 protocol 层使用
//					III. 作为协议的基类，同时提供一些通用的字符操作方法
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "_protocol.h"

namespace PS_FW
{
	int Protocol::verifyPacket(const char* szBegin,const char* szEnd,int& flag,int& pos)
	{
		/* 在协议的基类里，所有包都是完整包 */
		flag = 1;

		return 0;
	}
}	//PS_FW
