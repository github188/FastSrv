#include "../thread_pool.hpp"

typedef struct
{
	int socket;
	int msg;
} msgbox;

int main()
{
	int iReturn = PURE_SERVER::THREAD_POOL::launch();
}
