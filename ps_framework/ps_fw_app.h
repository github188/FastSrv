#ifndef __PS_FW_APP__
#define __PS_FW_APP__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 创建 framework 入口
//	File Property : public
//	Description :	I.调用 framework 的入口
//					II.可以调用 App 的 public 方法，来启动服务器或者客户端
//
//
////////////////////////////////////////////////////////////////////////////////////////

namespace PS_FW
{
	class Channel;
	class SocketManager;

	class App
	{
	public:
		App();
		virtual ~App(){}
	public:
		/* 
		//创建服务端，目前线程固定是 1 server 1 accept ; 1 client 1 read 3 deal
		// 1个服务端，1个监听线程；对于每个连接的客户端，分配1个读数据线程，3个处理数据线程
		*/
		int startServer(const char* ip,const int port);
		/* 创建客户端，如果连接成功，则分配1个读数据线程，3个处理数据线程 */
		int startConn(const char* ip,const int port);
	private:
		int init();
	private:
		/* channel for accept */
		Channel* m_pChannel;
		/* socket manager */
		SocketManager* m_pSocketManager;
	};
}	//PS_FW

#endif //__PS_FW_APP__
