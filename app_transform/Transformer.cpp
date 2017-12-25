#include "Transformer.h"


CTransformer::CTransformer() :
m_nLastTimeStamp(0),
m_bTransformStarted(false),
m_bIsLCMInitialized(false),
m_stRPCamera2Vehicle(-1.605f, -0.115f, 1.21f, 0.0f, 0.0f, 0.0f),
m_stRPMWR2Vehicle(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
m_stRPLeftSRR2Vehicle(-3.0f, 0.9f, 0.6f, 30 * DEGREE_TO_RADIAN, 0.0f, 0.0f),
m_stRPRightSRR2Vehicle(-3.0f, -0.9f, 0.6f, 150 * DEGREE_TO_RADIAN, 0.0f, 0.0f),
m_fRealSpeedVCUSpeedRatio(1.0f)
{
	m_bIsLCMInitialized = InitializeLCM();

	m_msgTransform.gfCameraPoseInVehicle[0] = m_stRPCamera2Vehicle.fX;
	m_msgTransform.gfCameraPoseInVehicle[1] = m_stRPCamera2Vehicle.fY;
	m_msgTransform.gfCameraPoseInVehicle[2] = m_stRPCamera2Vehicle.fZ;
	m_msgTransform.gfCameraPoseInVehicle[3] = m_stRPCamera2Vehicle.fYaw;
	m_msgTransform.gfCameraPoseInVehicle[4] = m_stRPCamera2Vehicle.fPitch;
	m_msgTransform.gfCameraPoseInVehicle[5] = m_stRPCamera2Vehicle.fRoll;
	CalculateTransformMatrix(m_stRPCamera2Vehicle, m_msgTransform.gfTransformCamera2Vehicle);

	m_msgTransform.gfFrontMWRPoseInVehicle[0] = m_stRPMWR2Vehicle.fX;
	m_msgTransform.gfFrontMWRPoseInVehicle[1] = m_stRPMWR2Vehicle.fY;
	m_msgTransform.gfFrontMWRPoseInVehicle[2] = m_stRPMWR2Vehicle.fZ;
	m_msgTransform.gfFrontMWRPoseInVehicle[3] = m_stRPMWR2Vehicle.fYaw;
	m_msgTransform.gfFrontMWRPoseInVehicle[4] = m_stRPMWR2Vehicle.fPitch;
	m_msgTransform.gfFrontMWRPoseInVehicle[5] = m_stRPMWR2Vehicle.fRoll;
	CalculateTransformMatrix(m_stRPMWR2Vehicle, m_msgTransform.gfTransformFrontMWR2Vehicle);

	m_msgTransform.gfLeftSRRPoseInVehicle[0] = m_stRPLeftSRR2Vehicle.fX;
	m_msgTransform.gfLeftSRRPoseInVehicle[1] = m_stRPLeftSRR2Vehicle.fY;
	m_msgTransform.gfLeftSRRPoseInVehicle[2] = m_stRPLeftSRR2Vehicle.fZ;
	m_msgTransform.gfLeftSRRPoseInVehicle[3] = m_stRPLeftSRR2Vehicle.fYaw;
	m_msgTransform.gfLeftSRRPoseInVehicle[4] = m_stRPLeftSRR2Vehicle.fPitch;
	m_msgTransform.gfLeftSRRPoseInVehicle[5] = m_stRPLeftSRR2Vehicle.fRoll;
	CalculateTransformMatrix(m_stRPLeftSRR2Vehicle, m_msgTransform.gfTransformLeftSRR2Vehicle);

	m_msgTransform.gfRightSRRPoseInVehicle[0] = m_stRPRightSRR2Vehicle.fX;
	m_msgTransform.gfRightSRRPoseInVehicle[1] = m_stRPRightSRR2Vehicle.fY;
	m_msgTransform.gfRightSRRPoseInVehicle[2] = m_stRPRightSRR2Vehicle.fZ;
	m_msgTransform.gfRightSRRPoseInVehicle[3] = m_stRPRightSRR2Vehicle.fYaw;
	m_msgTransform.gfRightSRRPoseInVehicle[4] = m_stRPRightSRR2Vehicle.fPitch;
	m_msgTransform.gfRightSRRPoseInVehicle[5] = m_stRPRightSRR2Vehicle.fRoll;
	CalculateTransformMatrix(m_stRPRightSRR2Vehicle, m_msgTransform.gfTransformRightSRR2Vehicle);
}


CTransformer::~CTransformer()
{
}

void CTransformer::Transform(const RTK_RAW_DATA& rtk, bool bStartTransform/* =false */)
{
	if (bStartTransform)
	{
		m_bTransformStarted = true;
	}
	if (m_bTransformStarted)
	{
		int deltaTimestamp = rtk.nGPSTimeStamp - m_nLastTimeStamp;
		m_nLastTimeStamp = rtk.nGPSTimeStamp;
		if (deltaTimestamp>0 && deltaTimestamp<500000)
		{
			IntegrateVelocity(rtk.fVelNorth, rtk.fVelWest, rtk.fVelUp, deltaTimestamp);
		} 
		else
		{
			m_bTransformStarted = false;

			ResetVelocityIntegrator();
			ResetDRIntegrator();
		}
	} 
	else
	{
		ResetVelocityIntegrator();
		ResetDRIntegrator();
	}

	m_stRPVehicle2World.fX = m_stVelocityIntegrator.fX;
	m_stRPVehicle2World.fY = m_stVelocityIntegrator.fY;
	m_stRPVehicle2World.fZ = m_stVelocityIntegrator.fZ;
	m_stRPVehicle2World.fYaw = rtk.fHeading;
	m_stRPVehicle2World.fPitch = rtk.fPitch;
	m_stRPVehicle2World.fRoll = rtk.fRoll;

	//calculate transfrom vehicle->world;
	m_msgTransform.gfVehiclePoseInWorld[0] = m_stRPVehicle2World.fX;
	m_msgTransform.gfVehiclePoseInWorld[1] = m_stRPVehicle2World.fY;
	m_msgTransform.gfVehiclePoseInWorld[2] = m_stRPVehicle2World.fZ;
	m_msgTransform.gfVehiclePoseInWorld[3] = m_stRPVehicle2World.fYaw;
	m_msgTransform.gfVehiclePoseInWorld[4] = m_stRPVehicle2World.fPitch;
	m_msgTransform.gfVehiclePoseInWorld[5] = m_stRPVehicle2World.fRoll;

	CalculateTransformMatrix(m_stRPVehicle2World, m_msgTransform.gfTransformVehicle2World);

	//publish transform;
	m_msgTransform.stHeader.nCounter = (static_cast<unsigned int> (m_msgTransform.stHeader.nCounter) + 1) % 65535;
	m_msgTransform.stHeader.nTimeStamp = GetLocalTimeStampInMicroSec();

	m_msgTransform.nRTKTimeStamp = rtk.nTimeStamp;

	m_msgTransform.gfVehicleVelocityInWorld[0] = rtk.fVelNorth;
	m_msgTransform.gfVehicleVelocityInWorld[1] = rtk.fVelWest;
	m_msgTransform.gfVehicleVelocityInWorld[2] = rtk.fVelUp;

	memcpy(&(m_msgTransform.gfTransformVehicle2WorldVCUDR), &(m_msgTransform.gfTransformVehicle2World), 16 * sizeof(float));
	memcpy(&(m_msgTransform.gfVehiclePoseInWorldVCUDR), &(m_msgTransform.gfVehiclePoseInWorld), 6 * sizeof(float));
	memcpy(&(m_msgTransform.gfVehicleVelocityInWorldVCUDR), &(m_msgTransform.gfVehicleVelocityInWorld), 3 * sizeof(float));

	if (m_stDRResault.bValid)
	{
		float DeltaTime = ((long long)m_msgTransform.nRTKTimeStamp - (long long)m_stDRResault.nTimeStamp) * MICRO_SEC_TO_SEC;
		m_msgTransform.gfVehiclePoseInWorldVCUDR[0] = m_stDRResault.gfPos_CFI_WORLD[0] + DeltaTime * m_stDRResault.gfVelocity_CFI_WORLD[0];
		m_msgTransform.gfVehiclePoseInWorldVCUDR[1] = m_stDRResault.gfPos_CFI_WORLD[1] + DeltaTime * m_stDRResault.gfVelocity_CFI_WORLD[1];
		m_msgTransform.gfTransformVehicle2WorldVCUDR[0][3] = m_stDRResault.gfPos_CFI_WORLD[0] + DeltaTime * m_stDRResault.gfVelocity_CFI_WORLD[0];;
		m_msgTransform.gfTransformVehicle2WorldVCUDR[1][3] = m_stDRResault.gfPos_CFI_WORLD[1] + DeltaTime * m_stDRResault.gfVelocity_CFI_WORLD[1];;
		m_msgTransform.gfVehicleVelocityInWorldVCUDR[0] = m_stDRResault.gfVelocity_CFI_WORLD[0];
		m_msgTransform.gfVehicleVelocityInWorldVCUDR[1] = m_stDRResault.gfVelocity_CFI_WORLD[1];
	}
	m_msgTransform.bVCUDRValid = m_stDRResault.bValid;

	m_pLCM->publish("TRANSFORM", &m_msgTransform);
}


const bool CTransformer::DeadReckoningWithVehicleInfo(VCU_VEHILCE_INFO VehicleInfo)
{
	if (m_bTransformStarted == false)
	{
		ResetDRIntegrator();
		return false;
	}
	else
	{
		const float Heading = m_stRPVehicle2World.fYaw;
		if (m_stDRResault.bValid == false)
		{
			m_stDRResault.fDeltaTime = 0.0f;
			m_stDRResault.fHeading = Heading;
			m_stDRResault.fSpeed = (VehicleInfo.fRearLeftWheelSpeed + VehicleInfo.fRearRightWheelSpeed) * 0.5f * m_fRealSpeedVCUSpeedRatio;
			m_stDRResault.gfPos_CFI_WORLD[0] = m_msgTransform.gfVehiclePoseInWorld[0];
			m_stDRResault.gfPos_CFI_WORLD[1] = m_msgTransform.gfVehiclePoseInWorld[1];
			m_stDRResault.gfVelocity_CFI_WORLD[0] = m_stDRResault.fSpeed * cos(Heading);
			m_stDRResault.gfVelocity_CFI_WORLD[1] = m_stDRResault.fSpeed * sin(Heading);
			m_stDRResault.nTimeStamp = (int64_t)VehicleInfo.stHeader.nTimeStamp;
			m_stDRResault.bValid = true;
			return true;
		}
		else
		{
			float tempVx = m_stDRResault.gfVelocity_CFI_WORLD[0];
			float tempVy = m_stDRResault.gfVelocity_CFI_WORLD[1];

			m_stDRResault.fDeltaTime = ((int64_t)VehicleInfo.stHeader.nTimeStamp - (int64_t)m_stDRResault.nTimeStamp) * MICRO_SEC_TO_SEC;
			m_stDRResault.nTimeStamp = (int64_t)VehicleInfo.stHeader.nTimeStamp;
			m_stDRResault.fSpeed = (VehicleInfo.fRearLeftWheelSpeed + VehicleInfo.fRearRightWheelSpeed) * 0.5f * m_fRealSpeedVCUSpeedRatio;
			m_stDRResault.fHeading = Heading;
			m_stDRResault.gfVelocity_CFI_WORLD[0] = m_stDRResault.fSpeed * cos(Heading);
			m_stDRResault.gfVelocity_CFI_WORLD[1] = m_stDRResault.fSpeed * sin(Heading);

			m_stDRResault.gfPos_CFI_WORLD[0] = (tempVx + m_stDRResault.gfVelocity_CFI_WORLD[0]) * 0.5 * m_stDRResault.fDeltaTime + m_stDRResault.gfPos_CFI_WORLD[0];
			m_stDRResault.gfPos_CFI_WORLD[1] = (tempVy + m_stDRResault.gfVelocity_CFI_WORLD[1]) * 0.5 * m_stDRResault.fDeltaTime + m_stDRResault.gfPos_CFI_WORLD[1];

			return true;
		}
	}
}

const bool CTransformer::IsInitialized()
{
	return m_bIsLCMInitialized;
}

const bool CTransformer::InitializeLCM()
{
	m_pLCM = new lcm::LCM("udpm://239.255.76.67:7667?ttl=1");
	if (!m_pLCM->good())
	{
		PrintErrorInfo("Initialize communication error, please check the Ethernet connection", __FILE__, __FUNCTION__, __LINE__);
		return false;
	}

	//m_msgRawINS.stHeader.nCounter = 0;
	//m_msgRawINS.stHeader.nFrameID = CFI_VEHICLE;
	//m_msgRawINS.stHeader.nTimeStamp = GetGlobalTimeStampInMicroSec();

	m_msgTransform.stHeader.nCounter = 0;
	m_msgTransform.stHeader.nFrameID = CFI_VEHICLE;
	m_msgTransform.stHeader.nTimeStamp = GetLocalTimeStampInMicroSec();
	return true;
}

inline const bool CTransformer::CalculateTransformMatrix(const float x, const float y, const float z, const float yaw, const float pitch, const float roll, float(&transform)[4][4])
{
	float cosyaw = cos(yaw);
	float sinyaw = sin(yaw);
	float cospitch = cos(pitch);
	float sinpitch = sin(pitch);
	float cosroll = cos(roll);
	float sinroll = sin(roll);
	transform[0][0] = cosyaw*cospitch;
	transform[0][1] = cosyaw*sinroll*sinpitch - cosroll*sinyaw;
	transform[0][2] = sinyaw*sinroll + cosyaw*cosroll*sinpitch;
	transform[0][3] = x;

	transform[1][0] = cospitch*sinyaw;
	transform[1][1] = cosyaw*cosroll + sinyaw*sinroll*sinpitch;
	transform[1][2] = cosroll*sinyaw*sinpitch - cosyaw*sinroll;
	transform[1][3] = y;

	transform[2][0] = -sinpitch;
	transform[2][1] = cospitch*sinroll;
	transform[2][2] = cosroll*cospitch;
	transform[2][3] = z;

	transform[3][0] = 0.0f;
	transform[3][1] = 0.0f;
	transform[3][2] = 0.0f;
	transform[3][3] = 1.0f;
	return true;
}

inline const bool CTransformer::CalculateTransformMatrix(const CONST_RELATIVE_POSE &pose, float(&transform)[4][4])
{
	float cosyaw = cos(pose.fYaw);
	float sinyaw = sin(pose.fYaw);
	float cospitch = cos(pose.fPitch);
	float sinpitch = sin(pose.fPitch);
	float cosroll = cos(pose.fRoll);
	float sinroll = sin(pose.fRoll);
	transform[0][0] = cosyaw*cospitch;
	transform[0][1] = cosyaw*sinroll*sinpitch - cosroll*sinyaw;
	transform[0][2] = sinyaw*sinroll + cosyaw*cosroll*sinpitch;
	transform[0][3] = pose.fX;

	transform[1][0] = cospitch*sinyaw;
	transform[1][1] = cosyaw*cosroll + sinyaw*sinroll*sinpitch;
	transform[1][2] = cosroll*sinyaw*sinpitch - cosyaw*sinroll;
	transform[1][3] = pose.fY;

	transform[2][0] = -sinpitch;
	transform[2][1] = cospitch*sinroll;
	transform[2][2] = cosroll*cospitch;
	transform[2][3] = pose.fZ;

	transform[3][0] = 0.0f;
	transform[3][1] = 0.0f;
	transform[3][2] = 0.0f;
	transform[3][3] = 1.0f;
	return true;
}

inline const bool CTransformer::CalculateTransformMatrix(const RELATIVE_POSE &pose, float(&transform)[4][4])
{
	float cosyaw = cos(pose.fYaw);
	float sinyaw = sin(pose.fYaw);
	float cospitch = cos(pose.fPitch);
	float sinpitch = sin(pose.fPitch);
	float cosroll = cos(pose.fRoll);
	float sinroll = sin(pose.fRoll);
	transform[0][0] = cosyaw*cospitch;
	transform[0][1] = cosyaw*sinroll*sinpitch - cosroll*sinyaw;
	transform[0][2] = sinyaw*sinroll + cosyaw*cosroll*sinpitch;
	transform[0][3] = pose.fX;

	transform[1][0] = cospitch*sinyaw;
	transform[1][1] = cosyaw*cosroll + sinyaw*sinroll*sinpitch;
	transform[1][2] = cosroll*sinyaw*sinpitch - cosyaw*sinroll;
	transform[1][3] = pose.fY;

	transform[2][0] = -sinpitch;
	transform[2][1] = cospitch*sinroll;
	transform[2][2] = cosroll*cospitch;
	transform[2][3] = pose.fZ;

	transform[3][0] = 0.0f;
	transform[3][1] = 0.0f;
	transform[3][2] = 0.0f;
	transform[3][3] = 1.0f;
	return true;
}

inline const bool CTransformer::IntegrateVelocity(const float fVelNorth, const float fVelWest, const float fVelUp, int nDeltaTimeStamp)
{
	m_msgTransform.bReseted = 0x00;
	m_stVelocityIntegrator.fX += fVelNorth*nDeltaTimeStamp*1e-6;
	m_stVelocityIntegrator.fY += fVelWest*nDeltaTimeStamp*1e-6;
	m_stVelocityIntegrator.fZ += fVelUp*nDeltaTimeStamp*1e-6;
	return true;
}

inline const bool CTransformer::ResetVelocityIntegrator()
{
	m_msgTransform.bReseted = 0x01;
	m_stVelocityIntegrator.fX = 0.0;
	m_stVelocityIntegrator.fY = 0.0;
	m_stVelocityIntegrator.fZ = 0.0;
	return true;
}


inline const bool CTransformer::PrintTransform(const float(&transform)[4][4])
{
	fprintf(stderr, "===================================\n%.3f\t%.3f\t%.3f\t%.3f\n%.3f\t%.3f\t%.3f\t%.3f\n%.3f\t%.3f\t%.3f\t%.3f\n%.3f\t%.3f\t%.3f\t%.3f\n", transform[0][0], transform[0][1], transform[0][2], transform[0][3], transform[1][0], transform[1][1], transform[1][2], transform[1][3], transform[2][0], transform[2][1], transform[2][2], transform[2][3], transform[3][0], transform[3][1], transform[3][2], transform[3][3]);
}


const bool CTransformer::CalculateVehicle2WorldTransformMatrix(const RELATIVE_POSE& pose, float(&transform)[4][4])
{
	float cosyaw = cos(pose.fYaw);
	float sinyaw = sin(pose.fYaw);
	float cospitch = cos(pose.fPitch);
	float sinpitch = sin(pose.fPitch);
	float cosroll = cos(pose.fRoll);
	float sinroll = sin(pose.fRoll);
	transform[0][0] = cosyaw*cospitch;
	transform[1][0] = cosyaw*sinroll*sinpitch - cosroll*sinyaw;
	transform[2][0] = sinyaw*sinroll + cosyaw*cosroll*sinpitch;
	transform[3][0] = pose.fX;

	transform[0][1] = cospitch*sinyaw;
	transform[1][1] = cosyaw*cosroll + sinyaw*sinroll*sinpitch;
	transform[2][1] = cosroll*sinyaw*sinpitch - cosyaw*sinroll;
	transform[3][1] = pose.fY;

	transform[0][2] = -sinpitch;
	transform[1][2] = cospitch*sinroll;
	transform[2][2] = cosroll*cospitch;
	transform[3][2] = pose.fZ;

	return true;
}

inline const bool CTransformer::ResetDRIntegrator()
{
	m_stDRResault.nTimeStamp = 0;
	m_stDRResault.gfPos_CFI_WORLD[0] = 0.0f;
	m_stDRResault.gfPos_CFI_WORLD[1] = 0.0f;
	m_stDRResault.gfVelocity_CFI_WORLD[0] = 0.0f;
	m_stDRResault.gfVelocity_CFI_WORLD[1] = 0.0f;
	m_stDRResault.fDeltaTime = 0.0f;
	m_stDRResault.fHeading = 0.0f;
	m_stDRResault.fSpeed = 0.0f;
	m_stDRResault.bValid = false;
	return true;
}
