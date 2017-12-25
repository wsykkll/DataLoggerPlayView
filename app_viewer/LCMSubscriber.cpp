#include "LCMSubscriber.h"


CLCMSubscriber::CLCMSubscriber():
//m_pLCM(new lcm::LCM("udpm://239.255.76.67:7667?ttl=1")),
m_pLCM(new lcm::LCM),
m_bInitilized(false)
{
	m_bInitilized = InitilizeLCM();
}


CLCMSubscriber::~CLCMSubscriber()
{
	delete[] m_pLCM;
}

void CLCMSubscriber::run()
{
	while (0 == m_pLCM->handle())
	{

	}
}

bool CLCMSubscriber::InitilizeLCM()
{
	if (!m_pLCM->good())
	{
		PrintErrorInfo("initialize communication error, please check the Ethernet connection", __FILE__, __FUNCTION__, __LINE__);
		return false;
	}
	m_pLCM->subscribe("LANE_LINES", &CLCMHandler::CallbackPrescanLines, &m_lcmHandler);
	m_pLCM->subscribe("TRANSFORM", &CLCMHandler::CallbackTransform, &m_lcmHandler);
	m_pLCM->subscribe("ESR_RADAR", &CLCMHandler::CallbackMWRInfo, &m_lcmHandler);
	m_pLCM->subscribe("GPSFront", &CLCMHandler::CallbackRTKInfo, &m_lcmHandler);
	m_pLCM->subscribe("SRR_Left", &CLCMHandler::CallbackSRRLeftInfo, &m_lcmHandler);
	m_pLCM->subscribe("SRR_Right", &CLCMHandler::CallbackSRRRightInfo, &m_lcmHandler);
	m_pLCM->subscribe("Video", &CLCMHandler::CallbackImageInfo, &m_lcmHandler);
	m_pLCM->subscribe("VehicleInfo_vehicle_speed", &CLCMHandler::CallbackVehicleSpeedInfo, &m_lcmHandler);
	m_pLCM->subscribe("VehicleInfo_steering_wheel_angle", &CLCMHandler::CallbackVehicleWheelAngleInfo, &m_lcmHandler);
	m_pLCM->subscribe("VehicleInfo_vehicle_yaw_rate", &CLCMHandler::CallbackVehicleYawrateInfo, &m_lcmHandler);

	m_pLCM->subscribe("PRESCAN_IMG", &CLCMHandler::CallbackPrescanIMG, &m_lcmHandler);
	m_pLCM->subscribe("RTK_INFO", &CLCMHandler::CallbackPrescanRTKInfo, &m_lcmHandler);
	m_pLCM->subscribe("TSR_INFO", &CLCMHandler::CallbackTSRInfo, &m_lcmHandler);

	m_pLCM->subscribe("LanemarkPoint", &CLCMHandler::CallbackLaneMarkPointInfo, &m_lcmHandler);
	m_pLCM->subscribe("VehiclePosture", &CLCMHandler::CallbackVehiclePosture, &m_lcmHandler);

	m_pLCM->subscribe("MAP_LINES", &CLCMHandler::CallbackMapLines, &m_lcmHandler);
#ifdef CALCULATEPOSTURE
	m_pLCM->subscribe("NEXTHEADING", &CLCMHandler::CallbackNextPostureMsg, &m_lcmHandler);
#endif // CALCULATEPOSTURE
	return true;
}

bool CLCMSubscriber::IsInitilized()
{
	return m_bInitilized;
}
