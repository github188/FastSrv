/*
//
//	Last Modify Date: 2015-11-03
//	Author: zengpw
//	History:
//					2015-10-20 zengpw created
//	File Property: public
//	Future:
//					I. 封装 otl
//
//
*/

#include "db.h"

namespace common
{
	DB::DB(string conn_info)
	{
		this->conn_info = conn_info;
		conn = NULL;
	}

	DB::~DB()
	{
		if(conn != NULL)
		{
			conn->logoff();
			delete conn;
		}
	}

	otl_connect* DB::getConn()
	{
		try
		{
			otl_connect::otl_initialize(1);
			conn = new otl_connect;
			conn->rlogon(conn_info.c_str());

			LOG_DEBUG("DB connect success");
		}
		catch(otl_exception &p)
		{
			LOG_DEBUG("DB initialize exception!");
			LOG_DEBUG("conn.msg = " << p.msg);
			LOG_DEBUG("conn.stm_text = " << p.stm_text);
			LOG_DEBUG("conn.var_info = " << p.var_info);
			delete conn;
			conn = NULL;
		}
		catch(...)
		{
			LOG_DEBUG("DB initialize occur unknown exception!");
			delete conn;
			conn = NULL;
		}

		return conn;
	}

	bool DB::check()
	{
		if(conn == NULL)
		{
			LOG_DEBUG("DB not connect!");
			return false;
		}

		return true;
	}

	bool DB::insert(const string& sql)
	{
		if(conn == NULL)
		{
			LOG_DEBUG("DB not connect!");
			return false;
		}

		otl_nocommit_stream os(1, sql.c_str(), *conn);

		try
		{
			os.flush();
			conn->commit();

			int record = os.get_rpc();
			os.close();

			LOG_DEBUG("DB insert success : record = " << record);

			if(record <= 0)
			{
				return false;
			}
		}
		catch(otl_exception &p)
		{
			LOG_DEBUG("DB insert exception!");
			LOG_DEBUG("conn.msg = " << p.msg);
			LOG_DEBUG("conn.stm_text = " << p.stm_text);
			LOG_DEBUG("conn.var_info = " << p.var_info);
			conn->rollback();
			os.close();
			return false;
		}
		catch(...)
		{
			LOG_DEBUG("DB insert occur unknown exception!");
			conn->rollback();
			os.close();
			return false;
		}

		return true;
	}

	bool DB::update(const string& sql)
	{
		if(conn == NULL)
		{
			LOG_DEBUG("DB not connect!");
			return false;
		}

		otl_nocommit_stream os(1, sql.c_str(), *conn);

		try
		{
			os.flush();
			conn->commit();

			int record = os.get_rpc();
			os.close();

			LOG_DEBUG("DB update success : record = " << record);
		}
		catch(otl_exception &p)
		{
			LOG_DEBUG("DB update exception!");
			LOG_DEBUG("conn.msg = " << p.msg);
			LOG_DEBUG("conn.stm_text = " << p.stm_text);
			LOG_DEBUG("conn.var_info = " << p.var_info);
			conn->rollback();
			os.close();
			return false;
		}
		catch(...)
		{
			LOG_DEBUG("DB update occur unknown exception!");
			conn->rollback();
			os.close();
			return false;
		}

		return true;
	}
};// namespace common