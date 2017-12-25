#include "DrawCoordinates.h"

CDrawCoordinates::CDrawCoordinates()
{

}

CDrawCoordinates::~CDrawCoordinates()
{

}

/************************************************************************/
/*
subscribe the TRANSFORM msg and push back to the transform vector
*/
/************************************************************************/
void CDrawCoordinates::GotaTransformMsg(const TRANSFORM* transform)
{
	m_stTransformListener.PushbackNewTransform(transform);
}

/**@brief switch opengl to specified coordinate system;
*
* switch opengl to specified coordiante system;
*@param timestamp [IN]: the required transform timestamp;
*@param target [IN]: the target coordinate system id;
*@return void;
*@note the length unit in libQGLViewer is cm, the angle unit in libQGLViewer is degree;
*/
void CDrawCoordinates::GLSwitch2Coordinates(const unsigned long long timestamp, const COORINDATE_FRMAE_ID target)
{
	TRANSFORM stTransform;

	//switch to world coordinate;
	if (CFI_WORLD == target)
	{
		if (!m_stTransformListener.GetStampedTransform(timestamp, stTransform))
		{
			return;
		}
		GLTransformVehicle2World(stTransform.gfVehiclePoseInWorld[0] * 100.0f, //x;
			stTransform.gfVehiclePoseInWorld[1] * 100.0f,//y;
			stTransform.gfVehiclePoseInWorld[2] * 100.0f,//z;
			stTransform.gfVehiclePoseInWorld[3] * RADIAN_TO_DEGREE,//yaw angle;
			stTransform.gfVehiclePoseInWorld[4] * RADIAN_TO_DEGREE,//pitch angle;
			stTransform.gfVehiclePoseInWorld[5] * RADIAN_TO_DEGREE); //roll angle;
		return;
	}

	if (!m_stTransformListener.GetNewestTransform(stTransform))
	{
		return;
	}
	switch (target)
	{
	case CFI_VEHICLE://switch to vehicle coordiante system;
		break;
	case CFI_MOBILEYE://switch to mobileye coordinate system;
		GLTransformVehicle2Sensor(stTransform.gfCameraPoseInVehicle);
		break;
	case CFI_FRONT_MWR://switch to front mwr coordiante system;
		GLTransformVehicle2Sensor(stTransform.gfFrontMWRPoseInVehicle);
		break;
	case CFI_LEFT_MWR://switch to left mwr coordinate system;
		GLTransformVehicle2Sensor(stTransform.gfLeftSRRPoseInVehicle);
		break;
	case CFI_RIGHT_MWR://switch to right mwr coordinate system;
		GLTransformVehicle2Sensor(stTransform.gfRightSRRPoseInVehicle);
		break;
	default:
		break;
	}
}


/**@brief transform current gl view from vehicle coordinate to sensor coordinate;
*
* transform current gl view from vehicle coordinate to sensor coordinate;
*@param x [IN]: the translate x, in cm;
*@param y [IN]: the translate y, in cm;
*@param z [IN]: the translate z, in cm;
*@param yaw [IN]: the yaw angle, in degree;
*@param pitch [IN]: the pitch angle, in degree;
*@param roll [IN]: the roll angle, in degree;
*@return void;
*@note the unit is set according to libQGLViewer and the model, first translate, then rotate;
*/
void CDrawCoordinates::GLTransformVehicle2Sensor(const float x, const float y, const float z, const float yaw, const float pitch, const float roll)
{
	glTranslatef(x, y, z);
	//rotate around z axis;
	glRotatef(yaw, 0.0f, 0.0f, 1.0f);
	//rotate around y axis;
	glRotatef(pitch, 0.0f, 1.0f, 0.0f);
	//rotate around x axis;
	glRotatef(roll, 1.0f, 0.0f, 0.0f);
}


/**@brief transform current gl view from vehicle coordinate to sensor coordinate;
*
* transform current gl view from vehicle coordinate to sensor coordinate;
*@param pose [IN]: the pose of the sensor in vehicle coordinates, in x (in m), y (in m), z (in m), yaw (in radian),
pitch (in radian), roll (in radian) order;
*@return void;
*@note the unit is set according to libQGLViewer and the model, first translate, then rotate;
*/
void CDrawCoordinates::GLTransformVehicle2Sensor(const float pose[6])
{
	float x = pose[0] * 100.0f;
	float y = pose[1] * 100.0f;
	float z = pose[2] * 100.0f;

	float yaw = pose[3] * RADIAN_TO_DEGREE;
	float pitch = pose[4] * RADIAN_TO_DEGREE;
	float roll = pose[5] * RADIAN_TO_DEGREE;

	glTranslatef(x, y, z);
	//rotate around z axis;
	glRotatef(yaw, 0.0f, 0.0f, 1.0f);
	//rotate around y axis;
	glRotatef(pitch, 0.0f, 1.0f, 0.0f);
	//rotate around x axis;
	glRotatef(roll, 1.0f, 0.0f, 0.0f);
}


/**@brief transform current gl view from world coordinate to vehicle coordinate;
*
* transform current gl view from world coordinate to vehicle coordiante;
*@param x [IN]: the vehicle x coordiante in world coordinates, in cm;
*@param y [IN]: the vehicle y coordinate in world coordiantes, in cm;
*@param z [IN]: the vehicle z coordinate in world coordiantes, in cm;
*@param yaw [IN]: the vehicle yaw angle in world coordinates, in degree;
*@param pitch [IN]: the vehicle pitch angle in world coordinates, in degree;
*@param roll [IN]: the vehicle roll angle in world coordinates, in degree;
*@return void;
*@note the unit is set according to libQGLViewer and the model, first translate, then rotate;
*/
void CDrawCoordinates::GLTransformWorld2Vehicle(const float x, const float y, const float z, const float yaw, const float pitch, const float roll)
{
	glTranslatef(x, y, z);
	//rotate around z axis;
	glRotatef(yaw, 0.0f, 0.0f, 1.0f);
	//rotate around y axis;
	glRotatef(pitch, 0.0f, 1.0f, 0.0f);
	//rotate around x axis;
	glRotatef(roll, 1.0f, 0.0f, 0.0f);
}

/**@brief transform current gl view from vehicle coordinate to world coordinate;
*
* transform current gl view from vehicle coordinate to world coordinate;
*@param x [IN]: the translate x from world to vehicle, in cm ;
*@param y [IN]: the translate y from world to vehicle, in cm;
*@param z [IN]: the translate z from world to vehicle, in cm;
*@param yaw [IN]: the yaw angle from world to vehicle, in degree;
*@param pitch [IN]: the pitch angle from world to vehicle, in degree;
*@param roll [IN]: the roll angle from world to vehicle, in degree;
*@return void;
*@note the unit is set according to libQGLViewer and the model, first rotate, then translate;
*/
void CDrawCoordinates::GLTransformVehicle2World(const float x, const float y, const float z, const float yaw, const float pitch, const float roll)
{
	//rotate around x axis;
	glRotatef(-roll, 1.0f, 0.0f, 0.0f);
	//rotate around y axis;
	glRotatef(-pitch, 0.0f, 1.0f, 0.0f);
	//rotate around z axis;
	glRotatef(-yaw, 0.0f, 0.0f, 1.0f);
	glTranslatef(-x, -y, -z);
}

/**@brief draw lines between coordinate system;
*
* draw lines between coordiante system;
*@return void;
*@note
*/
void CDrawCoordinates::GLDrawLinesBetweenCoordinates()
{
	POINT_3F start(0.0f, 0.0f, 0.0f);
	POINT_3F end;
	COLOR_3UB color(0xFF, 0xFF, 0x00);
	color.cR = 255;
	color.cG = 255;
	color.cB = 0;

	TRANSFORM stTransform;
	m_stTransformListener.GetNewestTransform(stTransform);

	//draw line from world to vehicle;
	glPushMatrix();
	
	GLSwitch2Coordinates(stTransform.nRTKTimeStamp, CFI_WORLD);

	end.fX = stTransform.gfVehiclePoseInWorld[0] * 100.0f;
	end.fY = stTransform.gfVehiclePoseInWorld[1] * 100.0f;
	end.fZ = stTransform.gfVehiclePoseInWorld[2] * 100.0f;
	m_stElementDrawer.DrawDashedLine(start, end, color, 1.0f);
	glPopMatrix();

	glPushMatrix();

	GLSwitch2Coordinates(stTransform.nRTKTimeStamp, CFI_VEHICLE);


	//draw line from vehicle to mobileye;
	end.fX = stTransform.gfCameraPoseInVehicle[0] * 100.0f;
	end.fY = stTransform.gfCameraPoseInVehicle[1] * 100.0f;
	end.fZ = stTransform.gfCameraPoseInVehicle[2] * 100.0f;
	m_stElementDrawer.DrawLine(start, end, color, 2.0);

	//draw line from vehicle to front mwr;
	end.fX = stTransform.gfFrontMWRPoseInVehicle[0] * 100.0f;
	end.fY = stTransform.gfFrontMWRPoseInVehicle[1] * 100.0f;
	end.fZ = stTransform.gfFrontMWRPoseInVehicle[2] * 100.0f;
	m_stElementDrawer.DrawLine(start, end, color, 2.0);

	//draw line from vehicle to left mwr;
	end.fX = stTransform.gfLeftSRRPoseInVehicle[0] * 100.0f;
	end.fY = stTransform.gfLeftSRRPoseInVehicle[1] * 100.0f;
	end.fZ = stTransform.gfLeftSRRPoseInVehicle[2] * 100.0f;
	m_stElementDrawer.DrawLine(start, end, color, 2.0);

	//draw line from vehicle to right mwr;
	end.fX = stTransform.gfRightSRRPoseInVehicle[0] * 100.0f;
	end.fY = stTransform.gfRightSRRPoseInVehicle[1] * 100.0f;
	end.fZ = stTransform.gfRightSRRPoseInVehicle[2] * 100.0f;
	m_stElementDrawer.DrawLine(start, end, color, 2.0);
	glPopMatrix();
}
