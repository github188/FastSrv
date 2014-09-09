#ifndef __PS_FW_CONNECTION__
#define __PS_FW_CONNECTION__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月3日
//	Modify history :
//					2014年9月3日 zengpw 连接管理
//					2014年9月7日 zengpw 添加实现
//					2014年9月9日 zengpw 规范注释，添加处理线程
//	File Property : private
//	Description :
//					I.这个类的对象的生命周期是全局的，随着进程退出而消亡
//					Ⅱ.它拥有 主动连接 和 被动连接 2种方式
//					Ⅲ.它直接持有 Channel 对象
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "thread.h"
#include "channel.h"
#include "_protocol.h"
#include "_session.h"

namespace PS_FW
{
	class Connection : public Thread
	{
	public:
		Connection();
		virtual ~Connection();
	public:
		int setProtocol(Protocol* pProtocol);
		int setSession(Session* pSession);
	public:
		int server(const char* ip,const int port);
		int client(const char* ip,const int port);
		int read(const int sockId);
		int send(const int sockId);
		static void* dealThread(void* pConnection);
	public:
		/*---------------------
		// use : 内置的对象
		// m_pChannelServer 服务线程
		// m_pChannelClient 连接线程
		// m_pChannelRead 数据读取线程
		// m_pChannelSend 数据发送线程
		---------------------*/
		Channel* m_pChannelServer;
		Channel* m_pChannelClient;
		Channel* m_pChannelRead;
		Channel* m_pChannelSend;
		/*---------------------
		// use : 外部的对象
		// m_pProtocol 使用的协议
		// m_pSession 使用的session
		---------------------*/
		Protocol* m_pProtocol;
		Session* m_pSession;
	};
}	//PS_FW

#endif //__PS_FW_CONNECTION__
