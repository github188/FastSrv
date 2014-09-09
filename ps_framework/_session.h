#ifndef __PS_FW_SESSION__
#define __PS_FW_SESSION__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月3日
//	Modify history :
//					2014年9月3日 zengpw 创建
//					2014年9月9日 zengpw 增加消息处理循环，提供接口
//	File Property : public
//	Description :
//					I. 控制连接，编写交互规则
//					II. session 要做到线程安全
//
//
////////////////////////////////////////////////////////////////////////////////////////

namespace PS_FW
{
	class Session
	{
	public:
		Session(){}
		virtual ~Session(){}
	public:
		virtual int getMessageType(char* szType);
		virtual int dealLogon();
		virtual int dealLogout();
	public:
		//设置输入数据
		int setMessageIn(const char* pMessageIn);
		//处理输入数据
		virtual int dealMessage();
		//获取输出数据
		int getMessageOut(char* pMessageOut,int len);
	protected:
		/*---------------------
		// use : session处理数据
		// m_szMessageIn session的输入数据
		// m_szMessageOut session的输出数据 
		---------------------*/
		char m_szMessageIn[10240];
		char m_szMessageOut[10240];
	};
}	//PS_FW

#endif //__PS_FW_SESSION__
