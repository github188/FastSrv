#include "../ps_api.hpp"
#include "unistd.h"

int main()
{
	if(socket_create("127.0.0.1",42890) != 0)
	{
		printf("\n==============127.0.0.1 error !");
	}

	printf("\n");
	sleep(100);
}
