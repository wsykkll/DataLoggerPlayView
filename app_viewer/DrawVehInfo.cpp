#include "DrawVehInfo.h"


CDrawVehInfo::CDrawVehInfo():
m_bReceiveVehInfo(false)
{
	m_dspeed = 10.0f;
	m_dwheelangle = 0.0f;
	m_dyawrate = 0.0f;
}


CDrawVehInfo::~CDrawVehInfo()
{
}

void CDrawVehInfo::DecodeVehInfo(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtuVehInfo.lock();
	m_bReceiveVehInfo = true;
	//m_msgVehInfo.decode(recvBuf->data, 0, recvBuf->data_size);
	m_msgVehicleInfo.decode(recvBuf->data, 0, recvBuf->data_size);
	m_mtuVehInfo.unlock();
}

const QStringList CDrawVehInfo::GetVehInfoStringList()
{
	QString str;
	QStringList strList;
	str.sprintf("========Vehicle Info=======");
	strList.append(str);
	switch (m_msgVehicleInfo.messageType)
	{
	case 1:
		m_dspeed = m_msgVehicleInfo.messageval;
		break;
	case 2:
		m_dwheelangle = m_msgVehicleInfo.messageval;
		break;
	case 6:
		m_dyawrate = m_msgVehicleInfo.messageval;
		break;
	default:
		break;
	}
	str.sprintf("Wheel Steer: %.3f deg", m_dwheelangle);
	strList.append(str);
	str.sprintf("YawRate: %.3f deg/s", m_dyawrate);
	strList.append(str);
	str.sprintf("Speed: %.3f km/h", m_dspeed);
	strList.append(str);
	return strList;
}
