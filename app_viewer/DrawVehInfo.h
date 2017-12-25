#pragma once

#include "global.hpp"
#include <QStringList>

#include "METVehicleInfo_Lcm.hpp"
#include "METPublisCANEvent_Lcm.hpp"

class CDrawVehInfo
{
public:
	CDrawVehInfo();
	~CDrawVehInfo();
	void DecodeVehInfo(const lcm::ReceiveBuffer* recvBuf);
	const QStringList GetVehInfoStringList();
	bool m_bReceiveVehInfo;
private:
	boost::mutex m_mtuVehInfo;
	METVehicleInfo_Lcm m_msgVehInfo;
	METPublisCANEvent_Lcm m_msgVehicleInfo;
	double m_dspeed;
	double m_dwheelangle;
	double m_dyawrate;
};

