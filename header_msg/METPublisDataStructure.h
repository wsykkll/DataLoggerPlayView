#ifndef _MET_METPUBLISDATASTRUCTURE_H__
#define _MET_METPUBLISDATASTRUCTURE_H__

#include <Windows.h>		/*system time*/


enum METMessageType
{
	MET_CARCAN_SPEED = 1,//float			vehicle_speed;					/*speed: 0~500km/h, accuracy: 0.1km/h*/
	MET_CARCAN_WHEELANGLE = 2,//float			steering_wheel_angle;			/*steering wheel angle: -1000~1000 degree, accuracy: 0.1 degree*/
	MET_CARCAN_ACCPEDALPOS = 3,//float			accelerator_pedal_pos;			/*accelerator pedal position: 0~100%, accuracy: 0.1%*/
	MET_CARCAN_ACCPEDALSPEED = 4,//short			accelerator_pedal_speed;		/*val:-5120~5080, unit:%/s*/
	MET_CARCAN_BRKPEDALPOS = 5,//float			brake_pedal_pos;				/*brake pedal position: 0~100%, accuracy: 0.1%*/
	MET_CARCAN_YAWRATE = 6,//float			vehicle_yaw_rate;				/*vehicle yaw rate: -255~255 degree/s, accuracy: 0.1 degree/s*/
	MET_CARCAN_TURNLIGHTSTATUS = 7,//unsigned char	Lft_turnlight_active;			/*left turn light active tag, 1-yes, 0-no*/
	MET_CARCAN_WINDWIPERSTATUS = 8,//unsigned char	windWiperStatus;				/*val:0-10, speed level*/
	MET_CARCAN_LIGHTSENSOR = 9,//short			light_sensor_val;				/*light sensor value*/
	MET_CARCAN_RAINSENSOR = 10,//unsigned char	rain_sensor_val;				/*rain sensor value*/
	MET_CARCAN_BEAMSTATUS = 11,//unsigned char	lowBeamStatus;					/*0-closed, 1-open*/
	MET_CARCAN_ENVIRLIGHTSTATUS = 12,//unsigned char	envirLightStatus;				/*0-unknown, 1- night, 2-day*/
	MET_CARCAN_BRKPEDALGRD = 13,//short			brakePedalGrd;					/*val:-5120~5080, unit:%/s*/
	MET_CARCAN_BRKPEDALFLAG = 14,//unsigned char	brakePedalFlag;					/*val 0:no brake 1:brake */
	MET_CARCAN_TEMPERATURE = 15,//float			temperatureValue;				/*val:-40~87.5, unit: degree Celsius, accuracy: 0.5*/
	MET_CARCAN_STEERWHEELSPEED = 16,//short			steeringWheelSpeed;				/*val:-2048~2057, unit:degree/s, accuracy: 1*/
	MET_CARCAN_GEARSTATUS = 17,//METGearInfo		gearInfo;						/*-3:unknown, -2:stop, -1:backup,0:neutral,1:advance,2:level1,
	MET_CARCAN_ESTIMATEDGEAR = 18,//unsigned char	estimated_gear;
	MET_CARCAN_MILEAGE = 19,//int				mileage;						/*0~1000000, unit:km*/
	MET_CARCAN_GPS_X = 20,
	MET_CARCAN_GPS_Y = 21,
	MET_CARCAN_GPS_Z = 22,//METVehicleGPSInfo	gpsInfo;
	// AEB //////////////////////////////////////////////////////////////////
	MET_CARCAN_BRAKEFAIL = 23,//unsigned char   aeb_brake_failed;
	MET_CARCAN_ENGINE_MIN_TORQUEVAL = 24,//short			engine_min_torque_value;
	MET_CARCAN_ENGINE_MAX_TORQUEVAL = 25,//short			engine_max_torque_value;
	MET_CARCAN_ENGINE_CUR_TORQUEVAL = 26,//short			engine_cur_torque_value;
	// ACC //////////////////////////////////////////////////////////////////
	MET_CARCAN_ACCBRKFAIL = 27,//unsigned char	acc_brake_failed;
	MET_CARCAN_CRUISECTRLENABLE = 28,//unsigned char	cruise_control_enable;
	MET_CARCAN_CRUISEGAPSWITCH = 29,//unsigned char	cruise_gap_switch_activation;
	MET_CARCAN_CRUISESECONDARYSWITH = 30,//unsigned char	cruise_secondary_switch_status;
	MET_CARCAN_CRUISESPEEDLIMITSWITCH = 31,//unsigned char	cruise_speed_limit_switch_status;
	// LKA //////////////////////////////////////////////////////////////////
	MET_CARCAN_LKAOVERLAYTORQUE = 32,//unsigned char	lka_overlay_torque_status;
	MET_CARCAN_LKASTEERTOTALTORQUE = 33,//float			lka_steering_total_torque;
	MET_CARCAN_LKASTEERWHEELMODE = 34,//unsigned char	lka_handoff_steering_wheel_mode;
	MET_CARCAN_LKAHANDOFFSTAT = 35,//unsigned char	lka_handoff_steering_wheel_stat;
	MET_CARCAN_LKADELTATORQUE = 36,//float			lka_steering_delta_torque;
	MET_CARCAN_LKADRIVERAPPLIEDTORQUE = 37,//float			lka_driver_applied_torque;
	MET_CARCAN_LATERALACCPRIMARY = 38,//float			lateral_acceleration_primary;
	MET_CARCAN_LATERALACCSECONDARY = 39,//float			lateral_acceleration_secondary;
	MET_CARCAN_LONGITUDINALACCPRIMARY = 40,//float			longitudinal_acceleration_primary;
	MET_CARCAN_LONGITUDINALACCSECONDARY = 41,//float			longitudinal_acceleration_secondary;
	MET_CARCAN_YAWRATEPRIMARY = 42,//float			yawrate_primary;
	MET_CARCAN_YAWRATESECONDARY = 43,//float			yawrate_secondary;
	MET_CARCAN_WHEELBRKPRESSUREESTIMATED = 44,//float			wheel_brake_pressure_estimated;
	MET_CARCAN_BRKACTUALDECELERATION = 45,//float			braking_actual_deceleration;
	MET_CARCAN_BRKTARGETDECELERATION = 46,//float			braking_target_deceleration;
	MET_CARCAN_GATEWAYBUTTON = 47,//unsigned char	gateway_button;
	MET_CARCAN_WHEELSTATUSFEBACKZCSD = 48,//unsigned char	wheel_status_feback_zcsd;
	//////////////////////////////////////////////////////////////////////////////////////////////
	MET_RTK = 49,//ouble    
	//////////////////////////////////////////////////////////////////////////////////////////////
	MET_RADAR_ESR_STAT = 81,
	MET_RADAR_ESR_OBJ = 82,
	MET_RADAR_SRR_LFT_OBJ = 83,
	MET_RADAR_SRR_RGT_OBJ = 84
};


typedef struct METPublisCANEvent
{
	METMessageType	messageType;
	SYSTEMTIME		messageTime;
	double			messageval;
}METPublisCANEvent;

typedef struct METPublisRADARStatEvent
{
	METMessageType		messageType;
	SYSTEMTIME			messageTime;
	unsigned char		objCount;
	unsigned char		ACC_Traget_ID;
	unsigned char		ACC_Stat_ID;
	unsigned char		CMBB_Move_ID;
	unsigned char		CMBB_Stat_ID;
	unsigned char		FCW_Move_ID;
	unsigned char		FCW_Stat_ID;
}METPublisRADARStatEvent;

typedef struct METPublisRADARObjEvent
{
	METMessageType	messageType;
	SYSTEMTIME		messageTime;
	unsigned char	objID;
	unsigned char	trackMEDRangeMode;		//val: 0~3, 2 bit, factor:1
	unsigned char	trackBridgeObject;		//val: 0~0, 1 bit, factor:1
	float			trackLATRate;			//val:-8~7.75, 6 bit, factor:0.25
	unsigned char	trackRollingCount;		//val:0~1, 1 bit, factor:1
	unsigned char	trackStatus;			//val: 0~7, 3 bit, factor:1
	float			trackWidth;				//val:0~7.5, 4 bit, factor: 0.5, unit: m
	unsigned char	trackOnComing;			//val:0~0, 1 bit, factor: 1
	float			trackRange;				//val:0~204.7, 11 bit, float: 0.1, unit: m
	float			trackRangeRate;			//val:-81.92~81.91, 14 bit, factor: 0.01, unit: m/s
	float			trackRangeAccel;		//val:-25.6~25.55, 10 bit, factor: 0.05, unit:m/s/s
	float			trackAngle;				//val:-51.2~51.1, 10 bit, factor: 0.1; unit: degree
	unsigned char	trackGroupingChanged;	//val:0~0, 1 bit, factor: 1
}METPublisRADARObjEvent;

typedef struct METSRRRADARObjEvent
{
	METMessageType	messageType;
	SYSTEMTIME		messageTime;
	unsigned char	SideFlag;			// 0:Left 1:Right
	unsigned char	objID;				// 0-6
	float			fDetectRange;		//val: 0~204.7,		16 bit, factor:0.0078125
	float			fDetectRangeRate;	//val: -81.9~81.9,	16 bit, factor:0.0078125
	float			fDetectAmplitude;	//val: -24~40,		12 bit, factor:0.125
	unsigned char	ucDetectValidLevel;	//val: 0~0,			3  bit, factor:1
	unsigned char	ucDetectStatus;		//val: 0~0,			1  bit, factor:1
	float			fDetectAngle;		//val: -102.4~102.2	16 bit, factor:0.0078125
}METSRRRADARObjEvent;

typedef struct METPublicRTKEvent
{
	METMessageType	messageType;
	SYSTEMTIME		GGAmessageTime;
	SYSTEMTIME		RMCmessageTime;
	SYSTEMTIME		TRAmessageTime;
	double			GGA_dwUtc;
	double			GGA_dwLat;
	unsigned char   GGA_cLatdir;
	double			GGA_dwLon;
	uint8_t    		GGA_cLondir;
	int64_t			GGA_nQF;
	int64_t			GGA_nSatNo;
	double			GGA_dwHdop;
	double			GGA_dwAlt;
	uint8_t			GGA_cAUnits;
	int64_t			GGA_nAge;
	int64_t			GGA_nStnID;
	double			RMC_dwUtc;
	uint8_t			RMC_cPosStatus;
	double			RMC_dwLat;
	uint8_t			RMC_cLatDir;
	double			RMC_dwLon;
	uint8_t			RMC_cLonDir;
	double			RMC_dwSpeedIn;
	double			RMC_dwTrackTrue;
	int64_t			RMC_nDate;
	double			RMC_dwMagVar;
	uint8_t			RMC_cVarDir;
	uint8_t			RMC_cModeInd;
	double			TRA_dwUtc;
	double			TRA_dwHeading;
	double			TRA_dwPitch;
	int64_t			TRA_nRoll;
	int64_t			TRA_nQF;
	int64_t			TRA_nSatNo;
	double			TRA_dwAge;
	int64_t			TRA_nStnID;
}METPublicRTKEvent;

#endif