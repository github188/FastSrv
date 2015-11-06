/*
//
//	Last Modify Date: 2015-11-05
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
	// return cidDataLbs_build(out);
	// return cidDataGps_build(out);
	// return cidDataTh_build(out);
	// return cidDevband_build(out);

	return session::HANDLE_RTN_CONTINUE;
}


session::HANDLE_RTN TerminalUtHandle::cidDataGps_build(protocol::PacketOut* out)
{
	out->setDevId("201506140223");
	out->setCID(CID_DATA_GPS);

	TLV_GPS gps_1;

	gps_1.dt = buildDateTime2k();

	gps_1.bd.rssi = 45;
	gps_1.bd.move = 1;
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
	out->setDevId("201506140223");
	out->setCID(CID_DATA_LBS);

	TLV_LBS lbs_1;

	lbs_1.dt = buildDateTime2k();

	lbs_1.bd.rssi = 45;
	lbs_1.bd.move = 1;
	lbs_1.bd.voltage = 409;
	lbs_1.bd.temperature = 2009;
	lbs_1.bd.exposure = 3364;

	lbs_1.ld[0].cell = 9112;
	lbs_1.ld[0].mnc = 00;
	lbs_1.ld[0].mcc = 460;
	lbs_1.ld[0].lac = 6338;
	lbs_1.ld[0].cell_id = 62755;
	lbs_1.ld[0].bsic = 35;
	lbs_1.ld[0].rssi = 45;

	lbs_1.ld[1].cell = 9112;
	lbs_1.ld[1].mnc = 00;
	lbs_1.ld[1].mcc = 460;
	lbs_1.ld[1].lac = 6338;
	lbs_1.ld[1].cell_id = 62498;
	lbs_1.ld[1].bsic = 35;
	lbs_1.ld[1].rssi = 45;

	lbs_1.ld[2].cell = 9112;
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
	lbs_2.bd.voltage = 409;
	lbs_2.bd.temperature = -2009;
	lbs_2.bd.exposure = 3364;

	lbs_2.ld[0].cell = 9112;
	lbs_2.ld[0].mnc = 00;
	lbs_2.ld[0].mcc = 460;
	lbs_2.ld[0].lac = 6338;
	lbs_2.ld[0].cell_id = 62755;
	lbs_2.ld[0].bsic = 35;
	lbs_2.ld[0].rssi = 45;

	lbs_2.ld[1].cell = 9112;
	lbs_2.ld[1].mnc = 00;
	lbs_2.ld[1].mcc = 460;
	lbs_2.ld[1].lac = 6338;
	lbs_2.ld[1].cell_id = 62498;
	lbs_2.ld[1].bsic = 35;
	lbs_2.ld[1].rssi = 45;

	lbs_2.ld[2].cell = 9112;
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
	out->setDevId("201506140223");
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

	th_2.alarm = 1;
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
	out->setDevId("201506140223");
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
		}
	}

	return session::HANDLE_RTN_CONTINUE;
}