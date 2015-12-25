/*
//
//	Last Modify Date: 2015-12-25
//	Author: zengpw
//	History:
//					2015-09-01 zengpw created
//	File Property: private
//	Future:
//					I. 心跳线程，报文基于 protobuf
//
//
*/

#include "heartbeat.h"

namespace session
{
	// for assign
	node& node::operator=(const node& n)
	{
		if(*this == n)
		{
			this->load = n.load;
			this->live_time = n.live_time;

			return *this;
		}

		this->ip = n.ip;
		this->port = n.port;
		this->load = n.load;
		this->live_time = n.live_time;

		return *this;
	}

	// for compare
	bool node::operator!=(const node& n) const
	{
		return (this->ip != n.ip || this->port != n.port);
	}

	// for stl find
	bool node::operator==(const node& n) const
	{
		return (this->ip == n.ip && this->port == n.port);
	}

	// for stl sort
	bool node::operator<(const node& n) const
	{
		return (this->load < n.load);
	}

	HeartBeat* HeartBeat::hb = NULL;

	HeartBeat* HeartBeat::create(const unsigned int port, common::Thread* th)
	{
		if(hb == NULL)
		{
			hb = new HeartBeat;
			hb->port = port;
			hb->th = th;
			hb->lock = PTHREAD_MUTEX_INITIALIZER;
			hb->th->create(master, (void*)hb);
		}

		return hb;
	}

	HeartBeat* HeartBeat::create(const char* ip, const unsigned int port, const unsigned int interval, const unsigned int self_port, common::Thread* th)
	{
		if(hb == NULL)
		{
			hb = new HeartBeat;
			strcpy(hb->ip, ip);
			hb->port = port;
			hb->interval = interval;
			hb->self_port = self_port;
			hb->th = th;
			hb->lock = PTHREAD_MUTEX_INITIALIZER;
			hb->load = 0;
			hb->th->create(slave, (void*)hb);
		}

		return hb;
	}

	HeartBeat* HeartBeat::instance()
	{
		return hb;
	}

	void* HeartBeat::master(void* self)
	{
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		HeartBeat* se = (HeartBeat*)self;
		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_LISTENER, NULL, se->port);
		conn->setReadCb(OnMasterReadCb);
		conn->extra = self;
		conn->run();

		google::protobuf::ShutdownProtobufLibrary();

		return NULL;
	}

	void* HeartBeat::slave(void* self)
	{
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		HeartBeat* se = (HeartBeat*)self;
		common::Conn* conn = new common::Conn;
		conn->init(common::CONN_TYPE_CONNECTER, se->ip, se->port);
		conn->setConnCb(OnSlaveConnCb);
		conn->setReadCb(OnSlaveReadCb);

		struct timeval tv;
		tv.tv_sec = se->interval;
		tv.tv_usec = 0;

		conn->setTiming(tv);
		conn->setTimingCb(OnSlaveTimingCb);
		conn->extra = self;

		while(true)
		{
			conn->run();
			LOG_DEBUG("Heartbeat : Master not find. Slave sleep 5 Seconds.");
			sleep(5);
		}

		google::protobuf::ShutdownProtobufLibrary();

		return NULL;
	}

	void HeartBeat::OnMasterReadCb(struct bufferevent *bev, void *conn)
	{
		// LOG_DEBUG("Heartbeat : OnMasterReadCb!");
		common::Conn* cn = (common::Conn*)conn;
		HeartBeat* se = (HeartBeat*)cn->extra;

		for(;;)
		{
			protocol::pb::PacketPB *in = new protocol::pb::PacketPB;

			int len = sizeof(protocol::pb::Head);

			if(cn->recvMsg(bev, (void*)in->setHead(), len) == 0)
			{
				len = in->parseHead();

				if(len > 0)
				{
					if(cn->recvMsg(bev, (void*)in->setBody(len), len) == 0)
					{
						string input;

						if(!in->parseBody(input))
						{
							protocol::pb::HeartBeat hb;
							hb.ParseFromString(input);

							node n;
							n.ip = cn->connAddr;
							n.port = hb.port();
							n.load = hb.load();
							n.live_time = common::buildDateTimeSecond();

							LOG_DEBUG("Heartbeat : [ task connect : ip = " << n.ip << ", port = " << n.port << ", load = " << n.load << ", live_time = " << n.live_time << " ]");
							se->push(n);
						}
						else
						{
							delete in;
							return;
						}
					}
					else
					{
						delete in;
						return;
					}
				}
				else
				{
					delete in;
					return;
				}
			}
			else
			{
				delete in;
				return;
			}

			delete in;
		}

		return;
	}

	void HeartBeat::OnSlaveConnCb(struct bufferevent *bev, void *conn)
	{
		// LOG_DEBUG("Heartbeat : OnSlaveConnCb!");
		common::Conn* cn = (common::Conn*)conn;
		HeartBeat* se = (HeartBeat*)cn->extra;

		protocol::pb::HeartBeat hb;
		hb.set_port(se->self_port);
		hb.set_load(se->get());

		string output;
		if(hb.SerializeToString(&output))
		{
			protocol::pb::PacketPB *out = new protocol::pb::PacketPB;
			out->build(output, output.length());
			cn->sendMsg(bev, (void*)out->getMsg(), out->getMsgLen());
			delete out;
		}
	}

	void HeartBeat::OnSlaveTimingCb(struct bufferevent *bev, void *conn)
	{
		// LOG_DEBUG("Heartbeat : OnSlaveTimingCb!");
		common::Conn* cn = (common::Conn*)conn;
		HeartBeat* se = (HeartBeat*)cn->extra;

		protocol::pb::HeartBeat hb;
		hb.set_port(se->self_port);
		hb.set_load(se->get());

		string output;
		if(hb.SerializeToString(&output))
		{
			protocol::pb::PacketPB *out = new protocol::pb::PacketPB;
			out->build(output, output.length());
			cn->sendMsg(bev, (void*)out->getMsg(), out->getMsgLen());
			delete out;
		}
	}

	void HeartBeat::OnSlaveReadCb(struct bufferevent *bev, void *conn)
	{
		// LOG_DEBUG("Heartbeat : OnSlaveReadCb!");
		return;
	}

	void HeartBeat::incr(unsigned int load)
	{
		pthread_mutex_lock(&this->lock);
		this->load += load;
		pthread_mutex_unlock(&this->lock);
	}

	void HeartBeat::decr(unsigned int load)
	{
		pthread_mutex_lock(&this->lock);
		this->load -= load;
		pthread_mutex_unlock(&this->lock);
	}

	unsigned int HeartBeat::get()
	{
		int n = 0;

		pthread_mutex_lock(&this->lock);
		n = this->load;
		pthread_mutex_unlock(&this->lock);

		return n;
	}

	void HeartBeat::push(node& n)
	{
		pthread_mutex_lock(&this->lock);

		nodeVec::iterator iter = std::find(vn.begin(), vn.end(), n);

		if(iter != vn.end())
		{
			*iter = n;
		}
		else
		{
			vn.push_back(n);
		}

		pthread_mutex_unlock(&this->lock);
	}

	node HeartBeat::pop()
	{
		node n;

		n.ip = "0.0.0.0";
		n.port = 0;
		n.load = 0;

		pthread_mutex_lock(&this->lock);

		long long dt = common::buildDateTimeSecond();

		nodeVec::iterator iter = vn.begin();
		for(; iter != vn.end(); )
		{
			if(dt - iter->live_time > 60)
			{
				iter = vn.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		LOG_DEBUG("----------------- server list ");

		nodeMap nm;

		for(iter = vn.begin(); iter != vn.end(); ++iter)
		{
			LOG_DEBUG("ip = " << iter->ip << ", port = " << iter->port << ", load = " << iter->load << ", live_time = " << iter->live_time);
			nm.insert(std::make_pair(iter->load, *iter));
		}

		if(nm.size() > 0)
		{
			n = nm.begin()->second;
		}

		pthread_mutex_unlock(&this->lock);

		return n;
	}
};// namespace session
