#pragma once
#include <QObject>
#include <QStringList>
#include <lcm\lcm-cpp.hpp>
#include <GL/freeglut.h>
#include "global.hpp"

#include "PRESCAN_LANES.hpp"
#include "TRANSFORM.hpp"
#include "METRadarObject_Lcm.hpp"
#include "DrawPrescanLines.h"
#include "DrawCoordinates.h"
#include "DrawMWR.h"
#include "INSDrawer.h"
#include "DrawVehInfo.h"
#include "DrawCamera.h"
#include "TSRInfo.hpp"

class CLCMHandler
{
public:
	CLCMHandler();
	~CLCMHandler();

	CDrawElement m_stElementDrawer;

	CDrawPrescanLines m_stDrawPrescanLines;
	CDrawCoordinates m_stCoordinatesDrawer;
	CDrawMWR m_stMWRDrawer;
	INSDrawer m_stINSDrawer;
	CDrawCamera m_stImgDrawer;
	CDrawVehInfo m_stVehInfoDrawer;

	boost::mutex m_mtxTSRInfo;
	TSRInfo m_msgTSRInfo;

	void CallbackPrescanLines(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const PRESCAN_LANES* msg);
	void CallbackTransform(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const TRANSFORM* msg);
	void CallbackMWRInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	void CallbackSRRLeftInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	void CallbackSRRRightInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	void CallbackRTKInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	void CallbackImageInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	void CallbackVehicleSpeedInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName);
	void CallbackVehicleWheelAngleInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName);
	void CallbackVehicleYawrateInfo(const lcm::ReceiveBuffer* recvbuf, const std::string& channelName);
	void CallbackPrescanIMG(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	//void CallbackTSRInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const TSRInfo* msg);
	void CallbackTSRInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	void CallbackPrescanRTKInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);

	void CallbackLaneMarkPointInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	void CallbackVehiclePosture(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	void CallbackNextPostureMsg(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	void CallbackMapLines(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
};

