#include "LCMSubscriber.h"


CLCMSubscriber::CLCMSubscriber():
m_pLCM(new lcm::LCM("udpm://239.255.76.67:7667?ttl=0")),
m_bInitilized(false)
{
	m_bInitilized = InitilizeLCM();
}


CLCMSubscriber::~CLCMSubscriber()
{
}

void CLCMSubscriber::run()
{
	while (0 == m_pLCM->handle())
	{

	}
}

bool CLCMSubscriber::IsInitilized()
{
	return m_bInitilized;
}

bool CLCMSubscriber::InitilizeLCM()
{
	if (!m_pLCM->good())
	{
		PrintErrorInfo("Initialize communication error, please check the Ethernet connection", __FILE__, __FUNCTION__, __LINE__);
		return false;
	}
	m_pLCM->subscribe("VEHICLE_INFO",&CLCMHandler::CallbackVehicleInfo,&m_lcmHandler);
	m_pLCM->subscribe("RTK_INFO", &CLCMHandler::CallbackRTKInfo, &m_lcmHandler);
	m_pLCM->subscribe("GPSFront", &CLCMHandler::CallbackRTKIMUInfo, &m_lcmHandler);
	return true;
}