#pragma once

#include "Transformer.h"
#include "global.hpp"

class CLCMHandler
{
public:
	CLCMHandler();
	~CLCMHandler();

	void CallbackRTKInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName, const RTK* msg);
	void CallbackVehicleInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName, const VCU_VEHILCE_INFO* msg);
	void CallbackRTKIMUInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const METGPSInfo_Lcm* msg);

private:
	CTransformer m_stTransformer;
	boost::mutex m_mtuTransformer;

	RTK_RAW_DATA m_stRTKData;

	VCU_VEHILCE_INFO m_msgVehicleInfo;
	boost::mutex m_mtuVehicleInfo;
};

