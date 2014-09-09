#ifndef __PS_FW_SYS_FUNC__
#define __PS_FW_SYS_FUNC__
//////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月3日
//	Modify history :
//					2014年9月3日 zengpw 创建
//					2014年9月4日 zengpw add func
//	File Property : private
//	Description : 
//				Ⅰ. 提供一些小函数的跨平台实现
//
//////////////////////////////////////////////////////////////////////////

#include "sys_include.h"

namespace PS_FW
{
	class SYS_FUNC
	{
	public:
		/* 休眠，参数为毫秒 */
		static void sleep(int milliseconds)
		{
#ifdef _MSC_VER
			Sleep(milliseconds);
#endif //_MSC_VER
#ifdef __GNU_C__
			usleep(milliseconds*1000);
#endif //__GNU_C__
		}
	};	//SYS_FUNC
}	//PS_FW
#endif //__PS_FW_SYS_FUNC__
