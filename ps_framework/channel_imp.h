#ifndef __PS_FW_CHANNEL_IMP__
#define __PS_FW_CHANNEL_IMP__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//					2014年9月2日 zengpw 重新设计，决定在设计上，在此层不实现回调
//	File Property : private
//	Description :
//				I. 作为 socket 的实现类，向 channel 类提供封装后的实现
//				II.作为基类，定义子类需要实现的方法
//				III.在具体的子类中，实现对不同平台不同实现的封装
//				IV. ChannelImp 和 Channel 是桥接关系（ Bridge 设计模式）
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "ps_fw_define.h"

namespace PS_FW
{
	class ChannelImp
	{
	public:
		ChannelImp(){}
		virtual ~ChannelImp(){}
	public:
		//初始化 socket 环境
		virtual void init() = 0;
		//关闭 socket
		virtual void close(int& sockfd) = 0;
		//初始化监听，并返回本地 socket
		virtual int acceptConnInit(const char* ip,const int port,int& sockId) = 0;
		//监听连接（阻塞或非阻塞，由具体子类实现）
		virtual int acceptConnWait(const int sockId) = 0;
		//接受并返回对端 socket
		virtual int acceptConn(const int sockId,int& sockPeerId) = 0;
		//连接
		virtual int conn(const char* ip,const int port,int& sockPeerId) = 0;
		//接收数据
		virtual int recvData(const int sockId,char* szBuf,const int len,int& realLen) = 0;
		//发送数据
		virtual int sendData(const int sockId,const char* szBuf,const int len) = 0;
	};
}	//PS_FW

#endif //__PS_FW_CHANNEL_IMP__
