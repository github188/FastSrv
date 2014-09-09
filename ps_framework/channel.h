#ifndef __PS_FW_CHANNEL__
#define __PS_FW_CHANNEL__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年9月2日 zengpw 重新设计
//					2014年9月7日 zengpw 增加线程入口函数
//					2014年9月9日 zengpw 增加读数据到达通知
//	File Property : private
//	Description :	I. Channel 被设计为不持有任何数据，不管理任何对象或事务的生命周期
//					II. Channel层的下级或者同级层，都不具有回调，所有的回调收敛在 Channel
//					III. Channel 有2种用途： 建立连接 或者 接收/发送数据
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "sys_func.h"
#include "_protocol.h"
#include "channel_imp_factory.h"
#include "subject.h"

namespace PS_FW
{
	class Channel : public Subject
	{
	public:
		Channel();
		virtual ~Channel();
	public:
		int setAddress(const char* ip,const int port);
		int setSocket(const int sockId);
		int setProtocol(Protocol* pProtocol);
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
		// m_pProtocol 读取或发送数据使用的协议，以后会改造成协议链的方式，支持同时使用多协议
		// m_szRecvData 读取到的数据（经过协议校验）
		// m_RecvLen 读取到的数据的长度
		---------------------*/
		int m_sockS;
		int m_sockP;
		int m_sockD;
		char m_szIP[128];
		int m_port;
		Protocol* m_pProtocol;
		char m_szRecvData[30960];
		int m_RecvLen;
	private:
		/*---------------------
		// use : 读取数据使用
		// m_szData A B ，2个数据区
		// m_pData 指向当前使用的数据区
		// m_pDataNext 指向下次使用的数据区
		// m_pos 数据区的实际结束地址，偏移量
		---------------------*/
		char m_szDataA[30960];
		char m_szDataB[30960];
		char* m_pData;
		char* m_pDataNext;
		int m_pos;
	private:
		//桥接
		ChannelImp* m_pChannelImp;
		ChannelImpFactory* m_pChannelImpFactory;
	};
}	//PS_FW

#endif //__PS_FW_CHANNEL__
