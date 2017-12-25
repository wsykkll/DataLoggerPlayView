#include "LCMHandler.h"


CLCMHandler::CLCMHandler()
{
}


CLCMHandler::~CLCMHandler()
{
}

void CLCMHandler::CallbackPrescanLines(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const PRESCAN_LANES* msg)
{
	m_stDrawPrescanLines.DecodePrescanLinesMsg(msg);
}

void CLCMHandler::CallbackMapLines(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stDrawPrescanLines.DecodeMapLines(recvBuf);
}

void CLCMHandler::CallbackTransform(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const TRANSFORM* msg)
{
	m_stCoordinatesDrawer.GotaTransformMsg(msg);
}

void CLCMHandler::CallbackMWRInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	//m_stMWRDrawer.DecodeRawFrontMWRObjectsMsg(msg);
	m_stMWRDrawer.DecodeRawFrontMWRObjectsMsg(recvBuf);
}

void CLCMHandler::CallbackSRRLeftInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stMWRDrawer.DecodeRawSRRLeftObjectsMsg(recvBuf);
}

void CLCMHandler::CallbackSRRRightInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stMWRDrawer.DecodeRawSRRRightObjectsMsg(recvBuf);
}

void CLCMHandler::CallbackRTKInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stINSDrawer.DecodeRTKMsg(recvBuf);
#ifdef CALCULATEPOSTURE
	m_stImgDrawer.DecodeVehRTKInfo(recvBuf);
#endif
}

void CLCMHandler::CallbackImageInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stImgDrawer.DecodeCameraImage(recvBuf);
}

void CLCMHandler::CallbackVehicleSpeedInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName)
{
	m_stVehInfoDrawer.DecodeVehInfo(recvbuf);
	m_stMWRDrawer.DecodeVehicleSpeedMsg(recvbuf);
}

void CLCMHandler::CallbackVehicleWheelAngleInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName)
{
	m_stVehInfoDrawer.DecodeVehInfo(recvbuf);
}

void CLCMHandler::CallbackVehicleYawrateInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName)
{
	m_stVehInfoDrawer.DecodeVehInfo(recvbuf);
}

void CLCMHandler::CallbackPrescanIMG(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stDrawPrescanLines.DecodePrescanIMG(recvBuf);
}

//void CLCMHandler::CallbackTSRInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const TSRInfo* msg)
void CLCMHandler::CallbackTSRInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	//m_mtxTSRInfo.lock();
	//memcpy(&m_msgTSRInfo, msg, sizeof(TSRInfo));
	//m_mtxTSRInfo.unlock();
	m_stImgDrawer.DecodeTSRInfo(recvBuf);
}

void CLCMHandler::CallbackPrescanRTKInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stDrawPrescanLines.DecodePrescanRTK(recvBuf);
}

void CLCMHandler::CallbackLaneMarkPointInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stImgDrawer.DecodeLaneMarkPoint(recvBuf);
}

void CLCMHandler::CallbackVehiclePosture(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stImgDrawer.DecodeVehiclePosture(recvBuf);
}

void CLCMHandler::CallbackNextPostureMsg(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stImgDrawer.DecodeNextPosture(recvBuf);
}