/*
//
//	Last Modify Date: 2015-11-06
//	Author: zengpw
//	History:
//					2015-11-04 zengpw created
//	File Property: private
//	Future:
//					I. 数据库操作
//
//
*/

#include "db_public.h"

namespace session
{
	bool DbPublic::public_get_order_id(common::DB* db, const string dev_id, string& order_id)
	{
		string sql;

		sql = "select nvl(fd_order_id, null) from t_user_goods ";
		sql += "where fd_device_id = '";
		sql += dev_id;
		sql += "' and fd_state !='4'";

		LOG_DEBUG("select sql: " << sql);

		if(!db->check())
		{
			return false;
		}

		otl_stream os(1, sql.c_str(), *db->conn);

		char buf[64];
		memset(buf, 0, sizeof(buf));

		try
		{
			while(!os.eof())
			{
				os >> buf;
			}

			os.close();
		}
		catch(otl_exception &p)
		{
			LOG_DEBUG("DB select exception!");
			LOG_DEBUG("conn.msg = " << p.msg);
			LOG_DEBUG("conn.stm_text = " << p.stm_text);
			LOG_DEBUG("conn.var_info = " << p.var_info);
			os.close();
			return false;
		}
		catch(...)
		{
			LOG_DEBUG("DB select occur unknown exception!");
			os.close();
			return false;
		}

		if(buf[0] == '\0')
		{
			LOG_DEBUG("dev_id " << dev_id << " can't find order id!");
			return false;
		}

		stringstream ss;

		ss << buf;
		order_id = ss.str();
		ss.str("");
		ss.clear();

		LOG_DEBUG("order_id : " << order_id);

		return true;
	}


	bool DbPublic::public_get_parameter_request(common::DB* db, const string dev_id, TLV_PARAMETER& para)
	{
		string sql;

		sql = "select fd_apn, fd_light_enable, fd_light_sound_enable, fd_temperature_enable, ";
		sql += "fd_temperature_sound_enable, fd_humidity_enable, fd_humidity_sound_enable, fd_light_value, ";
		sql += "fd_temperature_value, fd_temperature_minvalue, fd_humidity_value, fd_humidity_minvalue, ";
		sql += "fd_gprs_rate ";
		sql += "from t_device_config ";
		sql += "where fd_id = '";
		sql += dev_id;
		sql += "'";

		LOG_DEBUG("select sql: " << sql);

		if(!db->check())
		{
			return false;
		}

		otl_stream os(1, sql.c_str(), *db->conn);

		try
		{
			char buf[64];
			stringstream ss;
			int i;

			memset(&para, 0, sizeof(para));

			while(!os.eof())
			{
				//------------ 服务器
				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> para.apn;
				ss.str("");
				ss.clear();

				para.net = 1;
				para.band = 1;
				para.led = 1;

				//------------ 开关
				para.exposure_switch = 1;

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> i;
				para.exposure_alarm_switch = i;
				ss.str("");
				ss.clear();

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> i;
				para.exposure_voice_switch = i;
				ss.str("");
				ss.clear();

				para.t_switch = 1;

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> i;
				para.t_alarm_switch = i;
				ss.str("");
				ss.clear();

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> i;
				para.t_voice_switch = i;
				ss.str("");
				ss.clear();

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> i;
				para.h_alarm_switch = i;
				ss.str("");
				ss.clear();

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> i;
				para.h_voice_switch = i;
				ss.str("");
				ss.clear();

				//------------ 门限
				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> i;
				para.exposure_max = i;
				ss.str("");
				ss.clear();

				//温度需要除以10
				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> para.t0_max;
				para.t0_max = para.t0_max;
				ss.str("");
				ss.clear();

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> para.t0_min;
				para.t0_min = para.t0_min;
				ss.str("");
				ss.clear();

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> para.h0_max;
				ss.str("");
				ss.clear();

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> para.h0_min;
				ss.str("");
				ss.clear();

				para.temperature_cycle = 60;
				para.temperature_store_cycle = 120;
				para.exposure_cycle = 60;
				para.exposure_store_cycle = 60;

				memset(buf, 0, sizeof(buf));
				os >> buf;
				ss << buf;
				ss >> para.lbs_send_cycle;
				ss.str("");
				ss.clear();
			}

			os.close();
		}
		catch(otl_exception &p)
		{
			LOG_DEBUG("DB select exception!");
			LOG_DEBUG("conn.msg = " << p.msg);
			LOG_DEBUG("conn.stm_text = " << p.stm_text);
			LOG_DEBUG("conn.var_info = " << p.var_info);
			os.close();
			return false;
		}
		catch(...)
		{
			LOG_DEBUG("DB select occur unknown exception!");
			os.close();
			return false;
		}

		LOG_DEBUG("---------- TLV_PARAMETER content : ");
		LOG_DEBUG("addr = " << para.addr << \
				", port = " << para.port << \
				", apn = " << para.apn << \
				", user = " << para.user << \
				", pass = " << para.pass << \
				", net = " << (int)para.net << \
				", band = " << (int)para.band << \
				", led = " << (int)para.led);
		LOG_DEBUG("exposure_switch = " << (int)para.exposure_switch << \
				", exposure_alarm_switch = " << (int)para.exposure_alarm_switch << \
				", exposure_voice_switch = " << (int)para.exposure_voice_switch << \
				", t_switch = " << (int)para.t_switch << \
				", t_alarm_switch = " << (int)para.t_alarm_switch << \
				", t_voice_switch = " << (int)para.t_voice_switch << \
				", h_alarm_switch = " << (int)para.h_alarm_switch << \
				", h_voice_switch = " << (int)para.h_voice_switch);
		LOG_DEBUG("exposure_max = " << para.exposure_max << \
				", t0_max = " << para.t0_max << \
				", t0_min = " << para.t0_min << \
				", h0_max = " << para.h0_max << \
				", h0_min = " << para.h0_min << \
				", temperature_cycle = " << para.temperature_cycle << \
				", temperature_store_cycle = " << para.temperature_store_cycle << \
				", exposure_cycle = " << para.exposure_cycle << \
				", exposure_store_cycle = " << para.exposure_store_cycle << \
				", lbs_send_cycle = " << para.lbs_send_cycle);
		LOG_DEBUG("---------- end.");

		return true;
	}
};// namespace session