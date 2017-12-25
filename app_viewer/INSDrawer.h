#pragma once
#include "global.hpp"
#include "METGPSInfo_Lcm.hpp"
#include <QStringList>
#include "TRANSFORM.hpp"

class INSDrawer
{
public:
	INSDrawer();
	~INSDrawer();

	void DecodeRTKMsg(const lcm::ReceiveBuffer* recvBuf);
	const QStringList GetRTKStringList(float& velocity);

private:
	boost::mutex m_mtuRTKInfo;
	METGPSInfo_Lcm m_msgRTKInfo;
	bool m_bRTK;
};

