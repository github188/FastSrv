/*
//
//	Last Modify Date: 2015-08-28
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
	int Conn::init(unsigned int in_conn_type)
	{
		conn_type = in_conn_type;

		return 0;
	}


	int Conn::setPort(unsigned int in_port)
	{
		port = in_port;

		return 0;
	}


	void Conn::setDataHandleCb(dataHandleCb inDataHandleCb)
	{
		OnDataHandleCb = inDataHandleCb;
	}


	int Conn::run()
	{
		printf("\n conn_type = %d\n", conn_type);

		if(conn_type & CONN_TYPE_LISTENER)
		{
			struct sockaddr_in sAddrIn;
			bzero(&sAddrIn, sizeof(sAddrIn));
			sAddrIn.sin_family = AF_INET;
			// inet_ntop(AF_INET, ip, &sAddrIn.sin_addr, INET_ADDRSTRLEN);
			sAddrIn.sin_port = htons(port);

			this->pEvbase = event_base_new();
			this->pEvConn = evconnlistener_new_bind(this->pEvbase,OnConnListenerCb,(void*)this,LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,-1,(struct sockaddr*)&sAddrIn,sizeof(struct sockaddr_in));

			if(!this->pEvConn)
			{
				printf("\n server on %d fail \n", port);
				return -1;
			}

			evconnlistener_set_error_cb(this->pEvConn,OnConnListenerErrCb);
			printf("\n server on %d\n", port);

			event_base_dispatch(this->pEvbase);

			return 0;
		}

		if(conn_type & CONN_TYPE_CONNECTER)
		{

		}

		return 0;
	}


	int Conn::recvMsg(struct bufferevent* pEvbuf, void* data, size_t size)
	{
		size_t n = bufferevent_read(pEvbuf, data, size);

		return 0;
	}


	int Conn::sendMsg(struct bufferevent* pEvbuf, void* data, size_t size)
	{
		return bufferevent_write(pEvbuf, data, size);
	}


	void Conn::OnConnListenerCb(struct evconnlistener *evListener, evutil_socket_t evSocket, struct sockaddr *pAddrIn, int socklen, void *arg)
	{
		Conn *cn = (Conn*)arg;
		printf("\n New connecter arriving! \n");

		evutil_socket_t evSocketId = evSocket;
		struct bufferevent* pEvBuf = bufferevent_socket_new(cn->pEvbase, evSocketId, BEV_OPT_CLOSE_ON_FREE);
		bufferevent_setcb(pEvBuf, cn->OnReadCb, NULL, cn->OnConnBuffereventErrCb, (void*)cn);
		bufferevent_enable(pEvBuf, EV_READ | EV_WRITE);
	}


	void Conn::OnConnListenerErrCb(struct evconnlistener *evListener, void *arg)
	{
		Conn *cn = (Conn*)arg;

		int err = EVUTIL_SOCKET_ERROR();
		printf("\n Got an error %d(%s) on the listener! Program exit! \n", err, evutil_socket_error_to_string(err));
		event_base_loopexit(cn->pEvbase, NULL);
	}


	void Conn::OnConnBuffereventErrCb(struct bufferevent *bev, short what, void *ctx)
	{
		Conn *cn = (Conn*)ctx;

		if(what & BEV_EVENT_ERROR)
			printf("\n Error from bufferevent! BEV_EVENT = BEV_EVENT_ERROR \n");

		if(what & (BEV_EVENT_EOF | BEV_EVENT_ERROR))
		{
			printf("\n Error from bufferevent! BEV_EVENT = %d, call bufferevent_free() \n",what);
			bufferevent_free(bev);
		}
	}


	void Conn::OnReadCb(struct bufferevent *bev, void *ctx)
	{
		printf("\n New msg arriving! \n");
		Conn *cn = (Conn*)ctx;
		cn->OnDataHandleCb(ctx, bev, CONN_EVENT_READ);
	}


	void Conn::OnWriteCb(struct bufferevent *bev, void *ctx)
	{
		Conn *cn = (Conn*)ctx;
		cn->OnDataHandleCb(ctx, bev, CONN_EVENT_WRITE);
	}
};// namespace common
