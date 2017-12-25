#include "DrawPrescanLines.h"


CDrawPrescanLines::CDrawPrescanLines() :
m_nImageW(1280),
m_nImageH(960),
m_bMapLoaded(false),
m_bImgReveived(false)
{
	m_pImgRMsg = cvCreateImage(cvSize(m_nImageW, m_nImageH), IPL_DEPTH_8U, 1);
	m_pImgGMsg = cvCreateImage(cvSize(m_nImageW, m_nImageH), IPL_DEPTH_8U, 1);
	m_pImgBMsg = cvCreateImage(cvSize(m_nImageW, m_nImageH), IPL_DEPTH_8U, 1);
	m_pImgRGB = cvCreateImage(cvSize(m_nImageW, m_nImageH), IPL_DEPTH_8U, 3);

	fstream calibrateFile;
	char fileName[100] = { '\0' };
	sprintf_s(fileName, "LogLaneLineLocal.txt");
	calibrateFile.open(fileName, ios::in);
	if (calibrateFile)
	{
		GPS_Point tmp_point;
		string msg;
		double calibration_num;
		vector<double> Calibration_msg;
		while (!calibrateFile.eof())
		{
			getline(calibrateFile, msg);
			istringstream m(msg);
			while (m >> calibration_num)
			{
				Calibration_msg.push_back(calibration_num);
			}
		}
		vector<double>::iterator it = Calibration_msg.begin();
		for (; it != Calibration_msg.end(); it = it + 2)
		{
			tmp_point.dLatitude = *it;
			tmp_point.dLongitude = *(it + 1);
			m_vecLaneMapPoints.push_back(tmp_point);
		}
		m_bMapLoaded = true;
	}
}


CDrawPrescanLines::~CDrawPrescanLines()
{
	delete m_pImgBMsg;
	delete m_pImgGMsg;
	delete m_pImgRMsg;
	delete m_pImgRGB;
}

void CDrawPrescanLines::DecodePrescanLinesMsg(const PRESCAN_LANES* msg)
{
	m_mtuPrescanLines.lock();
	memcpy(&m_msgPrescanLines, msg, sizeof(PRESCAN_LANES));
	m_mtuPrescanLines.unlock();
}

void CDrawPrescanLines::DecodeMapLines(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtxMapLines.lock();
	m_msgMapLines.decode(recvBuf->data, 0, recvBuf->data_size);
	m_mtxMapLines.unlock();
}

void CDrawPrescanLines::GLDrawMapLines(CDrawCoordinates& coordinates)
{
	m_mtxMapLines.lock();
	coordinates.GLSwitch2Coordinates(m_msgPrescanLines.stHeader.nTimeStamp, CFI_MOBILEYE);
	glEnable(GL_BLEND);
	//glColor3ub(170, 170, 100);
	glLineWidth(2.0);
	if (m_msgMapLines.bRightRightLine)
	{
		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 0, 0);
		glVertex3f(m_msgMapLines.gfRightRightLineY[0] * 100.0f, -m_msgMapLines.gfRightRightLineX[0] * 100.0f, 0.0f);
		glVertex3f(m_msgMapLines.gfRightRightLineY[1] * 100.0f, -m_msgMapLines.gfRightRightLineX[1] * 100.0f, 0.0f);
		glColor3ub(170, 170, 100);
		for (int i = 2; i < (m_msgMapLines.nRightRightArrayLength + 99); i++)
		{
			glVertex3f(m_msgMapLines.gfRightRightLineY[i] * 100.0f, -m_msgMapLines.gfRightRightLineX[i] * 100.0f, 0.0f);
		}
		glEnd();
	}
	if (m_msgMapLines.bRightLine)
	{
		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 0, 0);
		glVertex3f(m_msgMapLines.gfRightLineY[0] * 100.0f, -m_msgMapLines.gfRightLineX[0] * 100.0f, 0.0f);
		glVertex3f(m_msgMapLines.gfRightLineY[1] * 100.0f, -m_msgMapLines.gfRightLineX[1] * 100.0f, 0.0f);
		glColor3ub(170, 170, 100);
		for (int i = 2; i < (m_msgMapLines.nRightArrayLength+99); i++)
		{
			glVertex3f(m_msgMapLines.gfRightLineY[i] * 100.0f, -m_msgMapLines.gfRightLineX[i] * 100.0f, 0.0f);
		}
		glEnd();
	}
	if (m_msgMapLines.bLeftLine)
	{
		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 0, 0);
		glVertex3f(m_msgMapLines.gfLeftLineY[0] * 100.0f, -m_msgMapLines.gfLeftLineX[0] * 100.0f, 0.0f);
		glVertex3f(m_msgMapLines.gfLeftLineY[1] * 100.0f, -m_msgMapLines.gfLeftLineX[1] * 100.0f, 0.0f);
		glColor3ub(170, 170, 100);
		for (int i = 2; i < (m_msgMapLines.nLeftArrayLength + 99); i++)
		{
			glVertex3f(m_msgMapLines.gfLeftLineY[i] * 100.0f, -m_msgMapLines.gfLeftLineX[i] * 100.0f, 0.0f);
		}
		glEnd();
	}
	if (m_msgMapLines.bLeftLeftLine)
	{
		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 0, 0);
		glVertex3f(m_msgMapLines.gfLeftLeftLineY[0] * 100.0f, -m_msgMapLines.gfLeftLeftLineX[0] * 100.0f, 0.0f);
		glVertex3f(m_msgMapLines.gfLeftLeftLineY[1] * 100.0f, -m_msgMapLines.gfLeftLeftLineX[1] * 100.0f, 0.0f);
		glColor3ub(170, 170, 100);
		for (int i = 2; i < (m_msgMapLines.nLeftLeftArrayLength + 99); i++)
		{
			glVertex3f(m_msgMapLines.gfLeftLeftLineY[i] * 100.0f, -m_msgMapLines.gfLeftLeftLineX[i] * 100.0f, 0.0f);
		}
		glEnd();
	}
	glDisable(GL_BLEND);
	m_mtxMapLines.unlock();
}

void CDrawPrescanLines::DecodePrescanIMG(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtuPrescanIMG.lock();
	m_msgPrescanIMG.decode(recvBuf->data, 0, recvBuf->data_size);
	m_bImgReveived = true;
	m_mtuPrescanIMG.unlock();
}

void CDrawPrescanLines::GLDrawPrescanMapLines(CDrawCoordinates& coordinates)
{
	m_mtxPrescanRTK.lock();
	if (m_bMapLoaded)
	{
		coordinates.GLSwitch2Coordinates(m_msgPrescanLines.stHeader.nTimeStamp, CFI_MOBILEYE);
		COLOR_3UB linecolor(255, 0, 255);
		glEnable(GL_BLEND);
		//glLineWidth(2.0);
		glPointSize(2.0f);
		glColor4ub(linecolor.cR, linecolor.cG, linecolor.cB, 0xFF);
		glBegin(GL_POINTS);
		vector<GPS_Point>::iterator it = m_vecLaneMapPoints.begin();
		for (; it != m_vecLaneMapPoints.end();it++)
		{
			//GPS_Point tmpP = *it;
			//if (DistanceInGps(m_msgPrescanRTK.dLatitude,m_msgPrescanRTK.dLongitude,it->dLatitude,it->dLongitude)<50)
			//{
				//PointXY tmpPoint = GCS2CCS(m_msgPrescanRTK.dLatitude, m_msgPrescanRTK.dLongitude, it->dLatitude, it->dLongitude);
				
			PointXY RelativePos;
			RelativePos.x = it->dLatitude - m_msgPrescanRTK.fPosX;
			RelativePos.y = it->dLongitude - m_msgPrescanRTK.fPosY;
			PointXY TP;
			TP.x = cos(m_msgPrescanRTK.fHeading)*RelativePos.x - sin(m_msgPrescanRTK.fHeading)*RelativePos.y;
			TP.y = sin(m_msgPrescanRTK.fHeading)*RelativePos.x + cos(m_msgPrescanRTK.fHeading)*RelativePos.y;

			glVertex3f(TP.y*100.0f, -TP.x*100.0f, 0.0f);
				//glVertex3f(TP.y*100.0f, -TP.x*100.0f, 0.0f);
			//}
		}
		glEnd();
	}
	m_mtxPrescanRTK.unlock();
}

void CDrawPrescanLines::GLDrawPrescanLines(CDrawCoordinates& coordinates)
{
	m_mtuPrescanLines.lock();
	coordinates.GLSwitch2Coordinates(m_msgPrescanLines.stHeader.nTimeStamp, CFI_MOBILEYE);
	COLOR_3UB linecolor(255, 255, 255);

	glEnable(GL_BLEND);
	glLineWidth(2.0);
	glPointSize(5.0f);

	for (unsigned int index = 0; index < 20; index++)
	{
		int b_valid = m_msgPrescanLines.gLines[index].bValid;
		if (b_valid < 1)
		{
			continue;
		}

		float ftmpLength = m_msgPrescanLines.gLines[index].fLength;
		int linelabel = m_msgPrescanLines.gLines[index].nLineLabel;
		linelabel = linelabel % 3;
		float xa = m_msgPrescanLines.gLines[index].fX0;
		float xb = m_msgPrescanLines.gLines[index].fX1;
		float xc = m_msgPrescanLines.gLines[index].fX2;
		float xd = m_msgPrescanLines.gLines[index].fX3;
		float ya = m_msgPrescanLines.gLines[index].fY0;
		float yb = m_msgPrescanLines.gLines[index].fY1;
		float yc = m_msgPrescanLines.gLines[index].fY2;
		float yd = m_msgPrescanLines.gLines[index].fY3;
		float seq = ftmpLength / 10.0f;
		float p_x, p_y;
		float fline_heading = xb / yb;
		if (abs(fline_heading) > 1)
		{
			switch (linelabel)
			{
			case 0:
				linecolor = COLOR_3UB(255, 0, 0);
				break;
			case 1:
				linecolor = COLOR_3UB(0, 255, 0);
				break;
			case 2:
				linecolor = COLOR_3UB(0, 0, 255);
				break;
			default:
				break;
			}

			glColor4ub(linecolor.cR, linecolor.cG, linecolor.cB, 0xFF);
			glBegin(GL_POINTS);
			for (unsigned int i = 0; i < 1; i++)
			{
				float dis = seq*i;
				p_x = xa + xb*dis + xc*dis*dis + xd*dis*dis*dis;
				p_y = ya + yb*dis + yc*dis*dis + yd*dis*dis*dis;
				glVertex3f(p_x*100.0f, p_y*100.0f, 0.0f);
			}
			glEnd();

			glBegin(GL_LINE_STRIP);
			for (unsigned int i = 0; i < 10; i++)
			{
				float dis = seq*i;
				p_x = xa + xb*dis + xc*dis*dis + xd*dis*dis*dis;
				p_y = ya + yb*dis + yc*dis*dis + yd*dis*dis*dis;
				glVertex3f(p_x*100.0f, p_y*100.0f, 0.0f);
			}
			glEnd();
		}
	}
	glDisable(GL_BLEND);
	m_mtuPrescanLines.unlock();
}

void CDrawPrescanLines::GLDrawPrescanIMG(int &width, int &height)
{
	if (m_bImgReveived)
	{
		m_mtuPrescanIMG.lock();
		memcpy(m_pImgRMsg->imageData, m_msgPrescanIMG.gnImgRData, m_nImageH*m_nImageW);
		memcpy(m_pImgGMsg->imageData, m_msgPrescanIMG.gnImgGData, m_nImageH*m_nImageW);
		memcpy(m_pImgBMsg->imageData, m_msgPrescanIMG.gnImgBData, m_nImageH*m_nImageW);

		/*cvMerge(m_pImgBMsg,m_pImgGMsg,m_pImgRMsg,0,m_pImgRGB);*/
		cvMerge(m_pImgRMsg, m_pImgGMsg, m_pImgBMsg, 0, m_pImgRGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nImageW, m_nImageH, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pImgRGB->imageData);
		m_mtuPrescanIMG.unlock();
		width = m_nImageW;
		height = m_nImageH;
	}
}

void CDrawPrescanLines::DecodePrescanRTK(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtxPrescanRTK.lock();
	m_msgPrescanRTK.decode(recvBuf->data, 0, recvBuf->data_size);
	m_mtxPrescanRTK.unlock();
}

const QStringList CDrawPrescanLines::GetRTKStringList(float& velocity)
{
	m_mtxPrescanRTK.lock();
	QString str;
	QStringList strList;
	str.sprintf("=========PreScanRTK========");
	strList.append(str);
	str.sprintf("Latitude: %.8lf deg", m_msgPrescanRTK.dLatitude);
	strList.append(str);
	str.sprintf("Longitude: %.8lf deg", m_msgPrescanRTK.dLongitude);
	strList.append(str);
	str.sprintf("Altitude: %.3f m", m_msgPrescanRTK.fAltitude);
	strList.append(str);
	str.sprintf("POSX: %.3f m", m_msgPrescanRTK.fPosX);
	strList.append(str);
	str.sprintf("POSY: %.3f m", m_msgPrescanRTK.fPosY);
	strList.append(str);
	str.sprintf("Heading: %.3f deg", m_msgPrescanRTK.fHeading);
	strList.append(str);
	str.sprintf("VelocityNorth: %.3f m/s", m_msgPrescanRTK.fVelNorth);
	strList.append(str);
	str.sprintf("VelocityWest: %.3f m/s", m_msgPrescanRTK.fVelWest);
	strList.append(str);
	str.sprintf("Velocity: %.3f m/s", m_msgPrescanRTK.fVelocity);
	strList.append(str);
	str.sprintf("SystemStatus: 0x%04X", m_msgPrescanRTK.nNavStatus);
	strList.append(str);
	velocity = sqrt((m_msgPrescanRTK.fVelNorth*m_msgPrescanRTK.fVelNorth)+(m_msgPrescanRTK.fVelNorth*m_msgPrescanRTK.fVelNorth))*3.6f;
	m_mtxPrescanRTK.unlock();
	return strList;
}
