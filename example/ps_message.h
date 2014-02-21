
typedef struct st_head
{
	char auth[10];			/*客户端名字*/
	char version[10];		/*客户端版本*/
} st_head;

typedef struct st_body
{
	char question[100];		/*客户端询问*/
	char answer[100];		/*服务端回答*/
} st_body;

