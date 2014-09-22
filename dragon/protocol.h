#ifndef __PS_FW_PROTOCOL__
#define __PS_FW_PROTOCOL__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年9月9日 zengpw 明确安全要求
//					2014年9月10日 zengpw 修改设计，增加数据初始化接口
//					2014年9月11日 zengpw 现在一个 session 对象会持有一个 protocol 对象
//	File Property : public
//	Description :	
//					I. 控制数据，编写数据交互规则
//					II. 要求是线程安全的
//					III. protocol 的输入输出都是字符串
//					IV. protocol 可以缓存部分数据
//					V. protocol的 virtual 函数都是基于字符串处理的
//	Future :
//					I. 优化缓冲区算法
//
//
////////////////////////////////////////////////////////////////////////////////////////

namespace PS_FW
{
	class Protocol
	{
	public:
		Protocol();
		virtual ~Protocol(){}
	public:
		//校验接收的包是否完整，是协议的一部分，由使用者继承实现
		// szBegin 包开始地址
		// szEnd 包结束地址
		// flag 取值： 1（整包） || 2（整包 + 部分包） || 3（部分包） || 4（错误包）
		// pos 当 flag = 2 时，返回 包偏移地址
		virtual int verifyPacket(const char* szBegin,const char* szEnd,int& flag,int& pos);
	public:
		//对收到的包进行初始化，此函数不需要用户继承，用户只需要按实际情况重写 verifyPacket()
		int messageInit(const char* pMessageIn,const int lenIn,char* pMessageOut,int& lenOut);
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
	};
}	//PS_FW

#endif //__PS_FW_PROTOCOL__
