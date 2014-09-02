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

#include "io.h"

namespace DRAGON
{
	int IO::getProgramType()
	{
		int iType = 0;
		scanf("%d",&iType);
		return iType;
	}
}	//DRAGON

