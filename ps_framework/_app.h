#ifndef __PS_FW_APP__
#define __PS_FW_APP__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 创建 framework 入口
//					2014年9月3日 zengpw 增加线程管理
//					2014年9月7日 zengpw 修改（缩小） app 能持有的类对象
//	File Property : public
//	Description :	I.调用 framework 的入口
//					II.可以调用 App 的 public 方法，来启动服务器或者客户端
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "_protocol.h"
#include "_session.h"

namespace PS_FW
{
	class Event;
	class Connection;

	class App
	{
	public:
		App();
		virtual ~App();
	public:
		//创建服务端，目前线程固定是 1 server 1 accept ; 1 client 1 read 3 deal
		// 1个服务端，1个监听线程；对于每个连接的客户端，分配1个读数据线程，3个处理数据线程
		int server(const char* ip,const int port);

		/* 创建客户端，如果连接成功，则分配1个读数据线程，3个处理数据线程 */
		int client(const char* ip,const int port);

		/* 等待线程返回 */
		void join();
	private:
		/*---------------------
		// use : 持有的变量
		// m_pProtocol 使用的协议
		// m_pSession
		// m_pConnection ， 和 session 是1对1关系
		// m_pEvent 事件监视
		---------------------*/
		Protocol* m_pProtocol;
		Session* m_pSession;
		Connection* m_pConnection;
		Event* m_pEvent;
		/*---------------------
		// use : 持有的消息池
		//
		---------------------*/
	};
}	//PS_FW

#endif //__PS_FW_APP__
