/*
//
//	Last Modify Date: 2015-09-17
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
			printf("\n redis connect error \n");
			return -1;
		}

		return 0;
	}


	int Redis::redis_hset(const std::string& key, const std::string& field, const std::string& value)
	{
		printf("\n redis key :   %s \n", key.c_str());
		printf("\n redis field : %s \n", field.c_str());
		printf("\n redis value : %s \n", value.c_str());

		const char* chKey = key.c_str();
		const char* chColumn = field.c_str();
		const char* chValue = value.c_str();

		redisReply* r = (redisReply*)redisCommand(c, "HSET %s %s %s", chKey, chColumn, chValue);

		if(r == NULL || (r->type == REDIS_REPLY_STATUS && r->str != REDIS_OK))
		{
			printf("\n redis HSET error \n");
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_INTEGER && (r->integer == 1 || r->integer == 0))
		{
			printf("\n redis HSET return ok \n");
			freeReplyObject(r);
		}
		else
		{
			printf("\n redis HSET integer not equal 1 or 2 \n");
			freeReplyObject(r);
			return -1;
		}

		return 0;
	}


	int Redis::redis_expire(const std::string& key, const std::string& second)
	{
		// 691200 = 60*60*24*8
		const char* chKey = key.c_str();
		const char* chExpire = second.c_str();

		redisReply* r = (redisReply*)redisCommand(c, "EXPIRE %s %s", chKey, chExpire);

		if(r == NULL || (r->type == REDIS_REPLY_STATUS && r->str != REDIS_OK))
		{
			printf("\n redis EXPIRE error \n");
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_INTEGER && r->integer == 1)
		{
			printf("\n redis EXPIRE ok \n");
			freeReplyObject(r);
		}
		else
		{
			printf("\n redis EXPIRE integer not equal \n");
			freeReplyObject(r);
			return -1;
		}

		return 0;
	}


	int Redis::redis_hget(const std::string& key, const std::string& field, std::string& value)
	{
		printf("\n redis key :   %s \n", key.c_str());
		printf("\n redis field : %s \n", field.c_str());

		const char* chKey = key.c_str();
		const char* chColumn = field.c_str();

		redisReply* r = (redisReply*)redisCommand(c, "HGET %s %s", chKey, chColumn);

		if(r == NULL || (r->type == REDIS_REPLY_NIL))
		{
			printf("\n redis HGET error , field not exist \n");
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_STRING)
		{
			value = std::string(r->str);
			freeReplyObject(r);
		}
		else
		{
			printf("\n redis HGET error, return type is not string \n");
			freeReplyObject(r);	
			return -1;
		}

		return 0;
	}


	int Redis::redis_keys(const std::string& vkey, std::vector<std::string>& value)
	{
		printf("\n redis search vkey :   %s \n", vkey.c_str());

		const char* chKey = vkey.c_str();

		redisReply* r = (redisReply*)redisCommand(c, "KEYS %s", chKey);

		if(r == NULL)
		{
			printf("\n KEYS error , vkey not exist :   %s \n", vkey.c_str());
			freeReplyObject(r);
			return -1;
		}

		if(r->type == REDIS_REPLY_NIL || r->type == REDIS_REPLY_ERROR)
		{
			printf("\n KEYS return , no data found :   %s \n", vkey.c_str());
			freeReplyObject(r);
			return 0;
		}

		if((r->type == REDIS_REPLY_STATUS && r->str != REDIS_OK) || r->type != REDIS_REPLY_ARRAY)
		{
			printf("\n KEYS error , vkey not exist :   %s \n", vkey.c_str());
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

					value.push_back(std::string(subKey));
				}
			}
		}

		freeReplyObject(r);
		printf("\n KEYS return ok , search vkeys : %s , result size %d \n", vkey.c_str(), value.size());

		return 0;
	}
};// namespace common