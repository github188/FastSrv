#ifndef __PS_FW_CHANNEL__
#define __PS_FW_CHANNEL__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-2 zengpw 重新设计
//					2014-9-7 zengpw 增加线程入口函数
//					2014-9-9 zengpw 增加读数据到达通知
//					2014-9-10 zengpw 将 Channel 和 Protocol 解耦
//					2014-9-18 zengpw 将 Channel 与 Thread 解耦，以后需要通过继承来使用 Channel
//	File Property : public
//	Description :	
//					I. Channel 被设计为不持有任何数据，不管理任何对象或事务的生命周期
//					II. Channel层的下级或者同级层，都不具有回调，所有的回调收敛在 Channel
//					III. Channel 有2种用途： 建立连接 或者 接收/发送数据
//	Future :
//					I. 实现异步和非阻塞
//					II. 增加一个成员变量，方便观察者判断 Channel 的事件性质
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "subject.h"

namespace PS_FW
{
	class ChannelImp;
	class ChannelImpFactory;

	class Channel : public Subject
	{
	public:
		Channel();
		virtual ~Channel();
	public:
		int setAddress(const char* ip,const int port);
		int setSocket(const int sockId);
	public:
		/* 监听，如果有客户端连接成功，会通知 socket pool */
		int acceptConn();
		static void* acceptConnThread(void* pChannel);

		/* 连接 */
		int conn();
		static void* connThread(void* pChannel);

		/* 接收数据，支持按协议读取 */
		int recvData();
		static void* recvDataThread(void* pChannel);

		/* 发送数据 */
		int sendData(const char* szBuf,const int len);
	public:
		/*---------------------
		// use : Channel属性
		// m_sockS 服务端 socket
		// m_sockP 客户端 socket
		// m_sockD 读取或发送数据使用的 socket
		// m_szIP 对端的 IP
		// m_port 对端的端口
		// m_RecvLen 读取到的数据的长度
		// m_szRecvData 读取到的数据
		---------------------*/
		int m_sockS;
		int m_sockP;
		int m_sockD;
		char m_szIP[128];
		int m_port;
		int m_RecvLen;
		char m_szRecvData[30960];
	private:
		//桥接
		ChannelImp* m_pChannelImp;
		ChannelImpFactory* m_pChannelImpFactory;
	};
}	//PS_FW

#endif //__PS_FW_CHANNEL__
