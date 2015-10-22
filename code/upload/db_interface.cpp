/*
//
//	Last Modify Date: 2015-10-22
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

TLV_HANDLE_RTN DbInterface::gps_update(common::DB* db, TLV_HANDLE_GPS& gps_handle)
{
	string sql;

	//TODO: 进行纠偏

	//TODO: 更新电压

	//TODO: 插入轨迹表 t_transway_info
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
	sql += "FD_MOVE_MARK) values(";

	sql += "TRANS_INFO_SEQ.nextval, ";
	sql += "'888888888888','";
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
	sql += gps_handle.mode + "', ";
	sql += "null, '";
	sql += gps_handle.datetime + "', ";
	sql += "null, ";
	sql += "null, ";
	sql += "null, '";
	sql += gps_handle.hbd.move + "')";

	LOG_DEBUG("insert sql: " << sql);

	if(db->insert(sql))
	{
		return THR_TRUE;
	}
	else
	{
		return THR_ERROR;
	}

	return THR_TRUE;
}


TLV_HANDLE_RTN DbInterface::lbs_update(common::DB* db, TLV_HANDLE_LBS& lbs_handle)
{
	string sql;

	//TODO: 进行纠偏

	//TODO: 更新电压

	//TODO: 插入轨迹表 t_transway_info
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
	sql += "FD_MOVE_MARK) values(";

	sql += "TRANS_INFO_SEQ.nextval, ";
	sql += "'888888888888','";
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
	sql += lbs_handle.mode + "', ";
	sql += "null, '";
	sql += lbs_handle.datetime + "', ";
	sql += "null, ";
	sql += "null, ";
	sql += "null, '";
	sql += lbs_handle.hbd.move + "')";

	LOG_DEBUG("insert sql: " << sql);

	if(db->insert(sql))
	{
		return THR_TRUE;
	}
	else
	{
		return THR_ERROR;
	}

	return THR_TRUE;
}