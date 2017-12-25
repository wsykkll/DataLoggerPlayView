#pragma once
#include "global.hpp"
#include "VCU_VEHILCE_INFO.hpp"
#include "RTK.hpp"
#include "TRANSFORM.hpp"
#include "METGPSInfo_Lcm.hpp"

struct DEADRECKONING_RESULT
{
	long nTimeStamp;
	float gfPos_CFI_WORLD[2];
	float gfVelocity_CFI_WORLD[2];
	float fDeltaTime;
	float fHeading;
	float fSpeed;
	bool bValid;
};

//struct INS_RAW_DATA
//{
//	unsigned long nTimeStamp;
//	long int nGPSTimeStamp;
//
//	double fLatitude;
//	double fLongitude;
//	float fAltitude;
//
//	float fHeading;
//	float fPitch;
//	float fRoll;
//
//	float fVelNorth;
//	float fVelWest;
//	float fVelUp;
//
//	float fAccX;
//	float fAccY;
//	float fAccZ;
//
//	float fGyroX;
//	float fGyroY;
//	float fGyroZ;
//};

struct RTK_RAW_DATA
{
	unsigned long long nTimeStamp;
	long long int nGPSTimeStamp;

	double fLatitude;
	double fLongitude;
	float fAltitude;

	float fHeading;
	float fPitch;
	float fRoll;

	float fVelNorth;
	float fVelWest;
	float fVelUp;
};

struct VELOCITY_INTEGRATOR
{
	float fX;
	float fY;
	float fZ;
	VELOCITY_INTEGRATOR()
	{
		fX = 0.0;
		fY = 0.0;
		fZ = 0.0;
	}
};

struct CONST_RELATIVE_POSE
{
	const float fX;
	const float fY;
	const float fZ;
	const float fYaw;
	const float fPitch;
	const float fRoll;
	CONST_RELATIVE_POSE(float x, float y, float z, float yaw, float pitch, float roll) :
		fX(x), fY(y), fZ(z), fYaw(yaw), fPitch(pitch), fRoll(roll)
	{}
};

struct RELATIVE_POSE
{
	float fX;
	float fY;
	float fZ;
	float fYaw;
	float fPitch;
	float fRoll;
	RELATIVE_POSE(float x = 0.0f, float y = 0.0f, float z = 0.0f, float yaw = 0.0f, float pitch = 0.0f, float roll = 0.0f) :
		fX(x), fY(y), fZ(z), fYaw(yaw), fPitch(pitch), fRoll(roll)
	{}
};


class CTransformer
{
public:
	CTransformer();
	~CTransformer();

	void Transform(const RTK_RAW_DATA& rtk, bool bStartTransform=false);
	const bool DeadReckoningWithVehicleInfo(VCU_VEHILCE_INFO VehicleInfo);
	const bool IsInitialized();

private:
	const bool InitializeLCM();
	const bool CalculateTransformMatrix(const float x, const float y, const float z, const float yaw, const float pitch, const float roll, float(&transform)[4][4]);
	const bool CalculateTransformMatrix(const RELATIVE_POSE& pose, float(&transform)[4][4]);
	const bool CalculateTransformMatrix(const CONST_RELATIVE_POSE& pose, float(&transform)[4][4]);
	const bool CalculateVehicle2WorldTransformMatrix(const RELATIVE_POSE& pose, float(&transform)[4][4]);
	const bool IntegrateVelocity(const float fVelNorth, const float fVelWest, const float fVelUp, int nDeltaTimeStamp);
	const bool ResetVelocityIntegrator();
	const bool PrintTransform(const float(&transform)[4][4]);
	inline const bool ResetDRIntegrator();

	long long int m_nLastTimeStamp;
	bool m_bTransformStarted;
	lcm::LCM* m_pLCM;
	bool m_bIsLCMInitialized;
	TRANSFORM m_msgTransform;
	VELOCITY_INTEGRATOR m_stVelocityIntegrator;

	CONST_RELATIVE_POSE m_stRPCamera2Vehicle;
	CONST_RELATIVE_POSE m_stRPMWR2Vehicle;
	CONST_RELATIVE_POSE m_stRPLeftSRR2Vehicle;
	CONST_RELATIVE_POSE m_stRPRightSRR2Vehicle;

	RELATIVE_POSE m_stRPVehicle2World;

	const float m_fRealSpeedVCUSpeedRatio;
	DEADRECKONING_RESULT m_stDRResault;

};

