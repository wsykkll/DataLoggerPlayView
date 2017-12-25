#include "LCMHandler.h"


CLCMHandler::CLCMHandler()
{
}


CLCMHandler::~CLCMHandler()
{
}

void CLCMHandler::CallbackVehicleInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName, const VCU_VEHILCE_INFO* msg)
{
	m_mtuVehicleInfo.lock();
	memcpy(&m_msgVehicleInfo, msg, sizeof(VCU_VEHILCE_INFO));
	m_stTransformer.DeadReckoningWithVehicleInfo(m_msgVehicleInfo);
	m_mtuVehicleInfo.unlock();
}

void CLCMHandler::CallbackRTKInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName, const RTK* msg)
{
	m_stRTKData.nTimeStamp = msg->stHeader.nTimeStamp;
	m_stRTKData.nGPSTimeStamp = msg->stHeader.nTimeStamp;

	m_stRTKData.fLatitude = msg->dLatitude;
	m_stRTKData.fLongitude = msg->dLongitude;
	m_stRTKData.fAltitude = msg->fAltitude;

	m_stRTKData.fVelNorth = msg->fVelNorth;
	m_stRTKData.fVelWest = msg->fVelWest;

	m_stRTKData.fHeading = msg->fHeading;

	if (msg->nNavStatus == 4)
	{
		m_mtuTransformer.lock();
		m_stTransformer.Transform(m_stRTKData,true);
		m_mtuTransformer.unlock();
	}
	else
	{
		m_mtuTransformer.lock();
		m_stTransformer.Transform(m_stRTKData, false);
		m_mtuTransformer.unlock();
	}
}

void CLCMHandler::CallbackRTKIMUInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const METGPSInfo_Lcm* msg)
{
	m_stRTKData.nTimeStamp = msg->header.nTimeStamp;
	m_stRTKData.nGPSTimeStamp = msg->header.nTimeStamp;

	m_stRTKData.fLatitude = msg->GGA_dwLat*0.01;
	m_stRTKData.fLongitude = msg->GGA_dwLon*0.01;
	m_stRTKData.fAltitude = msg->GGA_dwAlt;

	float fHeading = msg->TRA_dwHeading;
	m_stRTKData.fHeading = fHeading;

	//TODO:calculate the speed
	m_stRTKData.fVelNorth = msg->RMC_dwSpeedIn * cos(fHeading*DEGREE_TO_RADIAN);
	m_stRTKData.fVelWest =-msg->RMC_dwSpeedIn * sin(fHeading*DEGREE_TO_RADIAN);

	

	if (msg->GGA_nQF == 4 || msg->GGA_nQF == 6)
	{
		m_mtuTransformer.lock();
		m_stTransformer.Transform(m_stRTKData, true);
		m_mtuTransformer.unlock();
	}
	else
	{
		m_mtuTransformer.lock();
		m_stTransformer.Transform(m_stRTKData, false);
		m_mtuTransformer.unlock();
	}
}