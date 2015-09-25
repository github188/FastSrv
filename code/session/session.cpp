/*
//
//	Last Modify Date: 2015-09-25
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
	Session::Session(const unsigned int session_type, const char* ip, unsigned int port, common::Thread* th, SessionHandle* sh)
	{
		this->session_type = session_type;

		if(ip != NULL)
			strcpy(addr, ip);

		this->port = port;
		this->th = th;
		this->sh = sh;
	}


	void Session::start()
	{
		if(session_type == SESSION_TYPE_LISTENER)
			th->create(listenerCb, (void*)this);

		if(session_type == SESSION_TYPE_CONNECTER)
			th->create(connecterCb, (void*)this);
	}


	void* Session::listenerCb(void* self)
	{
		Session* se = (Session*)self;
		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_LISTENER, NULL, se->port);
		conn->setReadCb(se->OnReadCb);
		conn->extra = se->sh;
		conn->run();
	}


	void* Session::connecterCb(void* self)
	{
		Session* se = (Session*)self;
		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_CONNECTER, se->addr, se->port);
		conn->setConnCb(se->OnConnCb);
		conn->setReadCb(se->OnReadCb);
		conn->extra = se->sh;
		conn->run();
	}


	void Session::OnConnCb(struct bufferevent *bev, void *conn)
	{
		common::Conn* cn = (common::Conn*)conn;
		SessionHandle* sh = (SessionHandle*)cn->extra;

		protocol::Packet *out = new protocol::Packet;

		try
		{
			int rtn = sh->conn(out);

			if(rtn == SESSION_RTN_SEND)
				cn->sendMsg(bev, (void*)out->raw(), out->len());

			if(rtn == SESSION_RTN_STOP)
				cn->stop();
		}
		catch(...)
		{
			LOG_DEBUG("Message conn() throw exception!");
		}

		delete out;
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
					//此处调用 sessionHandle 来处理，具体怎么做交给调用方

					if(!in->parse())
					{
						try
						{
							int rtn = sh->dispatch(in, out);

							if(rtn == SESSION_RTN_SEND)
								cn->sendMsg(bev, (void*)out->raw(), out->len());

							if(rtn == SESSION_RTN_STOP)
								cn->stop();
						}
						catch(...)
						{
							LOG_DEBUG("Message dispatch() throw exception!");
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
