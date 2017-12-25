#pragma once

#include <GL\freeglut.h>
#include "global.hpp"
#include "METImageObject_Lcm.hpp"
#include "LaneMarkPointsList.hpp"
#include "VehiclePosture.hpp"
#include "METGPSInfo_Lcm.hpp"
#include "POSTURE.hpp"
#include <libjpeg/jpeglib.h>
#include "TSRCALIBRATION.hpp"
#include "DrawElement.h"
#include "DrawCoordinates.h"
#include "CoordinateTrans/CoordinateTrans.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "tinyxml2.h"
#include "MAP.h"
#include "MapGraph.h"
#include <list>
using namespace tinyxml2;

//#define CALCULATEPOSTURE
//#define ROUTE1//start 
//#define DRAWSECTIONBOX
//#define DRAWROADBOX

#define BEZIER_NUM 50

struct VehPosture
{
	double local_x;
	double local_y;
	double dLatitude;
	double dLongitude;
	double dHeading;
	double dSpeed;
	VehPosture()
	{
		local_x = 0.0f;
		local_y = 0.0f;
		dLatitude = 0.0f;
		dLongitude = 0.0f;
		dHeading = 0.0f;
		dSpeed = 0.0f;
	}
};

struct LogPoint
{
	double x;
	double y;
	double theta;
	int64_t ntimestamp;

	LogPoint()
	{
		x = 0;
		y = 0;
		theta = 0;
		ntimestamp = 0;
	}
};

struct CalibrationTSR
{
	double dPosx;
	double dPosy;
	float fWidth;
	float fHeight;
	float fHeight_;
	float fHeading;
	int iColor;
	CalibrationTSR()
	{
		dPosy = 0.0;
		dPosx = 0.0;
		fWidth = 0.0f;
		fHeight = 0.0f;
		fHeight_ = 0.0f;
		fHeading = 0.0f;
		iColor = 0;
	}
};

struct TPoint
{
	int iPointID;
	double dLatitude;
	double dLongitude;
	TPoint()
	{
		iPointID = 0;
		dLatitude = 0.0;
		dLongitude = 0.0;
	}
};

struct TLineSegment
{
	int iSegID;
	int iPointNum;
	vector<TPoint> vec_Points;
	TLineSegment()
	{
		iSegID = 0;
		iPointNum = 0;
	}
};

struct TLaneLine
{
	int iLanelineID;
	int iLanelineType;
	int iLanelineColor;
	int iSegNum;
	vector<TLineSegment> vec_Segments;
	TLaneLine()
	{
		iLanelineID = 0;
		iLanelineType = 0;
		iLanelineColor = 0;
		iSegNum = 0;
	}
};

struct TMAP
{
	TPoint stVehPos;
	vector<TLaneLine> vec_Lanelines;
};

class CDrawCamera
{
public:
	CDrawCamera();
	~CDrawCamera();

	void DecodeCameraImage(const lcm::ReceiveBuffer* recvBuf);
	void DecodeTSRInfo(const lcm::ReceiveBuffer* recvBuf);
	void GLDrawCameraImage(int &width, int &height);
	void GLDrawTSRInfo(CDrawCoordinates& coordinates);
	bool m_bRecrveImg;

	void DecodeLaneMarkPoint(const lcm::ReceiveBuffer* recvBuf);
	void GLDrawLaneMarkPoints(CDrawCoordinates& coordinates);
	void GLDrawMapMarkPoints(CDrawCoordinates& coordinates);

	void LoadLaneMark();
	void LoadLaneMarkTotally();
	void LoadTSRInfo();
	void LoadCalibrationLanelines();
	void LoadMap();
	bool m_bIsMapLoaded;
	METMAP m_stMap;

	//Test
	void GLDrawLane1MarkPoints(CDrawCoordinates& coordinates);
	void GLDrawLane2MarkPoints(CDrawCoordinates& coordinates);
	void GLDrawLane3MarkPoints(CDrawCoordinates& coordinates);
	void GLDrawLane4MarkPoints(CDrawCoordinates& coordinates);
	void GLDrawCalibrationLaneLines(CDrawCoordinates& coordinates);
	void GLDrawMapLanelineProcess(CDrawCoordinates& coordinates);
	void GLDrawMap(CDrawCoordinates& coordinates);
	void GLDrawLocalMap(CDrawCoordinates& coordinates);
	void GLDrawMETLine(METLine line);
	double DistanceVeh2Line(METLine* line);

	void GLDrawMapLanelineProcessNext(CDrawCoordinates& coordinates);

	double GPGGA2WGS(double dGpgga);

	void GLDrawMapTSRPoints(CDrawCoordinates& coordinates);
	void DecodeVehiclePosture(const lcm::ReceiveBuffer* recvBuf);
	void DecodeVehRTKInfo(const lcm::ReceiveBuffer* recvBuf);
	void DecodeNextPosture(const lcm::ReceiveBuffer* recvBuf);

private:
	//void jpgtobmp(const char* strSRC)

	boost::mutex m_mtuImage;
	boost::mutex m_mtxtsr;
	boost::mutex m_mtxRTK;
	boost::mutex m_mtxNextPos;
	//TSRInfo m_msgTsrInfo;
	TSRCALIBRATION m_msgTsrInfo;
	TSRInfo m_stMapTSR;
	METImageObject_Lcm m_msgImage;
	METGPSInfo_Lcm m_msgRTKInfo;

	bool m_bMapLoaded;//whether loaded the point map
	bool m_bPostureReceived;
	bool m_bMapSplitLoaded;
	bool m_bMapCalibrationLoaded;
	bool m_bMapTSRLoaded;

	double m_dLastHeading;
	int64_t m_iLastRecvPosTime;

	vector<LogPoint> m_vecLaneMapPoints;
	vector<LogPoint> m_vecLane1MapPoints;
	vector<LogPoint> m_vecLane2MapPoints;
	vector<LogPoint> m_vecLane3MapPoints;
	vector<LogPoint> m_vecLane4MapPoints;
	vector<LogPoint> m_vecMapGPSPoints;
	vector<CalibrationTSR> m_vecMapTSR;
	//vector<PointXY> m_vecLaneMapPoints;

	TMAP m_stTMap;
	CMapGraph m_stMapGraph;
	void CreateMapGraph();

	IplImage* m_pImg;
	int m_nImageW;
	int m_nImageH;
	//Mat m_msgMatImg;

	boost::mutex m_mtxLaneMarkPonits;
	LaneMarkPointsList m_msgLaneMarkPointsList;
	boost::mutex m_mtxVehPosture;
	VehiclePosture m_msgVehiclePosture;
	bool m_bLanemarkReceived;

	int64_t m_nlastPosTimestamp;
	int64_t m_nCurrentTimestamp;
	bool m_bCalLocalPos;
	double m_dInitLatitude;
	double m_dInitLongitude;
	VehPosture m_stVehiclePos;
	POSTURE m_msgNextPosture;

	void PrintMatrix(CvMat *Matrix, int Rows, int Cols, int Channels);
	vector<PointXY> GenerateBezier(PointXY* Anchor1, PointXY* Anchor2, PointXY* Control, int NUM);
	PointXY CrossPoint(PointXY p1, PointXY p2);
};

