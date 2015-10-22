/*
//
//	Last Modify Date: 2015-10-12
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
	Session::Session(const unsigned int session_type, const char* ip, unsigned int port, common::Thread* th, HandleBasic* hb)
	{
		this->session_type = session_type;

		if(ip != NULL)
			strcpy(addr, ip);

		this->port = port;
		this->th = th;
		this->hb = hb;
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
		conn->extra = se->hb;
		conn->run();
	}


	void* Session::connecterCb(void* self)
	{
		Session* se = (Session*)self;
		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_CONNECTER, se->addr, se->port);
		conn->setConnCb(se->OnConnCb);
		conn->setReadCb(se->OnReadCb);
		conn->extra = se->hb;
		conn->run();
	}


	void Session::OnConnCb(struct bufferevent *bev, void *conn)
	{
		common::Conn* cn = (common::Conn*)conn;
		HandleBasic* hb = (HandleBasic*)cn->extra;

		protocol::PacketOut* out = new protocol::PacketOut;

		try
		{
			int rtn = hb->conn(out);

			if(rtn == HANDLE_RTN_SEND)
				cn->sendMsg(bev, (void*)out->getMsg(), out->getMsgLen());

			if(rtn == HANDLE_RTN_STOP)
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
		HandleBasic* hb = (HandleBasic*)cn->extra;

		protocol::PacketIn *in = new protocol::PacketIn;
		protocol::PacketOut *out = new protocol::PacketOut;

		unsigned int len = sizeof(protocol::tlv::Head);

		if(!cn->recvMsg(bev, (void*)in->setHead(), len))
		{
			LOG_DEBUG("[hint] new message coming");

			len = in->parseHead();

			if(len > 0)
			{
				if(!cn->recvMsg(bev, (void*)in->setBody(), len))
				{
					//此处调用 HandleBasic 来处理，具体怎么做交给调用方

					if(!in->parseBody())
					{
						try
						{
							int rtn = hb->dispatch(in, out);

							if(rtn == HANDLE_RTN_SEND)
								cn->sendMsg(bev, (void*)out->getMsg(), out->getMsgLen());

							if(rtn == HANDLE_RTN_CONTINUE)
								LOG_DEBUG("Session -> OnReadCb() -> dispatch() rtn continue!");

							if(rtn == HANDLE_RTN_STOP)
								cn->stop();
						}
						catch(...)
						{
							LOG_DEBUG("Session -> OnReadCb() -> dispatch() throw exception!");
						}
					}
					else
						cn->stop();
				}
				else
					cn->stop();
			}
			else
			{
				LOG_DEBUG("Session -> OnReadCb() -> parseHead error !");
				cn->stop();
			}
		}

		delete in;
		delete out;

		return;
	}
};// namespace session
