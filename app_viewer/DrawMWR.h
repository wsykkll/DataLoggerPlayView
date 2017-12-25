#pragma once
#include "global.hpp"
#include "METRadarObject_Lcm.hpp"
#include "DrawElement.h"
#include "DrawCoordinates.h"
#include "METSRRRadarObject_Lcm.hpp"
#include "METPublisCANEvent_Lcm.hpp"

enum ESR_STATUS
{
	NO_TARGET,
	NEW_TARGET,
	NEW_UPDATED_TARGET,
	UPDATED_TARGET,
	COASTED_TARGET,
	MERGED_TARGET,
	INVALID_COASTED_TARGET,
	NEW_COASTED_TARGET
};


class CDrawMWR
{
public:
	CDrawMWR();
	~CDrawMWR();

	/*void DecodeRawFrontMWRObjectsMsg(const METRadarObject_Lcm* msg);*/
	void DecodeRawFrontMWRObjectsMsg(const lcm::ReceiveBuffer* recvBuf);
	void DecodeRawSRRLeftObjectsMsg(const lcm::ReceiveBuffer* recvBuf);
	void DecodeRawSRRRightObjectsMsg(const lcm::ReceiveBuffer* recvBuf);
	void DecodeVehicleSpeedMsg(const lcm::ReceiveBuffer* recvBuf);
	const std::vector<TEXT_3D> GLDrawRawFrontMWRObjects(CDrawCoordinates& coordinates);
	const std::vector<TEXT_3D> GLDrawRawESRNewObjects(CDrawCoordinates& coordinates);
	const std::vector<TEXT_3D> GLDrawRawESRNewUpdatedObjects(CDrawCoordinates& coordinates);
	const std::vector<TEXT_3D> GLDrawRawESRUpdatedObjects(CDrawCoordinates& coordinates);
	const std::vector<TEXT_3D> GLDrawRawESRCoastedObjects(CDrawCoordinates& coordinates);
	const std::vector<TEXT_3D> GLDrawESRACCObjects(CDrawCoordinates& coordinates);
	const std::vector<TEXT_3D> GLDrawESRFCWObjects(CDrawCoordinates& coordinates);
	const std::vector<TEXT_3D> GLDrawRawSRRLeftObjects(CDrawCoordinates& coordinates);
	const std::vector<TEXT_3D> GLDrawRawSRRRightObjects(CDrawCoordinates& coordinates);

private:
	boost::mutex m_mtuRawFrontMWRObjects;
	boost::mutex m_mtuSRRLeftObjects;
	boost::mutex m_mtuSRRRightObjects;
	boost::mutex m_mtxVehInfo;

	METRadarObject_Lcm m_msgRawFrontMWRObjects;
	METSRRRadarObject_Lcm m_msgSRRLeftObjects;
	METSRRRadarObject_Lcm m_msgSRRRightObjects;
	METPublisCANEvent_Lcm m_msgVehicleSpeedInfo;

	CDrawElement m_stElementDrawer;
	float m_fVehSpeed;
};

