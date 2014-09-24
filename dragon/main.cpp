////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-9-2
//	Modify history :
//	File Property : private
//	Description :
//					I. 用于启动 dragon
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "io.h"

#include "ps_framework/_include.h"
#include "ps_framework/_thread.h"
#include "ps_framework/_thread_pool.h"

void* print1(void* arg)
{
	printf("\n[DRAGON::MAIN] Thread 1 create ! \n");

	while(1)
	{
		printf("\n[DRAGON::MAIN] Thread 1 wait 1000*6 ! \n");
		Sleep(1000*6);
	}

	return NULL;
}


void* print2(void* arg)
{
	printf("\n[DRAGON::MAIN] Thread 2 create ! \n");

	while(1)
	{
		printf("\n[DRAGON::MAIN] Thread 2 wait 1000*12 ! \n");
		Sleep(1000*12);
	}

	return NULL;
}


int main(int argc,char* argv[])
{
// 	DRAGON::IO::welcome();
// 	DRAGON::IO::choseProgramType();

// 	int iType = DRAGON::IO::getProgramType();
// 
// 	if (iType != 1 && iType != 2)
// 	{
// 		DRAGON::IO::choseProgramTypeResult();
// 		system("pause");
// 		return 0;
// 	}

	PS_FW::ThreadPool threadPool(5);

	threadPool.add(print1,NULL);
	threadPool.add(print2,NULL);

	system("pause");
}

