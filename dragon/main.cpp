////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 创建 dragon 入口函数
//	File Property : private
//	Description :	I. 用于启动 dragon
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "ps_framework/_app.h"
#include "print.h"
#include "io.h"

int main(int argc,char* argv[])
{
	DRAGON::Print::welcome();
	DRAGON::Print::choseProgramType();

	int iType = DRAGON::IO::getProgramType();

	if (iType != 1 && iType != 2)
	{
		DRAGON::Print::choseProgramTypeResult();
		system("pause");
		return 0;
	}

	PS_FW::App* pApp = new PS_FW::App;

	if (iType == 1)
	{
		pApp->startServer("127.0.0.1",20001);
	}

	if (iType == 2)
	{
		pApp->startConn("127.0.0.1",20001);
	}

	pApp->join();

	system("pause");
}

