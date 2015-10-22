/*
//
//	Last Modify Date: 2015-10-22
//	Author: zengpw
//	History:
//					2015-10-22 zengpw created
//	File Property: private
//	Future:
//					I. http 操作
//
//
*/

#include "http_interface.h"

TLV_HANDLE_RTN HttpInterface::lbs2gps(LbsData* pLD, string& latitude, string& longitude)
{
	LOG_DEBUG("---------- lbs2gps : ");

	for(int i = 0; i < 3; i++)
	{
		LOG_DEBUG("cell = " << (int)pLD->cell << \
				",mnc = " << (int)pLD->mnc << \
				",mcc = " << pLD->mcc << \
				",lac = " << pLD->lac << \
				",cell_id = " << pLD->cell_id << \
				",bsic = " << (int)pLD->bsic << \
				", rssi = " << (int)pLD->rssi);

		pLD++;
	}

	LOG_DEBUG("---------- end.");

	return THR_OK;
}