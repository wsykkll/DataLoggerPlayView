#pragma once
#include <qglviewer.h>
#include <manipulatedCameraFrame.h>
#include <QFileDialog>
#include "LCMSubscriber.h"
#include <lib3ds/file.h>
#include <lib3ds/node.h>
#include <lib3ds/camera.h>
#include <lib3ds/mesh.h>
#include <lib3ds/material.h>
#include <lib3ds/matrix.h>
#include <lib3ds/vector.h>
#include <lib3ds/light.h>
#include <vector>
#include <fstream>
using namespace std;

extern CLCMSubscriber* g_pLCMSubscriber;

enum CURRENT_CAMERA_VIEW
{
	CCV_WORLD,
	CCV_VEHICLE,
	CCV_VELODYNE,
	CCV_MOBILEYE,
	CCV_IBEO
};

struct DISPLAY_CONTROL
{
	//raw sensor info
	//====================================
	bool bRawImage;
	bool bRawVCU550;
	bool bRawINS;

	bool bRawFrontMWR;
	bool bRawESRNew;
	bool bRawESRNewUpdated;
	bool bRawESRUpdated;
	bool bRawESRCoasted;
	bool bRawLeftMWR;
	bool bRawRightMWR;

	bool bPrescanLanes;
	bool bPrescanPos;
	bool bPrescanMapLanes;

	bool bDetectedLanelines;
	bool bMapLanelinesMark;
	bool bDetectedTSR;
	bool bMapTSR;

	//preprocessed sensor info
	//====================================
	bool bFrontMWRFiltered;
	bool bESRACCObjects;
	bool bESRFCWObjects;
	bool bLeftSRRFiltered;
	bool bRightSRRFiltered;

	//Miscellanrous info
	//=====================================
	bool bVehicleModel;
	bool bCoordinates;
	bool bSquareGrids;
	bool bRadicalGrids;

	bool bLineBetweenCoordinate;
	bool bWorldCoordinate;
	bool bVehicleCoordinate;
	bool bCameraCoordinate;
	bool bFrontMWRCoordinate;
	bool bLeftMWRCoordinate;
	bool bRightMWRCoordinate;

	bool bLane1;
	bool bLane2;
	bool bLane3;
	bool bLane4;
	bool bMapLanelinesCalibrated;
	bool bMapLanelinesProcess;

	CURRENT_CAMERA_VIEW stCurrentCameraView;

	DISPLAY_CONTROL()
	{
		bRawImage = true;
		bRawINS = true;
		bRawVCU550 = true;

		bRawFrontMWR = false;
		bRawESRNew = false;
		bRawESRNewUpdated = false;
		bRawESRUpdated = false;
		bRawESRCoasted = false;
		bRawLeftMWR = false;
		bRawRightMWR = false;

		bPrescanLanes = false;
		bPrescanPos = false;
		bPrescanMapLanes = true;

		bDetectedLanelines = false;
		bMapLanelinesMark = false;
		bDetectedTSR = false;
		bMapTSR = true;

		bFrontMWRFiltered = false;
		bESRACCObjects = false;
		bESRFCWObjects = false;
		bLeftSRRFiltered = false;
		bRightSRRFiltered = false;

		bVehicleModel = true;
		bCoordinates = true;
		bSquareGrids = true;
		bRadicalGrids = false;

		bLineBetweenCoordinate = false;
		bWorldCoordinate = true;
		bVehicleCoordinate = true;
		bCameraCoordinate = true;
		bFrontMWRCoordinate = true;
		bLeftMWRCoordinate = true;
		bRightMWRCoordinate = true;

		bLane1 = false;
		bLane2 = false;
		bLane3 = false;
		bLane4 = false;
		bMapLanelinesCalibrated = false;
		bMapLanelinesProcess = false;
	}
};


class CQGLViewer :
	public QGLViewer
{
public:
	CQGLViewer(QWidget* parent);
	~CQGLViewer();

	DISPLAY_CONTROL m_stDisplayControl;

private:
	int m_nScreenTextX;
	int m_nScreenTextY;
	QFont m_qFont2DText;
	Lib3dsFile* m_p3dsFile;
	char* m_p3dsCameraName;

	void InitializeScene();
	const bool Load3dsModel();
	void Render3dsNode(Lib3dsNode* node);

	void DrawCoordinatesSystem();
	void DrawGrids();
	void DrawVehicleModel();
	void DrawPrescanLanes();
	void DrawRawMWR();
	void Draw3DText(const std::vector<TEXT_3D>& vecText3D, COLOR_4UB color);
	void Draw3DText(const TEXT_3D& text3D, COLOR_4UB color);
	void DrawRawRTK();
	void DrawImage();
	void DrawVehInfo();
	void DrawTSRInfo();
protected:
	virtual void draw();
	virtual QString helpString() const;
	virtual void init();

	
};

