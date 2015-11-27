/*
//
//	Last Modify Date: 2015-11-27
//	Author: zengpw
//	History:
//					2015-10-21 zengpw created
//	File Property: private
//	Future:
//					I. 数据库操作
//
//
*/

#include "db_interface.h"

TLV_HANDLE_RTN DbInterface::firm_update(common::DB* db, TLV_HANDLE_DEV_FIRM& firm_handle)
{
	string sql;

	sql = "update t_device ";
	sql += "set fd_version = '";
	sql += firm_handle.version + "', fd_imei = '";
	sql += firm_handle.imei + "', fd_phone_cid = '";
	sql += firm_handle.iccid + "' where fd_id = '";
	sql += firm_handle.dev_id + "'";

	LOG_DEBUG("update sql: " << sql);

	if(!db->update(sql))
	{
		return THR_ERROR;
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::gps_update(common::DB* db, TLV_HANDLE_GPS& gps_handle)
{
	string sql;

	//谷歌地球gps数据 转 高德数据
	char buf[24];
	stringstream ss;

	string partition_x = gps_handle.latitude.substr(1, 2);
	string partition_y = gps_handle.longitude.substr(0, 3);

	double dx, dy;
	string x, y;

	ss << gps_handle.latitude;
	ss >> dx;
	ss.str("");
	ss.clear();

	// 11位数字（第1位是0，在转换成 double 类型时丢失），去掉后面的0；剩下7位数字，然后除以 100000
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%3.3f", dx/100000/10000);
	ss << buf;
	ss >> x;
	ss.str("");
	ss.clear();

	ss << gps_handle.longitude;
	ss >> dy;
	ss.str("");
	ss.clear();

	// 12位数字，去掉后面的0；剩下8位数字，然后除以 100000
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%3.3f", dy/100000/10000);
	ss << buf;
	ss >> y;
	ss.str("");
	ss.clear();

	sql = "select fd_offset_lng, fd_offset_lat from t_gps_offset subpartition(offset_max_";
	sql += partition_y + "_";
	sql += partition_x + ") where fd_lng = '";
	sql += y + "' and fd_lat = '";
	sql += x + "'";

	LOG_DEBUG("select sql: " << sql);

	if(!db->check())
	{
		return THR_ERROR;
	}

	try
	{
		otl_nocommit_stream os(1, sql.c_str(), *db->conn);

		try
		{
			db->conn->commit();

			while(!os.eof())
			{
				double offset_dx, offset_dy;
				string offset_x, offset_y;

				memset(buf, 0, sizeof(buf));
				os >> buf;
				offset_y = buf;

				memset(buf, 0, sizeof(buf));
				os >> buf;
				offset_x = buf;

				LOG_DEBUG("offset_x : " << offset_x);
				LOG_DEBUG("offset_y : " << offset_y);

				ss << offset_y;
				ss >> offset_dy;
				ss.str("");
				ss.clear();

				ss << offset_x;
				ss >> offset_dx;
				ss.str("");
				ss.clear();

				if(fabs(offset_dx) > 0.00000001 && fabs(offset_dy) > 0.00000001)
				{
					LOG_DEBUG("gps data need recalculate.");

					offset_dy = offset_dy*100000*10000;
					offset_dx = offset_dx*100000*10000;

					//加入偏移值
					dx += offset_dx;
					dy += offset_dy;

					//补到12位长度
					memset(buf, 0, sizeof(buf));
					sprintf(buf, "0%11lf", dx);
					ss << buf;
					gps_handle.latitude = ss.str();
					gps_handle.latitude += "000000000000";
					gps_handle.latitude = gps_handle.latitude.substr(0, 12);
					ss.str("");
					ss.clear();

					memset(buf, 0, sizeof(buf));
					sprintf(buf, "%12lf", dy);
					ss << buf;
					gps_handle.longitude = ss.str();
					gps_handle.longitude += "000000000000";
					gps_handle.longitude = gps_handle.longitude.substr(0, 12);
					ss.str("");
					ss.clear();

					LOG_DEBUG("new latitude = " << gps_handle.latitude << ", new longitude = " << gps_handle.longitude);
				}
			}

			os.close();
		}
		catch(...)
		{
			os.close();
			throw;
		}
	}
	catch(otl_exception &p)
	{
		LOG_DEBUG("DB select exception!");
		LOG_DEBUG("conn.msg = " << p.msg);
		LOG_DEBUG("conn.stm_text = " << p.stm_text);
		LOG_DEBUG("conn.var_info = " << p.var_info);
		db->conn->rollback();
		return THR_ERROR;
	}
	catch(...)
	{
		LOG_DEBUG("DB select occur unknown exception!");
		db->conn->rollback();
		return THR_ERROR;
	}

	//更新轨迹
	if(gps_handle.hbd.flag == "0")
	{
		sql = "insert into t_transway_info ";

		sql += "(FD_ID,";
		sql += "FD_ORDER_ID,";
		sql += "FD_GOODS_GPS_LONG,";
		sql += "FD_GOODS_GPS_LAT,";
		sql += "FD_GOODS_SENSOR_STATE,";
		sql += "FD_GOODS_GPS_MOD,";
		sql += "FD_GOODS_TEMPERATURE,";
		sql += "FD_GOODS_HUMIDITY,";
		sql += "FD_GOODS_ACCELER,";
		sql += "FD_GOODS_ACCELER_X,";
		sql += "FD_GOODS_ACCELER_Y,";
		sql += "FD_GOODS_ACCELER_Z,";
		sql += "FD_GOODS_EXPOSURE,";
		sql += "FD_GOODS_VOLTAGE,";
		sql += "FD_GPS_MODE,";
		sql += "FD_RESERVE,";
		sql += "FD_UPDATE_DATE,";
		sql += "FD_GOODS_ANGLE_X,";
		sql += "FD_GOODS_ANGLE_Y,";
		sql += "FD_GOODS_ANGLE_Z,";
		sql += "FD_MOVE_MARK";
		sql += ") values(";

		sql += "TRANS_INFO_SEQ.nextval, ";
		sql += "'";
		sql += gps_handle.order_id + "', '";
		sql += gps_handle.longitude + "', '";
		sql += gps_handle.latitude + "', ";
		sql += "null, ";
		sql += "null, '";
		sql += gps_handle.hbd.temperature + "', ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, '";
		sql += gps_handle.hbd.exposure + "', '";
		sql += gps_handle.hbd.voltage + "', '";
		sql += gps_handle.mode + "', '";
		sql += gps_handle.hbd.rssi + "', '";
		sql += gps_handle.datetime + "', ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, '";
		sql += gps_handle.hbd.move + "')";
	}
	else
	{
		HttpInterface hi;
		hi.gps2addrAmap(gps_handle.latitude, gps_handle.longitude, gps_handle.hbd.addr);

		LOG_DEBUG("alarm = " << gps_handle.hbd.alarm << ", addr = " << gps_handle.hbd.addr);

		sql = "insert into t_goods_warning ";

		sql += "(FD_ID,";
		sql += "FD_ORDER_ID,";
		sql += "FD_GOODS_GPS_LONG,";
		sql += "FD_GOODS_GPS_LAT,";
		sql += "FD_GOODS_SENSOR_STATE,";
		sql += "FD_GOODS_GPS_MODE,";
		sql += "FD_GOODS_TEMPERATURE,";
		sql += "FD_GOODS_HUMIDITY,";
		sql += "FD_GOODS_ACCELER,";
		sql += "FD_GOODS_ACCELER_X,";
		sql += "FD_GOODS_ACCELER_Y,";
		sql += "FD_GOODS_ACCELER_Z,";
		sql += "FD_GOODS_EXPOSURE,";
		sql += "FD_GOODS_VOLTAGE,";
		sql += "FD_GPS_MODE,";
		sql += "FD_RESERVE,";
		sql += "FD_WARNING_TIME,";
		sql += "FD_GOODS_ANGLE_X,";
		sql += "FD_GOODS_ANGLE_Y,";
		sql += "FD_GOODS_ANGLE_Z,";
		sql += "FD_WARNING_REASON,";
		sql += "FD_WARNING_ADDR,";
		sql += "FD_WARNING_LEVEL,";
		sql += "FD_GOODS_STATE";
		sql += ") values(";

		sql += "GOODS_WARNING_SEQ.nextval, ";
		sql += "'";
		sql += gps_handle.order_id + "', '";
		sql += gps_handle.longitude + "', '";
		sql += gps_handle.latitude + "', ";
		sql += "null, ";
		sql += "null, '";
		sql += gps_handle.hbd.temperature + "', ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, '";
		sql += gps_handle.hbd.exposure + "', '";
		sql += gps_handle.hbd.voltage + "', '";
		sql += gps_handle.mode + "', '";
		sql += gps_handle.hbd.rssi + "', '";
		sql += gps_handle.datetime + "', ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, '";
		sql += gps_handle.hbd.alarm + "', '";
		sql += gps_handle.hbd.addr + "', '";
		sql += "1', '";
		sql += "-1')";
	}

	LOG_DEBUG("insert sql: " << sql);

	if(!db->insert(sql))
	{
		return THR_ERROR;
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::lbs_update(common::DB* db, TLV_HANDLE_LBS& lbs_handle)
{
	string sql;

	//更新轨迹
	if(lbs_handle.hbd.flag == "0")
	{
		sql = "insert into t_transway_info ";

		sql += "(FD_ID,";
		sql += "FD_ORDER_ID,";
		sql += "FD_GOODS_GPS_LONG,";
		sql += "FD_GOODS_GPS_LAT,";
		sql += "FD_GOODS_SENSOR_STATE,";
		sql += "FD_GOODS_GPS_MOD,";
		sql += "FD_GOODS_TEMPERATURE,";
		sql += "FD_GOODS_HUMIDITY,";
		sql += "FD_GOODS_ACCELER,";
		sql += "FD_GOODS_ACCELER_X,";
		sql += "FD_GOODS_ACCELER_Y,";
		sql += "FD_GOODS_ACCELER_Z,";
		sql += "FD_GOODS_EXPOSURE,";
		sql += "FD_GOODS_VOLTAGE,";
		sql += "FD_GPS_MODE,";
		sql += "FD_RESERVE,";
		sql += "FD_UPDATE_DATE,";
		sql += "FD_GOODS_ANGLE_X,";
		sql += "FD_GOODS_ANGLE_Y,";
		sql += "FD_GOODS_ANGLE_Z,";
		sql += "FD_MOVE_MARK";
		sql += ") values(";

		sql += "TRANS_INFO_SEQ.nextval, ";
		sql += "'";
		sql += lbs_handle.order_id + "', '";
		sql += lbs_handle.longitude + "', '";
		sql += lbs_handle.latitude + "', ";
		sql += "null, ";
		sql += "null, '";
		sql += lbs_handle.hbd.temperature + "', ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, '";
		sql += lbs_handle.hbd.exposure + "', '";
		sql += lbs_handle.hbd.voltage + "', '";
		sql += lbs_handle.mode + "', '";
		sql += lbs_handle.hbd.rssi + "', '";
		sql += lbs_handle.datetime + "', ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, '";
		sql += lbs_handle.hbd.move + "')";
	}
	else
	{
		sql = "insert into t_goods_warning ";

		sql += "(FD_ID,";
		sql += "FD_ORDER_ID,";
		sql += "FD_GOODS_GPS_LONG,";
		sql += "FD_GOODS_GPS_LAT,";
		sql += "FD_GOODS_SENSOR_STATE,";
		sql += "FD_GOODS_GPS_MODE,";
		sql += "FD_GOODS_TEMPERATURE,";
		sql += "FD_GOODS_HUMIDITY,";
		sql += "FD_GOODS_ACCELER,";
		sql += "FD_GOODS_ACCELER_X,";
		sql += "FD_GOODS_ACCELER_Y,";
		sql += "FD_GOODS_ACCELER_Z,";
		sql += "FD_GOODS_EXPOSURE,";
		sql += "FD_GOODS_VOLTAGE,";
		sql += "FD_GPS_MODE,";
		sql += "FD_RESERVE,";
		sql += "FD_WARNING_TIME,";
		sql += "FD_GOODS_ANGLE_X,";
		sql += "FD_GOODS_ANGLE_Y,";
		sql += "FD_GOODS_ANGLE_Z,";
		sql += "FD_WARNING_REASON,";
		sql += "FD_WARNING_ADDR,";
		sql += "FD_WARNING_LEVEL,";
		sql += "FD_GOODS_STATE";
		sql += ") values(";

		sql += "GOODS_WARNING_SEQ.nextval, ";
		sql += "'";
		sql += lbs_handle.order_id + "', '";
		sql += lbs_handle.longitude + "', '";
		sql += lbs_handle.latitude + "', ";
		sql += "null, ";
		sql += "null, '";
		sql += lbs_handle.hbd.temperature + "', ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, '";
		sql += lbs_handle.hbd.exposure + "', '";
		sql += lbs_handle.hbd.voltage + "', '";
		sql += lbs_handle.mode + "', '";
		sql += lbs_handle.hbd.rssi + "', '";
		sql += lbs_handle.datetime + "', ";
		sql += "null, ";
		sql += "null, ";
		sql += "null, '";
		sql += lbs_handle.hbd.alarm + "', '";
		sql += lbs_handle.hbd.addr + "', '";
		sql += "1', '";
		sql += "-1')";
	}

	LOG_DEBUG("insert sql: " << sql);

	if(!db->insert(sql))
	{
		return THR_ERROR;
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::th_update(common::DB* db, TLV_HANDLE_TH& th_handle)
{
	string sql;

	//取分表号
	int i = 0;
	stringstream ss;
	string sub = th_handle.order_id.substr(th_handle.order_id.length() - 1);
	ss << sub;
	ss >> i;
	ss.str("");
	ss.clear();

	i = i%5;
	ss << i;
	sub = ss.str();
	ss.str("");
	ss.clear();

	//更新轨迹
	sql = "insert into da_express_th_";
	sql += sub;
	sql += " (fd_order_id, fd_info_id, fd_flag, fd_update_date, fd_goods_temperature_1, fd_goods_humidity_1) values(";
	sql += "'";
	sql += th_handle.order_id + "', '";
	sql += th_handle.datetime_gps + "', '";
	sql += th_handle.alarm + "', '";
	sql += th_handle.datetime + "', '";
	sql += th_handle.t0 + "', '";
	sql += th_handle.h0 + "')";

	LOG_DEBUG("insert sql: " << sql);

	if(!db->insert(sql))
	{
		return THR_ERROR;
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::unband_update(common::DB* db, TLV_HANDLE_UNBAND_RTN& unband_handle)
{
	if(unband_handle.rtn == "1")
	{
		string sql;

		sql = "update T_USER_ORDER ";
		sql += "set fd_order_state = 5, fd_update_date = default ";
		sql += "where fd_order_id in (select fd_order_id from T_USER_GOODS where fd_device_id = '";
		sql += unband_handle.dev_id;
		sql += "' and fd_state != 4)";

		LOG_DEBUG("update sql: " << sql);

		if(!db->update(sql))
		{
			return THR_ERROR;
		}

		sql = "update T_USER_GOODS ";
		sql += "set fd_state = 4, fd_reserve = '终端已回复解绑成功' ,fd_update_date = default ";
		sql += "where fd_device_id = '";
		sql += unband_handle.dev_id;
		sql += "' and fd_state != 4";

		LOG_DEBUG("update sql: " << sql);

		if(!db->update(sql))
		{
			return THR_ERROR;
		}
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::dev_unband_update(common::DB* db, TLV_HANDLE_DEV_UNBAND_RTN& dev_unband_handle)
{
	string sql;

	sql = "update T_USER_ORDER ";
	sql += "set fd_order_state = 5, fd_update_date = '";
	sql += dev_unband_handle.datetime;
	sql += "' ";
	sql += "where fd_order_id in (select fd_order_id from T_USER_GOODS where fd_device_id = '";
	sql += dev_unband_handle.dev_id;
	sql += "' and fd_state != 4)";

	LOG_DEBUG("update sql: " << sql);

	if(!db->update(sql))
	{
		return THR_ERROR;
	}

	sql = "update T_USER_GOODS ";
	sql += "set fd_state = 4, fd_reserve = '终端自解绑' ,fd_update_date = '";
	sql += dev_unband_handle.datetime;
	sql += "' ";
	sql += "where fd_device_id = '";
	sql += dev_unband_handle.dev_id;
	sql += "' and fd_state != 4";

	LOG_DEBUG("update sql: " << sql);

	if(!db->update(sql))
	{
		return THR_ERROR;
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::dev_msg_update(common::DB* db, TLV_HANDLE_DEV_MSG& dev_msg_handle)
{
	string sql;

	sql = "insert into t_device_trace_all ";
	sql += "(fd_id, fd_device_id, fd_goods_sensor_state, fd_reserve, fd_goods_voltage) values(";
	sql += "t_device_trace_autoid.nextval, '";
	sql += dev_msg_handle.dev_id + "', '";
	sql += dev_msg_handle.state + "', '";
	sql += dev_msg_handle.rssi + "', '";
	sql += dev_msg_handle.voltage + "')";

	LOG_DEBUG("insert sql: " << sql);

	if(!db->insert(sql))
	{
		return THR_ERROR;
	}

	sql = "update t_device ";
	sql += "set fd_version = '";
	sql += dev_msg_handle.version + "' ";
	sql += "where fd_id = '";
	sql += dev_msg_handle.dev_id + "'";

	LOG_DEBUG("update sql: " << sql);

	if(!db->update(sql))
	{
		return THR_ERROR;
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::parameter_update(common::DB* db, TLV_HANDLE_PARAMETER_RTN& parameter_handle)
{
	if(parameter_handle.rtn == "0")
	{
		string sql;

		sql = "update t_device_config_task_linux ";
		sql += "set fd_flag = '2' ";
		sql += "where fd_device_id = '";
		sql += parameter_handle.dev_id + "'";

		LOG_DEBUG("update sql: " << sql);

		if(!db->update(sql))
		{
			return THR_ERROR;
		}
	}

	if(parameter_handle.rtn == "1")
	{
		string sql;

		sql = "update t_device_config_task_linux ";
		sql += "set fd_flag = '0' ";
		sql += "where fd_device_id = '";
		sql += parameter_handle.dev_id + "'";

		LOG_DEBUG("update sql: " << sql);

		if(!db->update(sql))
		{
			return THR_ERROR;
		}
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::version_update(common::DB* db, TLV_HANDLE_VERSION_RTN& ver_handle)
{
	if(ver_handle.rtn == "0")
	{
		string sql;

		sql = "update T_VERSION_TASK ";
		sql += "set fd_flag = '2' ";
		sql += "where fd_device_id = '";
		sql += ver_handle.dev_id + "'";

		LOG_DEBUG("update sql: " << sql);

		if(!db->update(sql))
		{
			return THR_ERROR;
		}
	}

	if(ver_handle.rtn == "1")
	{
		string sql;

		sql = "update T_VERSION_TASK ";
		sql += "set fd_flag = '0' ";
		sql += "where fd_device_id = '";
		sql += ver_handle.dev_id + "'";

		LOG_DEBUG("update sql: " << sql);

		if(!db->update(sql))
		{
			return THR_ERROR;
		}
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::manage_lbs_update(common::DB* db, TLV_HANDLE_MANAGE_LBS& m_lbs_handle)
{
	string sql;

	sql = "insert into t_device_trace_all ";
	sql += "(fd_id, fd_device_id, fd_goods_sensor_state, fd_reserve, fd_goods_voltage, ";
	sql += "fd_update_date, fd_goods_temperature, fd_goods_gps_long, fd_goods_gps_lat) values(";
	sql += "t_device_trace_autoid.nextval, '";
	sql += m_lbs_handle.dev_id + "', '";
	sql += m_lbs_handle.state + "', '";
	sql += m_lbs_handle.rssi + "', '";
	sql += m_lbs_handle.voltage + "', '";
	sql += m_lbs_handle.datetime + "', '";
	sql += m_lbs_handle.temperature + "', '";
	sql += m_lbs_handle.longitude + "', '";
	sql += m_lbs_handle.latitude + "')";

	LOG_DEBUG("insert sql: " << sql);

	if(!db->insert(sql))
	{
		return THR_ERROR;
	}

	return THR_TRUE;
}