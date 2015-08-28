/*
//
//	Last Modify Date: 2015-08-28
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
	common::Conn* conn = new common::Conn;

	conn->init(common::CONN_TYPE_LISTENER);
	conn->setPort(21000);
	conn->setDataHandleCb(OnDataHandleCb);
	conn->run();

	return 0;
}


void OnDataHandleCb(void* conn, struct bufferevent* pEvbuf, int conn_event)
{
	printf("\n conn_event = %d\n", conn_event);

	common::Conn* cn = (common::Conn*)conn;

	if(conn_event & common::CONN_EVENT_READ)
	{
		protocol::Packet *in = new protocol::Packet;
		protocol::Packet *out = new protocol::Packet;

		unsigned int len = sizeof(protocol::data::Head);

		if(!cn->recvMsg(pEvbuf, (void*)in->setBuffer(len), len))
		{
			len = in->parseHead();

			if(len > 0)
			{
				if(!cn->recvMsg(pEvbuf, (void*)in->setBuffer(len), len))
				{
					if(!in->parse())
					{
						BalanceHandle* balanceHandle = new BalanceHandle;
						balanceHandle->dispatch(in, out);

						cn->sendMsg(pEvbuf, (void*)out->raw(), out->len());
					}
				}
			}
		}

		delete in;
		delete out;
		return;
	}

	if(conn_event & common::CONN_EVENT_WRITE)
	{
		printf("\n CONN_EVENT_WRITE! \n");
	}

	return;
}
