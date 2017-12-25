#include "INSDrawer.h"


INSDrawer::INSDrawer():
m_bRTK(true)
{
	m_msgRTKInfo.GGA_dwLat = 0.0f;
	m_msgRTKInfo.GGA_dwLon = 0.0f;
	m_msgRTKInfo.GGA_dwAlt = 0.0f;
	m_msgRTKInfo.TRA_dwHeading = 0.0f;
	m_msgRTKInfo.TRA_dwPitch = 0.0f;
	m_msgRTKInfo.TRA_nRoll = 0.0f;
	m_msgRTKInfo.GGA_nQF = 0;
}


INSDrawer::~INSDrawer()
{
}

void INSDrawer::DecodeRTKMsg(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtuRTKInfo.lock();
	m_msgRTKInfo.decode(recvBuf->data, 0, recvBuf->data_size);
	m_mtuRTKInfo.unlock();
}

const QStringList INSDrawer::GetRTKStringList(float& velocity)
{
	m_mtuRTKInfo.lock();
	QString str;
	QStringList strList;
	str.sprintf("=========RTK========");
	strList.append(str);
	str.sprintf("Latitude: %.8lf deg", m_msgRTKInfo.GGA_dwLat / 100);
	strList.append(str);
	str.sprintf("Longitude: %.8lf deg", m_msgRTKInfo.GGA_dwLon / 100);
	strList.append(str);
	str.sprintf("Altitude: %.3f m", m_msgRTKInfo.GGA_dwAlt);
	strList.append(str);
	str.sprintf("Heading: %.3f deg", m_msgRTKInfo.TRA_dwHeading);
	strList.append(str);
	str.sprintf("Pitch: %.3f deg", m_msgRTKInfo.TRA_dwPitch);
	strList.append(str);
	str.sprintf("Roll: %.3f deg", m_msgRTKInfo.TRA_nRoll);
	strList.append(str);
	//str.sprintf("VelocityNorth: %.3f m/s", m_msgRTKInfo.fVelNorth);
	//strList.append(str);
	//str.sprintf("VelocityWest: %.3f m/s", m_msgRTKInfo.fVelWest);
	//strList.append(str);
	//str.sprintf("VelocityUp: %.3f m/s", m_msgRTKInfo.fVelUp);
	//strList.append(str);
	//float speed = sqrt(m_msgRTKInfo.fVelNorth*m_msgRTKInfo.fVelNorth + m_msgRTKInfo.fVelWest*m_msgRTKInfo.fVelWest
	//	+ m_msgRTKInfo.fVelUp*m_msgRTKInfo.fVelUp); //the speed include the up speed;
	//str.sprintf("Velocity: %.3f m/s", speed);
	//strList.append(str);
	//str.sprintf("Velocity: %.3f km/h", speed*3.6f);
	//strList.append(str);
	//str.sprintf("AccelerationX: %.3f m/s/s", m_msgRTKInfo.fAccX);
	//strList.append(str);
	//str.sprintf("AccelerationY: %.3f m/s/s", m_msgRTKInfo.fAccY);
	//strList.append(str);
	//str.sprintf("AccelerationZ: %.3f m/s/s", m_msgRTKInfo.fAccZ);
	//strList.append(str);
	//str.sprintf("AngularRateX: %.3f deg/s", m_msgRTKInfo.fAngRateX*RADIAN_TO_DEGREE);
	//strList.append(str);
	//str.sprintf("AngularRateY: %.3f deg/s", m_msgRTKInfo.fAngRateY*RADIAN_TO_DEGREE);
	//strList.append(str);
	//str.sprintf("AngularRateZ: %.3f deg/s", m_msgRTKInfo.fAngRateZ*RADIAN_TO_DEGREE);
	//strList.append(str);
	str.sprintf("SystemStatus: 0x%04X", m_msgRTKInfo.GGA_nQF);
	strList.append(str);
	velocity = m_msgRTKInfo.RMC_dwSpeedIn*0.5144f*3.6f;
	m_mtuRTKInfo.unlock();
	return strList;
}