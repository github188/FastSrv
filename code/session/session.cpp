/*
//
//	Last Modify Date: 2015-09-16
//	Author: zengpw
//	History:
//					2015-09-15 zengpw created
//	File Property: public
//	Future:
//					I. 进一步封装 net层 和 protocol层
//
//
*/

#include "session.h"

namespace session
{
	Session::Session(common::Thread* th, common::Config* cfg, SessionHandle* sh)
	{
		this->th = th;
		this->cfg = cfg;
		this->sh = sh;
	}


	void Session::start()
	{
		th->create(listenerCb, (void*)this);
	}


	void* Session::listenerCb(void* arg)
	{
		Session* se = (Session*)arg;
		unsigned int port = atoi(se->cfg->get('p').c_str());

		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_LISTENER, NULL, port);
		conn->setReadCb(se->OnReadCb);
		conn->extra = se->sh;
		conn->run();
	}


	void Session::OnReadCb(struct bufferevent *bev, void *conn)
	{
		common::Conn* cn = (common::Conn*)conn;
		SessionHandle* sh = (SessionHandle*)cn->extra;

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
					// TODO 将 head 和 body 拿到手以后，先存入 redis 0
					if(!in->parse())
					{
						try
						{
							if(sh->dispatch(in, out))
							{
								cn->sendMsg(bev, (void*)out->raw(), out->len());
							}
						}
						catch(...)
						{
							printf("\n Message dispatch() throw exception! \n");
						}
					}
				}
			}
		}

		delete in;
		delete out;

		return;
	}
};// namespace session
