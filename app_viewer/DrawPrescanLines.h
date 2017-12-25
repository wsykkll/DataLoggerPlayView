#pragma once
#include "PRESCAN_LANES.hpp"
#include "global.hpp"
#include "DrawCoordinates.h"
#include "DrawElement.h"
#include "PRESCANIMG.hpp"
#include <QStringList>
#include "RTK.hpp"
#include "PERCEPTION_LINES.hpp"
//#include "Notation.h"
#include "CoordinateTrans/CoordinateTrans.h"
#include <opencv\cv.h>
#include <opencv\highgui.h>

struct GPS_Point
{
	double dLatitude;
	double dLongitude;
};

class CDrawPrescanLines
{
public:
	CDrawPrescanLines();
	~CDrawPrescanLines();

	void DecodePrescanLinesMsg(const PRESCAN_LANES* msg);
	void DecodeMapLines(const lcm::ReceiveBuffer* recvBuf);
	void GLDrawPrescanLines(CDrawCoordinates& coordinates);
	void GLDrawMapLines(CDrawCoordinates& coordinates);
	void GLDrawPrescanMapLines(CDrawCoordinates& coordinates);
	void DecodePrescanIMG(const lcm::ReceiveBuffer* recvBuf);
	void GLDrawPrescanIMG(int &width, int &height);
	void DecodePrescanRTK(const lcm::ReceiveBuffer* recvBuf);
	const QStringList GetRTKStringList(float& velocity);
private:
	IplImage* m_pImgRMsg;
	IplImage* m_pImgGMsg;
	IplImage* m_pImgBMsg;
	IplImage* m_pImgRGB;
	int m_nImageW;
	int m_nImageH;
	bool m_bImgReveived;
	bool m_bMapLoaded;

	boost::mutex m_mtuPrescanLines;
	PRESCAN_LANES m_msgPrescanLines;
	boost::mutex m_mtuPrescanIMG;
	PRESCANIMG m_msgPrescanIMG;
	CDrawElement m_stElementDrawer;
	boost::mutex m_mtxPrescanRTK;
	RTK m_msgPrescanRTK;

	boost::mutex m_mtxMapLines;
	PERCEPTION_LINES m_msgMapLines;

	vector<GPS_Point> m_vecLaneMapPoints;
};

