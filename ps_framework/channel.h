#ifndef __PS_FW_CHANNEL__
#define __PS_FW_CHANNEL__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年9月2日 zengpw 重新设计
//	File Property : private
//	Description :	I. Channel 被设计为不持有任何数据，不管理任何对象或事务的生命周期
//					II. Channel层的下级或者同级层，都不具有回调，所有的回调收敛在 Channel
//					III. Channel 有2种用途： 建立连接 或者 接收/发送数据
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
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
		/* 监听，如果有客户端连接成功，会通知 socket pool */
		int acceptConn(const char* ip,const int port);

		/* 连接 */
		int conn(const char* ip,const int port);

		/* 接收数据，支持按协议读取 */
		int recvData(const int sockId,char* rBuf,int& rlen,Protocol* pProtocol);

		/* 发送数据 */
		int sendData(const int sockId,const char* sBuf,const int slen);
	public:
		//仅用于 监听 或 连接 成功以后，临时存放 socket
		int m_sockS;
		int m_sockP;
	private:
		ChannelImp* m_pChannelImp;
		ChannelImpFactory* m_pChannelImpFactory;
	private:
		/*---------------------
		// 读取方式
		// szData A B ，2个数据区
		// pData 指向当前使用的数据区
		// pDataNext 指向下次使用的数据区
		// pos 数据区的实际结束地址，偏移量
		---------------------*/
		char m_szDataA[30960];
		char m_szDataB[30960];
		char* m_pData;
		char* m_pDataNext;
		int m_pos;
	};
}	//PS_FW

#endif //__PS_FW_CHANNEL__
