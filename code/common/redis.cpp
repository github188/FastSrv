/*
//
//	Last Modify Date: 2015-09-24
//	Author: zengpw
//	History:
//					2015-09-17 zengpw created
//	File Property: public
//	Future:
//					I. redis 接口
//
//
*/

#include "redis.h"

namespace common
{
	Redis::Redis(string ip, unsigned int port)
	{
		this->ip = ip;
		this->port = port;
		this->c = NULL;
	}


	int Redis::redis_conn()
	{
		if(this->c != NULL)
		{
			redisFree(c);
		}

		this->c = redisConnect(this->ip.c_str(), this->port);

		if(this->c == NULL || this->c->err)
		{
			LOG_DEBUG("redis connect error");
			return -1;
		}

		return 0;
	}


	int Redis::redis_lpush(const char* key, const char* value, const int length)
	{
		LOG_DEBUG("redis key : " << key);
		LOG_DEBUG("redis value : ");
		common::printByHex(value, length);

		redisReply* r = (redisReply*)redisCommand(c, "LPUSH %s %b", key, value, (size_t)length);

		if(r == NULL || r->type == REDIS_REPLY_ERROR || (r->type == REDIS_REPLY_STATUS && r->str != REDIS_OK))
		{
			LOG_DEBUG("redis LPUSH error");
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_INTEGER)
		{
			LOG_DEBUG("redis LPUSH return ok, list size is " << r->integer);
			freeReplyObject(r);
		}

		return 0;
	}


	int Redis::redis_rpoplpush(const char* key_src, const char* key_dest, char* value, int* len)
	{
		LOG_DEBUG("RPOPLPUSH " << key_src << " " << key_dest);

		redisReply* r = (redisReply*)redisCommand(c, "RPOPLPUSH %s %s", key_src, key_dest);

		if(r == NULL || r->type == REDIS_REPLY_ERROR || (r->type == REDIS_REPLY_STATUS && r->str != REDIS_OK))
		{
			LOG_DEBUG("redis RPOPLPUSH error");
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_NIL)
		{
			LOG_DEBUG("redis RPOPLPUSH return ok, list size is empty!");
			freeReplyObject(r);
			return 1;
		}

		if(r->type == REDIS_REPLY_STRING)
		{
			LOG_DEBUG("redis RPOPLPUSH return ok, value = ");
			common::printByHex(r->str, r->len);

			//copy to return value
			memcpy(value, r->str, r->len);
			*len = r->len;

			freeReplyObject(r);
		}

		return 0;
	}


	int Redis::redis_hset(const string& key, const string& field, const string& value)
	{
		LOG_DEBUG("redis key : " << key.c_str());
		LOG_DEBUG("redis field : " << field.c_str());
		LOG_DEBUG("redis value : " << value.c_str());

		const char* chKey = key.c_str();
		const char* chColumn = field.c_str();
		const char* chValue = value.c_str();

		redisReply* r = (redisReply*)redisCommand(c, "HSET %s %s %s", chKey, chColumn, chValue);

		if(r == NULL || (r->type == REDIS_REPLY_STATUS && r->str != REDIS_OK))
		{
			LOG_DEBUG("redis HSET error");
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_INTEGER && (r->integer == 1 || r->integer == 0))
		{
			LOG_DEBUG("redis HSET return ok");
			freeReplyObject(r);
		}
		else
		{
			LOG_DEBUG("redis HSET integer not equal 1 or 2");
			freeReplyObject(r);
			return -1;
		}

		return 0;
	}


	int Redis::redis_expire(const string& key, const string& second)
	{
		// 691200 = 60*60*24*8
		const char* chKey = key.c_str();
		const char* chExpire = second.c_str();

		redisReply* r = (redisReply*)redisCommand(c, "EXPIRE %s %s", chKey, chExpire);

		if(r == NULL || (r->type == REDIS_REPLY_STATUS && r->str != REDIS_OK))
		{
			LOG_DEBUG("redis EXPIRE error");
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_INTEGER && r->integer == 1)
		{
			LOG_DEBUG("redis EXPIRE ok");
			freeReplyObject(r);
		}
		else
		{
			LOG_DEBUG("redis EXPIRE integer not equal");
			freeReplyObject(r);
			return -1;
		}

		return 0;
	}


	int Redis::redis_hget(const string& key, const string& field, string& value)
	{
		LOG_DEBUG("redis key : " << key.c_str());
		LOG_DEBUG("redis field : " << field.c_str());

		const char* chKey = key.c_str();
		const char* chColumn = field.c_str();

		redisReply* r = (redisReply*)redisCommand(c, "HGET %s %s", chKey, chColumn);

		if(r == NULL || (r->type == REDIS_REPLY_NIL))
		{
			LOG_DEBUG("redis HGET error , field not exist");
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_STRING)
		{
			value = string(r->str);
			freeReplyObject(r);
		}
		else
		{
			LOG_DEBUG("redis HGET error, return type is not string");
			freeReplyObject(r);	
			return -1;
		}

		return 0;
	}


	int Redis::redis_keys(const string& vkey, vector<string>& value)
	{
		LOG_DEBUG("redis search vkey : " << vkey.c_str());

		const char* chKey = vkey.c_str();

		redisReply* r = (redisReply*)redisCommand(c, "KEYS %s", chKey);

		if(r == NULL)
		{
			LOG_DEBUG("KEYS error , vkey not exist : " << vkey.c_str());
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_NIL || r->type == REDIS_REPLY_ERROR)
		{
			LOG_DEBUG("KEYS return , no data found : " << vkey.c_str());
			freeReplyObject(r);
			return 0;
		}

		if((r->type == REDIS_REPLY_STATUS && r->str != REDIS_OK) || r->type != REDIS_REPLY_ARRAY)
		{
			LOG_DEBUG("KEYS error , vkey not exist : " << vkey.c_str());
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_ARRAY)
		{
			for(int i = 0; i < r->elements; i++)
			{
				redisReply* rt = r->element[i];

				if(rt == NULL)
				{
					continue;
				}

				if(rt->type == REDIS_REPLY_STRING)
				{
					char subKey[64];
					memset(subKey,0,64);
					memcpy(subKey,rt->str,rt->len);

					value.push_back(string(subKey));
				}
			}
		}

		LOG_DEBUG("KEYS return ok , search vkeys : " << vkey.c_str() << " , result size : " << value.size());
		freeReplyObject(r);

		return 0;
	}
};// namespace common