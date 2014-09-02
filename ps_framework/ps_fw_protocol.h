#ifndef __PS_FW_PROTOCOL__
#define __PS_FW_PROTOCOL__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//	File Property : public （此头文件是对外公开的）
//	Description :	I. 所有子协议的基类，framework提供此头文件供 protocol 层使用
//					II. 作为协议的基类，同时提供一些通用的字符操作方法
//
//
////////////////////////////////////////////////////////////////////////////////////////

namespace PS_FW
{
	class Protocol
	{
	public:
		Protocol(){}
		virtual ~Protocol(){}
	public:
		//校验接收的包是否完整，是协议的一部分，由使用者继承实现
		// szBegin 包开始地址
		// szEnd 包结束地址
		// flag 取值： 1（整包） || 2（整包 + 部分包） || 3（部分包） || 4（错误包）
		// pos 当 flag = 2 时，返回 包偏移地址
		virtual int verifyPacket(const char* szBegin,const char* szEnd,int& flag,int& pos);
	};
}	//PS_FW

#endif //__PS_FW_PROTOCOL__
