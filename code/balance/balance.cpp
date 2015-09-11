/*
//
//	Last Modify Date: 2015-09-02
//	Author: zengpw
//	History:
//					2015-08-12 zengpw created
//	File Property: private
//	Future:
//					I. 负载均衡
//
//
*/

#include "balance.h"

int main()
{
	common::Thread* thread = new common::Thread;

	if(thread->create(threadCb, NULL) != 0)
	{
		printf("\n create thread error \n");
		return 0;
	}

	common::HeartBeat* heartBeat = new common::HeartBeat;

	if(thread->create(heartBeat->master, NULL) != 0)
	{
		printf("\n create thread error \n");
		return 0;
	}

	thread->join();

	return 0;
}


void* threadCb(void* arg)
{
	common::Conn* conn = new common::Conn;

	conn->init(common::CONN_TYPE_LISTENER, NULL, 21000);
	conn->setReadCb(OnReadCb);
	conn->run();
}


void OnReadCb(struct bufferevent *bev, void *conn)
{
	common::Conn* cn = (common::Conn*)conn;

	protocol::Packet *in = new protocol::Packet;
	protocol::Packet *out = new protocol::Packet;

	unsigned int len = sizeof(protocol::data::Head);

	if(!cn->recvMsg(bev, (void*)in->setBuffer(len), len))
	{
		len = in->parseHead();

		if(len > 0)
		{
			if(!cn->recvMsg(bev, (void*)in->setBuffer(len), len))
			{
				if(!in->parse())
				{
					BalanceHandle* balanceHandle = new BalanceHandle;
					balanceHandle->dispatch(in, out);

					cn->sendMsg(bev, (void*)out->raw(), out->len());
				}
			}
		}
	}

	delete in;
	delete out;

	return;
}
