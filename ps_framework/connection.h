#ifndef __PS_FW_CONNECTION__
#define __PS_FW_CONNECTION__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年9月2日 zengpw 重新设计
//	File Property : private （此头文件是私有的）
//	Description :	I. Connection 在每个线程只有 1 个
//
//
////////////////////////////////////////////////////////////////////////////////////////

namespace PS_FW
{
	class Connection
	{
	public:
		Connection();
		virtual ~Connection(){}
	public:
	};
}	//PS_FW

#endif //__PS_FW_CONNECTION__
