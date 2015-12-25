/*
//
//	Last Modify Date: 2015-12-25
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. task 单元测试
//
//
*/

#include "terminal_ut_handle.h"

session::HANDLE_RTN TerminalUtHandle::conn(protocol::PacketOut* out)
{
	#if 1
		// return empty_build(out);
		// return error_crc_build(out);
		return cidDataLbs_build(out);
		// return cidDataGps_build(out);
		// return cidDataTh_build(out);
		// return cidDevband_build(out);
		// return cidParameter_build(out);
		// return cidParameterVersion_build(out);
		// return cidManageLbs_build(out);
		// return cidDataTh2_build(out);
	#else
		return session::HANDLE_RTN_CONTINUE;
	#endif
}


session::HANDLE_RTN TerminalUtHandle::empty_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(0x0099);
	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::error_crc_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(0x0099);
	out->build();

	//设置 CRC 为 01
	out->data[out->len - 2] = 0;
	out->data[out->len - 1] = 1;

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::cidDataGps_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(CID_DATA_GPS);

	TLV_GPS gps_1;

	gps_1.dt = buildDateTime2k();

	gps_1.bd.rssi = 45;
	gps_1.bd.move = 1;
	gps_1.bd.flag = 0;
	gps_1.bd.voltage = 409;
	gps_1.bd.temperature = 2009;
	gps_1.bd.exposure = 3364;

	gps_1.sn_lat = 0;
	gps_1.ew_long = 0;
	gps_1.latitude = 3120064;
	gps_1.longitude = 12160311;

	out->add(TID_GPS, sizeof(TLV_GPS), (char*)&gps_1);

	sleep(1);

	TLV_GPS gps_2;

	gps_2.dt = buildDateTime2k();

	gps_2.bd.rssi = 45;
	gps_2.bd.move = 1;
	gps_2.bd.flag = 1;
	gps_2.bd.voltage = 409;
	gps_2.bd.temperature = -2009;
	gps_2.bd.exposure = 3364;

	gps_2.sn_lat = 0;
	gps_2.ew_long = 0;
	gps_2.latitude = 3120064;
	gps_2.longitude = 12160311;

	out->add(TID_GPS, sizeof(TLV_GPS), (char*)&gps_2);

	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::cidDataGps(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_RTN)
		{
			LOG_DEBUG("CID_DATA_GPS - TID_RTN - " << (int)*iter->value);
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TerminalUtHandle::cidDataLbs_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(CID_DATA_LBS);

	TLV_LBS lbs_1;

	lbs_1.dt = buildDateTime2k();

	lbs_1.bd.rssi = 45;
	lbs_1.bd.move = 1;
	lbs_1.bd.flag = 0;
	lbs_1.bd.voltage = 409;
	lbs_1.bd.temperature = 2009;
	lbs_1.bd.exposure = 3364;

	lbs_1.ld[0].cell = 152;
	lbs_1.ld[0].mnc = 00;
	lbs_1.ld[0].mcc = 460;
	lbs_1.ld[0].lac = 6338;
	lbs_1.ld[0].cell_id = 62755;
	lbs_1.ld[0].bsic = 35;
	lbs_1.ld[0].rssi = 45;

	lbs_1.ld[1].cell = 152;
	lbs_1.ld[1].mnc = 00;
	lbs_1.ld[1].mcc = 460;
	lbs_1.ld[1].lac = 6338;
	lbs_1.ld[1].cell_id = 62498;
	lbs_1.ld[1].bsic = 35;
	lbs_1.ld[1].rssi = 45;

	lbs_1.ld[2].cell = 152;
	lbs_1.ld[2].mnc = 00;
	lbs_1.ld[2].mcc = 460;
	lbs_1.ld[2].lac = 6334;
	lbs_1.ld[2].cell_id = 37089;
	lbs_1.ld[2].bsic = 35;
	lbs_1.ld[2].rssi = 45;

	out->add(TID_LBS, sizeof(TLV_LBS), (char*)&lbs_1);

	sleep(1);

	TLV_LBS lbs_2;

	lbs_2.dt = buildDateTime2k();

	lbs_2.bd.rssi = 45;
	lbs_2.bd.move = 1;
	lbs_2.bd.flag = 1;
	lbs_2.bd.voltage = 409;
	lbs_2.bd.temperature = -2009;
	lbs_2.bd.exposure = 3364;

	lbs_2.ld[0].cell = 152;
	lbs_2.ld[0].mnc = 00;
	lbs_2.ld[0].mcc = 460;
	lbs_2.ld[0].lac = 6338;
	lbs_2.ld[0].cell_id = 62755;
	lbs_2.ld[0].bsic = 35;
	lbs_2.ld[0].rssi = 45;

	lbs_2.ld[1].cell = 152;
	lbs_2.ld[1].mnc = 00;
	lbs_2.ld[1].mcc = 460;
	lbs_2.ld[1].lac = 6338;
	lbs_2.ld[1].cell_id = 62498;
	lbs_2.ld[1].bsic = 35;
	lbs_2.ld[1].rssi = 45;

	lbs_2.ld[2].cell = 152;
	lbs_2.ld[2].mnc = 00;
	lbs_2.ld[2].mcc = 460;
	lbs_2.ld[2].lac = 6334;
	lbs_2.ld[2].cell_id = 37089;
	lbs_2.ld[2].bsic = 35;
	lbs_2.ld[2].rssi = 45;

	out->add(TID_LBS, sizeof(TLV_LBS), (char*)&lbs_2);

	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::cidDataLbs(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_RTN)
		{
			LOG_DEBUG("CID_DATA_LBS - TID_RTN - " << (int)*iter->value);
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TerminalUtHandle::cidDataTh_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(CID_DATA_TH);

	TLV_TH th_1;

	th_1.dt = buildDateTime2k();
	th_1.dt_gps = buildDateTime2k();

	th_1.alarm = 0;
	th_1.t0 = 288;
	th_1.h0 = 223;

	out->add(TID_TH, sizeof(TLV_TH), (char*)&th_1);

	sleep(1);

	TLV_TH th_2;

	th_2.dt = buildDateTime2k();
	th_2.dt_gps = buildDateTime2k();

	/* = 00, = 01, = 11 */
	th_2.alarm = 3;
	th_2.t0 = -121;
	th_2.h0 = 0;

	out->add(TID_TH, sizeof(TLV_TH), (char*)&th_2);

	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::cidDataTh(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_RTN)
		{
			LOG_DEBUG("CID_DATA_TH - TID_RTN - " << (int)*iter->value);
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TerminalUtHandle::cidUnband(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_TIME)
		{
			TLV_TIME tt;

			memcpy(&tt, iter->value, iter->len);

			LOG_DEBUG("CID_UNBAND - TID_TIME - " << DateTime2StringSec(tt));

			TLV_RTN rtn = 1;
			out->add(TID_RTN, sizeof(TLV_RTN), (char*)&rtn);
			out->build();

			return session::HANDLE_RTN_SEND;
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TerminalUtHandle::cidDevband_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(CID_DEV_BAND);

	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::cidDevband(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_TIME)
		{
			TLV_TIME tt;

			memcpy(&tt, iter->value, iter->len);

			printDateTimeSec(tt);
			LOG_DEBUG("cidDevband - TID_TIME - " << DateTime2StringSec(tt));
		}

		if(iter->type == TID_ORDER_ID)
		{
			TLV_ORDER_ID order_id;

			memcpy(&order_id, iter->value, iter->len);

			LOG_DEBUG("cidDevband - TID_ORDER_ID - " << order_id);
		}

		if(iter->type == TID_PARAMETER)
		{
			TLV_PARAMETER para;

			memcpy(&para, iter->value, iter->len);

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
					", t0_alarm_switch = " << (int)para.t0_alarm_switch << \
					", t0_voice_switch = " << (int)para.t0_voice_switch << \
					", h0_alarm_switch = " << (int)para.h0_alarm_switch << \
					", h0_voice_switch = " << (int)para.h0_voice_switch << \
					", t1_alarm_switch = " << (int)para.t1_alarm_switch << \
					", t1_voice_switch = " << (int)para.t1_voice_switch << \
					", h1_alarm_switch = " << (int)para.h1_alarm_switch << \
					", h1_voice_switch = " << (int)para.h1_voice_switch);
			LOG_DEBUG("exposure_max = " << para.exposure_max << \
					", t0_max = " << para.t0_max << \
					", t0_min = " << para.t0_min << \
					", h0_max = " << para.h0_max << \
					", h0_min = " << para.h0_min << \
					", t1_max = " << para.t1_max << \
					", t1_min = " << para.t1_min << \
					", h1_max = " << para.h1_max << \
					", h1_min = " << para.h1_min << \
					", temperature_cycle = " << para.temperature_cycle << \
					", temperature_store_cycle = " << para.temperature_store_cycle << \
					", temperature_store_cycle_alarm = " << para.temperature_store_cycle_alarm << \
					", exposure_cycle = " << para.exposure_cycle << \
					", exposure_store_cycle = " << para.exposure_store_cycle << \
					", lbs_send_cycle = " << para.lbs_send_cycle << \
					", lbs_send_cycle_alarm = " << para.lbs_send_cycle_alarm);
			LOG_DEBUG("---------- end.");
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TerminalUtHandle::cidParameter_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(CID_PARAMETER);

	TLV_RTN rtn = 1;
	out->add(TID_RTN, sizeof(TLV_RTN), (char*)&rtn);

	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::cidParameter(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_PARAMETER)
		{
			TLV_PARAMETER para;

			memcpy(&para, iter->value, iter->len);

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
					", t0_alarm_switch = " << (int)para.t0_alarm_switch << \
					", t0_voice_switch = " << (int)para.t0_voice_switch << \
					", h0_alarm_switch = " << (int)para.h0_alarm_switch << \
					", h0_voice_switch = " << (int)para.h0_voice_switch << \
					", t1_alarm_switch = " << (int)para.t1_alarm_switch << \
					", t1_voice_switch = " << (int)para.t1_voice_switch << \
					", h1_alarm_switch = " << (int)para.h1_alarm_switch << \
					", h1_voice_switch = " << (int)para.h1_voice_switch);
			LOG_DEBUG("exposure_max = " << para.exposure_max << \
					", t0_max = " << para.t0_max << \
					", t0_min = " << para.t0_min << \
					", h0_max = " << para.h0_max << \
					", h0_min = " << para.h0_min << \
					", t1_max = " << para.t1_max << \
					", t1_min = " << para.t1_min << \
					", h1_max = " << para.h1_max << \
					", h1_min = " << para.h1_min << \
					", temperature_cycle = " << para.temperature_cycle << \
					", temperature_store_cycle = " << para.temperature_store_cycle << \
					", temperature_store_cycle_alarm = " << para.temperature_store_cycle_alarm << \
					", exposure_cycle = " << para.exposure_cycle << \
					", exposure_store_cycle = " << para.exposure_store_cycle << \
					", lbs_send_cycle = " << para.lbs_send_cycle << \
					", lbs_send_cycle_alarm = " << para.lbs_send_cycle_alarm);
			LOG_DEBUG("---------- end.");
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TerminalUtHandle::cidParameterVersion_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(CID_PARAMETER_VERSION);

	TLV_RTN rtn = 1;
	out->add(TID_RTN, sizeof(TLV_RTN), (char*)&rtn);

	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::cidParameterVersion(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_PARAMETER_VERSION)
		{
			TLV_PARAMETER_VERSION ver;

			memcpy(&ver, iter->value, iter->len);

			LOG_DEBUG("---------- TLV_PARAMETER_VERSION content : ");
			LOG_DEBUG("update_flag = " << (int)ver.update_flag << \
					", version = " << (int)ver.version << \
					", addr = " << ver.addr << \
					", port = " << ver.port << \
					", apn = " << ver.apn << \
					", user = " << ver.user << \
					", pass = " << ver.pass << \
					", file = " << ver.file << \
					", path = " << ver.path);
			LOG_DEBUG("---------- end.");
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TerminalUtHandle::cidManageLbs_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(CID_MANAGE_LBS);

	TLV_MANAGE_LBS m_lbs_1;

	m_lbs_1.dt = buildDateTime2k();

	m_lbs_1.rssi = 45;
	m_lbs_1.state = 0;
	m_lbs_1.voltage = 409;
	m_lbs_1.temperature = 2009;

	m_lbs_1.ld[0].cell = 152;
	m_lbs_1.ld[0].mnc = 00;
	m_lbs_1.ld[0].mcc = 460;
	m_lbs_1.ld[0].lac = 6338;
	m_lbs_1.ld[0].cell_id = 62755;
	m_lbs_1.ld[0].bsic = 35;
	m_lbs_1.ld[0].rssi = 45;

	m_lbs_1.ld[1].cell = 152;
	m_lbs_1.ld[1].mnc = 00;
	m_lbs_1.ld[1].mcc = 460;
	m_lbs_1.ld[1].lac = 6338;
	m_lbs_1.ld[1].cell_id = 62498;
	m_lbs_1.ld[1].bsic = 35;
	m_lbs_1.ld[1].rssi = 45;

	m_lbs_1.ld[2].cell = 152;
	m_lbs_1.ld[2].mnc = 00;
	m_lbs_1.ld[2].mcc = 460;
	m_lbs_1.ld[2].lac = 6334;
	m_lbs_1.ld[2].cell_id = 37089;
	m_lbs_1.ld[2].bsic = 35;
	m_lbs_1.ld[2].rssi = 45;

	out->add(TID_MANAGE_LBS, sizeof(TLV_MANAGE_LBS), (char*)&m_lbs_1);

	sleep(1);

	TLV_MANAGE_LBS m_lbs_2;

	m_lbs_2.dt = buildDateTime2k();

	m_lbs_2.rssi = 45;
	m_lbs_2.state = 0;
	m_lbs_2.voltage = 409;
	m_lbs_2.temperature = -2009;

	m_lbs_2.ld[0].cell = 152;
	m_lbs_2.ld[0].mnc = 00;
	m_lbs_2.ld[0].mcc = 460;
	m_lbs_2.ld[0].lac = 6338;
	m_lbs_2.ld[0].cell_id = 62755;
	m_lbs_2.ld[0].bsic = 35;
	m_lbs_2.ld[0].rssi = 45;

	m_lbs_2.ld[1].cell = 152;
	m_lbs_2.ld[1].mnc = 00;
	m_lbs_2.ld[1].mcc = 460;
	m_lbs_2.ld[1].lac = 6338;
	m_lbs_2.ld[1].cell_id = 62498;
	m_lbs_2.ld[1].bsic = 35;
	m_lbs_2.ld[1].rssi = 45;

	m_lbs_2.ld[2].cell = 152;
	m_lbs_2.ld[2].mnc = 00;
	m_lbs_2.ld[2].mcc = 460;
	m_lbs_2.ld[2].lac = 6334;
	m_lbs_2.ld[2].cell_id = 37089;
	m_lbs_2.ld[2].bsic = 35;
	m_lbs_2.ld[2].rssi = 45;

	out->add(TID_MANAGE_LBS, sizeof(TLV_MANAGE_LBS), (char*)&m_lbs_2);

	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::cidManageLbs(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_RTN)
		{
			LOG_DEBUG("CID_MANAGE_LBS - TID_RTN - " << (int)*iter->value);
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TerminalUtHandle::cidDataTh2_build(protocol::PacketOut* out)
{
	out->setDevId("201506040000");
	out->setCID(CID_DATA_TH2);

	TLV_TH2 th_1;

	th_1.dt = buildDateTime2k();
	th_1.dt_gps = buildDateTime2k();

	th_1.alarm = 0;
	th_1.t0 = 288;
	th_1.h0 = 223;
	th_1.t1 = 502;
	th_1.h1 = 213;

	out->add(TID_TH2, sizeof(TLV_TH2), (char*)&th_1);

	sleep(1);

	TLV_TH2 th_2;

	th_2.dt = buildDateTime2k();
	th_2.dt_gps = buildDateTime2k();

	/* = 0000, = 0001, = 0011, = 0100, = 0110, = 0111, = 1000, ... = 1110 */
	th_2.alarm = 15;
	th_2.t0 = -121;
	th_2.h0 = 0;
	th_2.t1 = -333;
	th_2.h1 = -23;

	out->add(TID_TH2, sizeof(TLV_TH2), (char*)&th_2);

	out->build();

	return session::HANDLE_RTN_SEND;
}


session::HANDLE_RTN TerminalUtHandle::cidDataTh2(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type == TID_RTN)
		{
			LOG_DEBUG("CID_DATA_TH - TID_RTN - " << (int)*iter->value);
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}