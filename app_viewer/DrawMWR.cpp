#include "DrawMWR.h"


CDrawMWR::CDrawMWR()
{
}


CDrawMWR::~CDrawMWR()
{
}

//void CDrawMWR::DecodeRawFrontMWRObjectsMsg(const METRadarObject_Lcm* msg)
void CDrawMWR::DecodeRawFrontMWRObjectsMsg(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtuRawFrontMWRObjects.lock();
	m_msgRawFrontMWRObjects.decode(recvBuf->data, 0, recvBuf->data_size);
	//memcpy(&m_msgRawFrontMWRObjects, msg, sizeof(METRadarObject_Lcm));
	m_mtuRawFrontMWRObjects.unlock();
}

void CDrawMWR::DecodeVehicleSpeedMsg(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtxVehInfo.lock();
	m_msgVehicleSpeedInfo.decode(recvBuf->data, 0, recvBuf->data_size);
	m_fVehSpeed = float(m_msgVehicleSpeedInfo.messageval);
	m_mtxVehInfo.unlock();
}

void CDrawMWR::DecodeRawSRRLeftObjectsMsg(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtuSRRLeftObjects.lock();
	m_msgSRRLeftObjects.decode(recvBuf->data, 0, recvBuf->data_size);
	m_mtuSRRLeftObjects.unlock();
}

void CDrawMWR::DecodeRawSRRRightObjectsMsg(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtuSRRRightObjects.lock();
	m_msgSRRRightObjects.decode(recvBuf->data, 0, recvBuf->data_size);
	m_mtuSRRRightObjects.unlock();
}

const std::vector<TEXT_3D> CDrawMWR::GLDrawRawFrontMWRObjects(CDrawCoordinates& coordinates)
{
	std::vector<TEXT_3D> vecText3D;
	float dist = 0.0f, angle = 0.0f, x = 0.0f, y = 0.0f;
	m_mtuRawFrontMWRObjects.lock();
	coordinates.GLSwitch2Coordinates(m_msgRawFrontMWRObjects.header.nTimeStamp, CFI_FRONT_MWR);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	
	for (int i = 0; i < 64; i++)
	{
		if (m_msgRawFrontMWRObjects.objList[i].trackStatus != 0)
		{
			if (m_msgRawFrontMWRObjects.objList[i].trackOnComing != 0)
			{
				glColor4ub(0xEE, 0x00, 0x00, 0xFF);
			}
			else
			{
				glColor4ub(0x00, 0xEE, 0x00, 0xFF);
			}
			dist = m_msgRawFrontMWRObjects.objList[i].trackRange;
			angle = m_msgRawFrontMWRObjects.objList[i].trackAngle * DEGREE_TO_RADIAN;

			x = dist*cos(angle) *100.0f;
			y = -dist*sin(angle) *100.0f;
			glVertex3f(x, y, 0.0f);
			char* status_[8] = { "NO", "NEW", "NEW_UPDATED", "UPDATED", "COASTED", "MERGED", "INVALID_COASTED", "NEW_COASTED" };
			TEXT_3D text3D;
			text3D.stPosition.fX = x;
			text3D.stPosition.fY = y;
			text3D.stPosition.fZ = 0.0;
			//text3D.strText.sprintf("id:%d, w:%.2f, speed:%.2f, vely:%.2f, m:%d, st:%d, Power:%d",
			text3D.strText.sprintf("id:%d, width:%.2f, speed:%.2f, Acc:%.2f, st:%s",
				i,
				m_msgRawFrontMWRObjects.objList[i].trackWidth,
				m_msgRawFrontMWRObjects.objList[i].trackRangeRate * 3.6f,
				m_msgRawFrontMWRObjects.objList[i].trackRangeAccel * 3.6f,
				status_[m_msgRawFrontMWRObjects.objList[i].trackStatus]);
			vecText3D.push_back(text3D);
		}
	}
	glEnd();
	glPointSize(1.0f);

	m_mtuRawFrontMWRObjects.unlock();

	return vecText3D;
}

const std::vector<TEXT_3D> CDrawMWR::GLDrawRawESRNewObjects(CDrawCoordinates& coordinates)
{
	std::vector<TEXT_3D> vecText3D;
	float dist = 0.0f, angle = 0.0f, x = 0.0f, y = 0.0f;
	m_mtuRawFrontMWRObjects.lock();
	coordinates.GLSwitch2Coordinates(m_msgRawFrontMWRObjects.header.nTimeStamp, CFI_FRONT_MWR);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(0xEE, 0xEE, 0x00, 0xFF);
	for (int i = 0; i < 64; i++)
	{
		if (m_msgRawFrontMWRObjects.objList[i].trackStatus == 1)
		{
			dist = m_msgRawFrontMWRObjects.objList[i].trackRange;
			angle = m_msgRawFrontMWRObjects.objList[i].trackAngle * DEGREE_TO_RADIAN;

			x = dist*cos(angle) *100.0f;
			y = -dist*sin(angle) *100.0f;
			glVertex3f(x, y, 0.0f);
			char* status_[8] = { "NO", "NEW", "NEW_UPDATED", "UPDATED", "COASTED", "MERGED", "INVALID_COASTED", "NEW_COASTED" };
			TEXT_3D text3D;
			text3D.stPosition.fX = x;
			text3D.stPosition.fY = y;
			text3D.stPosition.fZ = 0.0;
			text3D.strText.sprintf("id:%d, width:%.2f, speed:%.2f, Acc:%.2f, st:%s",
				i,
				m_msgRawFrontMWRObjects.objList[i].trackWidth,
				m_msgRawFrontMWRObjects.objList[i].trackRangeRate * 3.6f,
				m_msgRawFrontMWRObjects.objList[i].trackRangeAccel * 3.6f,
				status_[m_msgRawFrontMWRObjects.objList[i].trackStatus]);
			vecText3D.push_back(text3D);
		}
	}
	glEnd();
	glPointSize(1.0f);
	m_mtuRawFrontMWRObjects.unlock();
	return vecText3D;
}

const std::vector<TEXT_3D> CDrawMWR::GLDrawRawESRNewUpdatedObjects(CDrawCoordinates& coordinates)
{
	std::vector<TEXT_3D> vecText3D;
	float dist = 0.0f, angle = 0.0f, x = 0.0f, y = 0.0f;
	m_mtuRawFrontMWRObjects.lock();
	coordinates.GLSwitch2Coordinates(m_msgRawFrontMWRObjects.header.nTimeStamp, CFI_FRONT_MWR);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(0x00, 0xEE, 0x00, 0xFF);
	for (int i = 0; i < 64; i++)
	{
		if (m_msgRawFrontMWRObjects.objList[i].trackStatus == 2)
		{
			dist = m_msgRawFrontMWRObjects.objList[i].trackRange;
			angle = m_msgRawFrontMWRObjects.objList[i].trackAngle * DEGREE_TO_RADIAN;

			x = dist*cos(angle) *100.0f;
			y = -dist*sin(angle) *100.0f;
			glVertex3f(x, y, 0.0f);
			char* status_[8] = { "NO", "NEW", "NEW_UPDATED", "UPDATED", "COASTED", "MERGED", "INVALID_COASTED", "NEW_COASTED" };
			TEXT_3D text3D;
			text3D.stPosition.fX = x;
			text3D.stPosition.fY = y;
			text3D.stPosition.fZ = 0.0;
			text3D.strText.sprintf("id:%d, width:%.2f, speed:%.2f, Acc:%.2f, st:%s",
				i,
				m_msgRawFrontMWRObjects.objList[i].trackWidth,
				m_msgRawFrontMWRObjects.objList[i].trackRangeRate * 3.6f,
				m_msgRawFrontMWRObjects.objList[i].trackRangeAccel * 3.6f,
				status_[m_msgRawFrontMWRObjects.objList[i].trackStatus]);
			vecText3D.push_back(text3D);
		}
	}
	glEnd();
	glPointSize(1.0f);
	m_mtuRawFrontMWRObjects.unlock();
	return vecText3D;
}

const std::vector<TEXT_3D> CDrawMWR::GLDrawRawESRUpdatedObjects(CDrawCoordinates& coordinates)
{
	std::vector<TEXT_3D> vecText3D;
	float dist = 0.0f, angle = 0.0f, x = 0.0f, y = 0.0f;
	m_mtuRawFrontMWRObjects.lock();
	coordinates.GLSwitch2Coordinates(m_msgRawFrontMWRObjects.header.nTimeStamp, CFI_FRONT_MWR);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	//glColor4ub(0xEE, 0x00, 0x00, 0xFF);
	for (int i = 0; i < 64; i++)
	{
		if (m_msgRawFrontMWRObjects.objList[i].trackStatus == 3)
		{
			float fDeltaSpeed = fabs(m_fVehSpeed + m_msgRawFrontMWRObjects.objList[i].trackRangeRate*3.6f);
			if (fDeltaSpeed > 3.0f)
			{
				glColor4ub(0xEE, 0x00, 0x00, 0xFF);
			}
			else
			{
				glColor4ub(0x00, 0xFF, 0xFF, 0xFF);
				//break;
			}
			dist = m_msgRawFrontMWRObjects.objList[i].trackRange;
			angle = m_msgRawFrontMWRObjects.objList[i].trackAngle * DEGREE_TO_RADIAN;

			x = dist*cos(angle) *100.0f;
			y = -dist*sin(angle) *100.0f;
			glVertex3f(x, y, 0.0f);
			char* status_[8] = { "NO", "NEW", "NEW_UPDATED", "UPDATED", "COASTED", "MERGED", "INVALID_COASTED", "NEW_COASTED" };
			TEXT_3D text3D;
			text3D.stPosition.fX = x;
			text3D.stPosition.fY = y;
			text3D.stPosition.fZ = 0.0;
			text3D.strText.sprintf("id:%d, width:%.2f, speed:%.2f, Acc:%.2f, st:%s",
				i,
				m_msgRawFrontMWRObjects.objList[i].trackWidth,
				m_msgRawFrontMWRObjects.objList[i].trackRangeRate * 3.6f,
				m_msgRawFrontMWRObjects.objList[i].trackRangeAccel * 3.6f,
				status_[m_msgRawFrontMWRObjects.objList[i].trackStatus]);
			vecText3D.push_back(text3D);
		}
	}
	glEnd();
	glPointSize(1.0f);
	m_mtuRawFrontMWRObjects.unlock();
	return vecText3D;
}

const std::vector<TEXT_3D> CDrawMWR::GLDrawRawESRCoastedObjects(CDrawCoordinates& coordinates)
{
	std::vector<TEXT_3D> vecText3D;
	float dist = 0.0f, angle = 0.0f, x = 0.0f, y = 0.0f;
	m_mtuRawFrontMWRObjects.lock();
	coordinates.GLSwitch2Coordinates(m_msgRawFrontMWRObjects.header.nTimeStamp, CFI_FRONT_MWR);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(0xEE, 0x00, 0xEE, 0xFF);
	for (int i = 0; i < 64; i++)
	{
		if (m_msgRawFrontMWRObjects.objList[i].trackStatus == 4)
		{
			dist = m_msgRawFrontMWRObjects.objList[i].trackRange;
			angle = m_msgRawFrontMWRObjects.objList[i].trackAngle * DEGREE_TO_RADIAN;

			x = dist*cos(angle) *100.0f;
			y = -dist*sin(angle) *100.0f;
			glVertex3f(x, y, 0.0f);
			char* status_[8] = { "NO", "NEW", "NEW_UPDATED", "UPDATED", "COASTED", "MERGED", "INVALID_COASTED", "NEW_COASTED" };
			TEXT_3D text3D;
			text3D.stPosition.fX = x;
			text3D.stPosition.fY = y;
			text3D.stPosition.fZ = 0.0;
			text3D.strText.sprintf("id:%d, width:%.2f, speed:%.2f, Acc:%.2f, st:%s",
				i,
				m_msgRawFrontMWRObjects.objList[i].trackWidth,
				m_msgRawFrontMWRObjects.objList[i].trackRangeRate * 3.6f,
				m_msgRawFrontMWRObjects.objList[i].trackRangeAccel * 3.6f,
				status_[m_msgRawFrontMWRObjects.objList[i].trackStatus]);
			vecText3D.push_back(text3D);
		}
	}
	glEnd();
	glPointSize(1.0f);
	m_mtuRawFrontMWRObjects.unlock();
	return vecText3D;
}

const std::vector<TEXT_3D> CDrawMWR::GLDrawESRACCObjects(CDrawCoordinates& coordinates)
{
	std::vector<TEXT_3D> vecText3D;
	float dist = 0.0f, angle = 0.0f, x = 0.0f, y = 0.0f;
	m_mtuRawFrontMWRObjects.lock();
	coordinates.GLSwitch2Coordinates(m_msgRawFrontMWRObjects.header.nTimeStamp, CFI_FRONT_MWR);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(0xB3, 0xEE, 0x3A, 0xFF);
	for (int i = 0; i < 64; i++)
	{
		if (m_msgRawFrontMWRObjects.ACC_Traget_ID == (i + 1) && m_msgRawFrontMWRObjects.objList[i].trackStatus != 0)
		{
			dist = m_msgRawFrontMWRObjects.objList[i].trackRange;
			angle = m_msgRawFrontMWRObjects.objList[i].trackAngle * DEGREE_TO_RADIAN;

			x = dist*cos(angle) *100.0f;
			y = -dist*sin(angle) *100.0f;
			glVertex3f(x, y, 0.0f);
			char* status_[8] = { "NO", "NEW", "NEW_UPDATED", "UPDATED", "COASTED", "MERGED", "INVALID_COASTED", "NEW_COASTED" };
			TEXT_3D text3D;
			text3D.stPosition.fX = x;
			text3D.stPosition.fY = y;
			text3D.stPosition.fZ = 0.0;
			//text3D.strText.sprintf("id:%d, w:%.2f, speed:%.2f, vely:%.2f, m:%d, st:%d, Power:%d",
			text3D.strText.sprintf("id:%d, width:%.2f, speed:%.2f, Acc:%.2f, st:%s",
				i,
				m_msgRawFrontMWRObjects.objList[i].trackWidth,
				m_msgRawFrontMWRObjects.objList[i].trackRangeRate * 3.6f,
				m_msgRawFrontMWRObjects.objList[i].trackRangeAccel * 3.6f,
				status_[m_msgRawFrontMWRObjects.objList[i].trackStatus]);
			vecText3D.push_back(text3D);
			break;
		}
	}
	glEnd();
	glPointSize(1.0f);
	m_mtuRawFrontMWRObjects.unlock();
	return vecText3D;
}

const std::vector<TEXT_3D> CDrawMWR::GLDrawESRFCWObjects(CDrawCoordinates& coordinates)
{
	std::vector<TEXT_3D> vecText3D;
	float dist = 0.0f, angle = 0.0f, x = 0.0f, y = 0.0f;
	m_mtuRawFrontMWRObjects.lock();
	coordinates.GLSwitch2Coordinates(m_msgRawFrontMWRObjects.header.nTimeStamp, CFI_FRONT_MWR);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(0xBF, 0xBF, 0xBF, 0xFF);
	for (int i = 0; i < 64; i++)
	{
		if (m_msgRawFrontMWRObjects.FCW_Move_ID == (i + 1) && m_msgRawFrontMWRObjects.objList[i].trackStatus != 0)
		{
			dist = m_msgRawFrontMWRObjects.objList[i].trackRange;
			angle = m_msgRawFrontMWRObjects.objList[i].trackAngle * DEGREE_TO_RADIAN;

			x = dist*cos(angle) *100.0f;
			y = -dist*sin(angle) *100.0f;
			glVertex3f(x, y, 0.0f);
			char* status_[8] = { "NO", "NEW", "NEW_UPDATED", "UPDATED", "COASTED", "MERGED", "INVALID_COASTED", "NEW_COASTED" };
			TEXT_3D text3D;
			text3D.stPosition.fX = x;
			text3D.stPosition.fY = y;
			text3D.stPosition.fZ = 0.0;
			text3D.strText.sprintf("id:%d, width:%.2f, speed:%.2f, Acc:%.2f, st:%s",
				i,
				m_msgRawFrontMWRObjects.objList[i].trackWidth,
				m_msgRawFrontMWRObjects.objList[i].trackRangeRate * 3.6f,
				m_msgRawFrontMWRObjects.objList[i].trackRangeAccel * 3.6f,
				status_[m_msgRawFrontMWRObjects.objList[i].trackStatus]);
			vecText3D.push_back(text3D);
			break;
		}
	}
	glEnd();
	glPointSize(1.0f);
	m_mtuRawFrontMWRObjects.unlock();
	return vecText3D;
}

const std::vector<TEXT_3D> CDrawMWR::GLDrawRawSRRLeftObjects(CDrawCoordinates& coordinates)
{
	std::vector<TEXT_3D> vecText3D;
	float dist = 0.0f, angle = 0.0f, x = 0.0f, y = 0.0f;
	m_mtuSRRLeftObjects.lock();
	coordinates.GLSwitch2Coordinates(m_msgSRRLeftObjects.header.nTimeStamp, CFI_LEFT_MWR);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(0xEE, 0xEE, 0x00, 0xFF);
	for (int i = 0; i < 64; i++)
	{
		dist = m_msgSRRLeftObjects.objList[i].fDetectRange;
		angle = m_msgSRRLeftObjects.objList[i].fDetectAngle * DEGREE_TO_RADIAN;

		y = dist*cos(angle) *100.0f;
		x = -dist*sin(angle) *100.0f;
		glVertex3f(x, y, 0.0f);

		TEXT_3D text3D;
		text3D.stPosition.fX = x;
		text3D.stPosition.fY = y;
		text3D.stPosition.fZ = 0.0;
		//text3D.strText.sprintf("id:%d, w:%.2f, speed:%.2f, vely:%.2f, m:%d, st:%d, Power:%d",
		text3D.strText.sprintf("id:%d,  speed:%.2f,  st:%d",
			i,
			m_msgSRRLeftObjects.objList[i].fDetectRangeRate * 3.6f,
			m_msgSRRLeftObjects.objList[i].ucDetectStatus);
		vecText3D.push_back(text3D);
	}
	glEnd();
	glPointSize(1.0f);

	m_mtuSRRLeftObjects.unlock();

	return vecText3D;
}

const std::vector<TEXT_3D> CDrawMWR::GLDrawRawSRRRightObjects(CDrawCoordinates& coordinates)
{
	std::vector<TEXT_3D> vecText3D;
	float dist = 0.0f, angle = 0.0f, x = 0.0f, y = 0.0f;
	m_mtuSRRRightObjects.lock();
	coordinates.GLSwitch2Coordinates(m_msgSRRRightObjects.header.nTimeStamp, CFI_RIGHT_MWR);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor4ub(0x7F, 0xFF, 0xD4, 0xFF);
	for (int i = 0; i < 64; i++)
	{
		dist = (m_msgSRRRightObjects.objList[i].fDetectRange);
		angle = m_msgSRRRightObjects.objList[i].fDetectAngle * DEGREE_TO_RADIAN;

		y = dist*cos(angle) *100.0f;
		x = dist*sin(angle) *100.0f;
		glVertex3f(x, y, 0.0f);

		TEXT_3D text3D;
		text3D.stPosition.fX = x;
		text3D.stPosition.fY = y;
		text3D.stPosition.fZ = 0.0;
		//text3D.strText.sprintf("id:%d, w:%.2f, speed:%.2f, vely:%.2f, m:%d, st:%d, Power:%d",
		text3D.strText.sprintf("id:%d,  speed:%.2f,  st:%d",
			i,
			m_msgSRRRightObjects.objList[i].fDetectRangeRate * 3.6f,
			m_msgSRRRightObjects.objList[i].ucDetectStatus);
		vecText3D.push_back(text3D);
	}
	glEnd();
	glPointSize(1.0f);

	m_mtuSRRRightObjects.unlock();

	return vecText3D;
}