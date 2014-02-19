/* 测试server端的例子,makefile统一在cmake目录下 */
#include "../ps_api.hpp"

int main()
{
	int fd = 0;

	fd = socket_open("127.0.0.1",42890);
	printf("\n==============fd: %d",fd);
	printf("\n");
}
