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

#include "io.h"

namespace DRAGON
{
	int IO::welcome()
	{
		printf("\n");
		printf("==================================================\n");
		printf("=                                                =\n");
		printf("=    Dragon                                      =\n");
		printf("=      v 0.01                                    =\n");
		printf("=                                                =\n");
		printf("==================================================\n");
		printf("\n");

		return 0;
	}


	int IO::choseProgramType()
	{
		printf("\n");
		printf("==================================================\n");
		printf("=                                                =\n");
		printf("=    please chose the program type               =\n");
		printf("=                                                =\n");
		printf("=    1.  server                                  =\n");
		printf("=    2.  client                                  =\n");
		printf("=                                                =\n");
		printf("==================================================\n");
		printf("\n");

		return 0;
	}


	int IO::choseProgramTypeResult()
	{
		printf("\n");
		printf("=    must be press 1 or 2 \n");
		printf("\n");

		return 0;
	}


	int IO::getProgramType()
	{
		int iType = 0;
		scanf("%d",&iType);
		return iType;
	}
}	//DRAGON

