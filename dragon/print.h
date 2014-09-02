#ifndef __DRAGON_PRINT__
#define __DRAGON_PRINT__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 用于屏幕打印
//	File Property : private
//	Description :	I. 负责屏幕提示信息的打印
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"

namespace DRAGON
{
	class Print
	{
	public:
		Print(){}
		virtual ~Print(){}
	public:
		static int welcome();
		static int choseProgramType();
		static int choseProgramTypeResult();
	};
}	//DRAGON

#endif //__DRAGON_PRINT__
