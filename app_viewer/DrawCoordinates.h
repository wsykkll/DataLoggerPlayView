#pragma once
#include <GL/freeglut.h>
#include "TransformListener.h"
#include "DrawElement.h"

class CDrawCoordinates
{
public:
	CDrawCoordinates();
	~CDrawCoordinates();

	TransformListener m_stTransformListener;

	void GotaTransformMsg(const TRANSFORM* transform);
	void GLSwitch2Coordinates(const unsigned long long timestamp, const COORINDATE_FRMAE_ID target);
	void GLTransformVehicle2Sensor(const float x, const float y, const float z, const float yaw, const float pitch, const float roll);
	void GLTransformVehicle2Sensor(const float pose[6]);
	void GLTransformWorld2Vehicle(const float x, const float y, const float z, const float yaw, const float pitch, const float roll);
	void GLTransformVehicle2World(const float x, const float y, const float z, const float yaw, const float pitch, const float roll);
	void GLDrawLinesBetweenCoordinates();
private:
	CDrawElement m_stElementDrawer;
};

