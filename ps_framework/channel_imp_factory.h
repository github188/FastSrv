#ifndef __PS_FW_CHANNEL_IMP_FACTORY__
#define __PS_FW_CHANNEL_IMP_FACTORY__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//					2014年9月2日 zengpw 修改说明和头文件
//	File Property : private
//	Description :
//					I. 作为 ChannelImp 的抽象工厂
//					II.为了避免源文件膨胀，将实现写在 .h 里
//
////////////////////////////////////////////////////////////////////////////////////////

#include "channel_imp.h"
#include "channel_imp_win.h"
#include "channel_imp_linux.h"

namespace PS_FW
{
	class ChannelImpFactory
	{
	public:
		ChannelImpFactory(){};
		virtual ~ChannelImpFactory(){};
		ChannelImp* create()
		{
#ifdef _MSC_VER
			return new ChannelImpWin;
#endif
#ifdef __GNU_C__
			return new ChannelImpLinux;
#endif
		}
	};
}	//PS_FW

#endif //__PS_FW_CHANNEL_IMP_FACTORY__

