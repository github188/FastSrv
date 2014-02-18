#include "../ps_api.hpp"
#include "unistd.h"

int main()
{
	int fd = 0;

	fd = socket_open("127.0.0.1",42890);
	printf("\n==============fd: %d",fd);
	printf("\n");
}
