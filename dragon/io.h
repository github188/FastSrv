#ifndef __DRAGON_IO__
#define __DRAGON_IO__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 用于屏幕或者命令行的命令处理
//	File Property : private
//	Description :	I. 负责一些屏幕或者命令行的命令处理
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"

namespace DRAGON
{
	class IO
	{
	public:
		IO(){}
		virtual ~IO(){}
	public:
		static int getProgramType();
	};
}	//DRAGON

#endif //__DRAGON_IO__
