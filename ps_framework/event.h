#ifndef __PS_FW_EVENT__
#define __PS_FW_EVENT__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 用于管理成功建立的 socket
//					2014年9月8日 zengpw 用于管理所有发生的事件
//					2014年9月9日 zengpw 完善服务端事件
//	File Property : private
//	Description :
//					I. 事件观察者
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "subject.h"
#include "observer.h"
#include "channel.h"
#include "connection.h"
#include "_session.h"

namespace PS_FW
{
	class Event : public Observer
	{
	public:
		Event();
		virtual ~Event();
	public:
		int AttachConnection(Connection* pConnection);
		int AttachSession(Session* pSession);
	public:
		virtual void Update(Subject* pSubject);
	private:
		/*---------------------
		// use : 监听Connection及其内部通道
		// m_pConnection 用来实现某些监听后的操作
		// m_pChannelServer 服务监听
		// m_pChannelClient 连接监听
		// m_pChannelRead 数据到达监听
		---------------------*/
		Connection* m_pConnection;
		Channel* m_pChannelServer;
		Channel* m_pChannelClient;
		Channel* m_pChannelRead;
		/*---------------------
		// use : 监听Session
		// m_pSession 对应于 Connection 的 Session
		---------------------*/
		Session* m_pSession;
	};
}	//PS_FW

#endif //__PS_FW_EVENT__
