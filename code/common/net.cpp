/*
//
//	Last Modify Date: 2015-11-13
//	Author: zengpw
//	History:
//					2015-08-12 zengpw created
//	File Property: public
//	Future:
//					I. 网络接口
//
//
*/

#include "net.h"

namespace common
{
	Conn::Conn()
	{
		OnConnCbAddr = NULL;
		OnReadCbAddr = NULL;
		OnTimingCbAddr = NULL;
	}


	void Conn::init(const unsigned int conn_type, const char* ip, const unsigned int port)
	{
		this->conn_type = conn_type;

		bzero(&sAddrIn, sizeof(sAddrIn));
		sAddrIn.sin_family = AF_INET;

		if(ip != NULL)
		{
			inet_pton(AF_INET, ip, &sAddrIn.sin_addr);
		}

		sAddrIn.sin_port = htons(port);

		int outlen = sizeof(this->addr);
		memset(this->addr, 0, outlen);
		evutil_inet_ntop(AF_INET, (void*)&sAddrIn.sin_addr, this->addr, outlen);
	}


	void Conn::setConnCb(OnConnCb inConnCbAddr)
	{
		OnConnCbAddr = inConnCbAddr;
	}


	void Conn::setReadCb(OnReadCb inReadCbAddr)
	{
		OnReadCbAddr = inReadCbAddr;
	}


	void Conn::setTiming(struct timeval tv)
	{
		this->tv.tv_sec = tv.tv_sec;
		this->tv.tv_usec = tv.tv_usec;
	}


	void Conn::setTimingCb(OnTimingCb inTimingCbAddr)
	{
		OnTimingCbAddr = inTimingCbAddr;
	}


	void Conn::run()
	{
		if(conn_type & CONN_TYPE_LISTENER)
		{
			this->pEvbase = event_base_new();
			struct evconnlistener* pEvConn = evconnlistener_new_bind(this->pEvbase,
																	OnConnListenerCb,
																	(void*)this,
																	LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
																	-1,
																	(struct sockaddr*)&sAddrIn,
																	sizeof(struct sockaddr_in));

			if(!pEvConn)
			{
				LOG_DEBUG("server on " << addr << ":" << ntohs(sAddrIn.sin_port) << " fail");
				return;
			}

			LOG_DEBUG("server on " << addr << ":" << ntohs(sAddrIn.sin_port));
			evconnlistener_set_error_cb(pEvConn, OnConnListenerErrCb);
			event_base_dispatch(this->pEvbase);
			return;
		}

		if(conn_type & CONN_TYPE_CONNECTER)
		{
			this->pEvbase = event_base_new();
			this->pConnEvBuf = bufferevent_socket_new(this->pEvbase, -1, BEV_OPT_CLOSE_ON_FREE);
			bufferevent_setcb(this->pConnEvBuf, OnReadCbAddr, NULL, OnConnEventCb, (void*)this);

			if(bufferevent_socket_connect(this->pConnEvBuf, (struct sockaddr*)&sAddrIn, sizeof(struct sockaddr_in)) != 0)
			{
				LOG_DEBUG("conn on " << addr << ":" << ntohs(sAddrIn.sin_port) << " fail");
				bufferevent_free(this->pConnEvBuf);
				return;
			}

			LOG_DEBUG("conn on " << addr << ":" << ntohs(sAddrIn.sin_port));

			struct event* pEvent = NULL;
			evutil_socket_t fd = bufferevent_getfd(this->pConnEvBuf);

			if(fd != -1 && OnTimingCbAddr != NULL)
			{
				pEvent = event_new(this->pEvbase, fd, EV_PERSIST, OnTimingEventCb, (void*)this);
				event_add(pEvent, &this->tv);
			}

			bufferevent_enable(this->pConnEvBuf, EV_READ);
			event_base_dispatch(this->pEvbase);

			if(fd != -1 && OnTimingCbAddr != NULL)
			{
				event_del(pEvent);
			}

			return;
		}
	}


	void Conn::stop()
	{
		event_base_loopexit(this->pEvbase, NULL);
	}


	int Conn::recvMsg(struct bufferevent* pEvbuf, void* data, size_t size)
	{
		size_t n = bufferevent_read(pEvbuf, data, size);

		char c = '\0';
		for(int i = 0; i < n; i++)
		{
			if(memcmp(data + i, (void*)&c, 1) != 0)
			{
				//如果存在有效数据
				return 0;
			}
		}

		//读到的数据为全0
		// LOG_DEBUG("[hint] recvMsg() read " << size << " character '0' from buffer, skip!");
		return -1;
	}


	int Conn::sendMsg(struct bufferevent* pEvbuf, void* data, size_t size)
	{
		return bufferevent_write(pEvbuf, data, size);
	}


	void Conn::OnConnListenerCb(struct evconnlistener *evListener, evutil_socket_t evSocket, struct sockaddr *pAddrIn, int socklen, void *arg)
	{
		LOG_DEBUG("New connecter !");

		char addr[64];
		memset(addr, 0, socklen);
		struct sockaddr_in* sIn = (struct sockaddr_in*)pAddrIn;
		evutil_inet_ntop(AF_INET, (void*)&sIn->sin_addr, addr, socklen);

		LOG_DEBUG("Peer IP is " << addr);

		Conn *cn = (Conn*)arg;
		cn->connAddr.assign(addr, strlen(addr));
		struct bufferevent* pEvBuf = bufferevent_socket_new(cn->pEvbase, evSocket, BEV_OPT_CLOSE_ON_FREE);
		bufferevent_setcb(pEvBuf, cn->OnReadCbAddr, NULL, cn->OnConnEventCb, (void*)cn);
		bufferevent_enable(pEvBuf, EV_READ);
	}


	void Conn::OnConnListenerErrCb(struct evconnlistener *evListener, void *arg)
	{
		Conn *cn = (Conn*)arg;
		int err = EVUTIL_SOCKET_ERROR();
		LOG_DEBUG("Got an error " << err << "(" << evutil_socket_error_to_string(err) << ") on the listener! Program exit!");
		event_base_loopexit(cn->pEvbase, NULL);
	}


	void Conn::OnConnEventCb(struct bufferevent *bev, short what, void *conn)
	{
		LOG_DEBUG("BEV_EVENT = 0x" << hex << setiosflags(ios::uppercase) << setfill('0') << setw(2) << what);

		Conn *cn = (Conn*)conn;

		if(what & BEV_EVENT_ERROR)
		{
			LOG_DEBUG("Error from bufferevent! BEV_EVENT = BEV_EVENT_ERROR");

			bufferevent_free(bev);
			if(cn->conn_type & CONN_TYPE_CONNECTER)
				event_base_loopexit(cn->pEvbase, NULL);

			return;
		}

		if(what & BEV_EVENT_EOF)
		{
			LOG_DEBUG("BEV_EVENT = BEV_EVENT_EOF");
			LOG_DEBUG("peer connecter disconnect");

			bufferevent_free(bev);
			if(cn->conn_type & CONN_TYPE_CONNECTER)
				event_base_loopexit(cn->pEvbase, NULL);

			return;
		}

		if(what & BEV_EVENT_CONNECTED)
		{
			cn->OnConnCbAddr(bev, conn);
			return;
		}
	}


	void Conn::OnTimingEventCb(evutil_socket_t fd, short events, void* conn)
	{
		Conn *cn = (Conn*)conn;
		cn->OnTimingCbAddr(cn->pConnEvBuf, conn);
	}
};// namespace common
