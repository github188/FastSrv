/*
//
//	Last Modify Date: 2015-11-13
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


	void Session::startNoThread()
	{
		if(session_type == SESSION_TYPE_LISTENER)
			listenerCb((void*)this);

		if(session_type == SESSION_TYPE_CONNECTER)
			connecterCb((void*)this);
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
			{
				cn->sendMsg(bev, (void*)out->getMsg(), out->getMsgLen());
				LOG_DEBUG("Session -> OnConnCb() send message!");
			}

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

		for(;;)
		{
			protocol::PacketIn *in = new protocol::PacketIn;
			protocol::PacketOut *out = new protocol::PacketOut;

			int len = sizeof(protocol::tlv::Head);

			if(cn->recvMsg(bev, (void*)in->setHead(), len) == 0)
			{
				LOG_DEBUG("[hint] new message coming");

				len = in->parseHead();

				if(len > 0)
				{
					if(cn->recvMsg(bev, (void*)in->setBody(), len) == 0)
					{
						if(!in->parseBody())
						{
							try
							{
								//解析上行消息
								int rtn = hb->dispatch(in, out);

								if(rtn == HANDLE_RTN_SEND)
								{
									cn->sendMsg(bev, (void*)out->getMsg(), out->getMsgLen());
									LOG_DEBUG("Session -> OnReadCb() -> dispatch() send message!");
								}

								if(rtn == HANDLE_RTN_CONTINUE)
									LOG_DEBUG("Session -> OnReadCb() -> dispatch() return continue!");

								if(rtn == HANDLE_RTN_STOP)
									cn->stop();

								//查询下发消息
								vector<protocol::PacketOut> vp;

								if(hb->sending(in, vp) == HANDLE_RTN_SEND)
								{
									LOG_DEBUG("[hint] " << vp.size() << " message ready to send!");
									for(int i = 0; i < vp.size(); i++)
									{
										cn->sendMsg(bev, (void*)vp[i].getMsg(), vp[i].getMsgLen());
										LOG_DEBUG("Session -> OnReadCb() -> dispatch() sending!");
									}
								}
							}
							catch(...)
							{
								LOG_DEBUG("Session -> OnReadCb() -> dispatch() throw exception!");
								return;
							}
						}
						else
						{
							if(hb->reject(in, out) == HANDLE_RTN_SEND)
							{
								cn->sendMsg(bev, (void*)out->getMsg(), out->getMsgLen());
								LOG_DEBUG("parse message fail, send reject msg!");
							}

							return;
						}
					}
					else
						return;
				}
				else
					return;
			}
			else
				return;

			delete in;
			delete out;
		}

		return;
	}
};// namespace session
