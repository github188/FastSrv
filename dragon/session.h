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
//					I. 控制连接和数据，编写交互规则
//					II. 要求是线程安全的
//					III. session 的 virtual 函数都是基于事件的，但是会预先对数据做处理
//					IV. session 可以缓存部分数据
//	Future :
//					I. 实现更多基本控制
//					II. 实现一个查找比较快的数据结构
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "_protocol.h"

namespace PS_FW
{
	typedef std::map<std::string,std::string> MsgTypeMap;

	class Session
	{
	public:
		Session();
		virtual ~Session(){}
	public:
		virtual int onReceive(const char* pMessageIn,const int lenIn) = 0;
		virtual int onInitMsgTypeMap(MsgTypeMap& pMsgTypeMap) = 0;
	public:
		void receive(const char* pMessageIn);
		int init(Protocol* pProtocol);
	protected:
		//字符串 - 消息类型
		MsgTypeMap m_mapMsgTypeMap;
		/*---------------------
		// use : session处理数据
		// m_szMessageIn session的输入数据
		// m_szMessageOut session的输出数据
		---------------------*/
		int m_lenIn;
		int m_lenOut;
		char m_szMessageIn[30960];
		char m_szMessageOut[30960];
	private:
		int isStart;
		Protocol* m_pProtocol;
	};
}	//PS_FW

#endif //__PS_FW_SESSION__
