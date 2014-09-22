#ifndef __DRAGON_IO__
#define __DRAGON_IO__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-9-2
//	Modify history :
//					2014-9-2 zengpw 用于屏幕或者命令行的命令处理
//					2014-9-18 zengpw 重新设计
//	File Property : private
//	Description :
//					I. 负责一些屏幕或者命令行的命令处理
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
		// print
		static int welcome();
		static int choseProgramType();
		static int choseProgramTypeResult();
	public:
		// input
		static int getProgramType();
	};
}	//DRAGON

#endif //__DRAGON_IO__
