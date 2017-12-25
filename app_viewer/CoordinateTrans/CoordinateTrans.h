#pragma once

#include <stdio.h>
#include <list>
#include <math.h>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stdint.h>
#include "global.hpp"

using namespace std;
#define COORDINATETRANS_DLL _declspec(dllexport)

//const double DISPERLATITUDEDEGREE = 111712.69150641055729984301412873;
//const double DISPERLONGITUDEDEGREE = 102834.74258026089786013677476285;
//const double SAMPLERATE = 1.08;
//const double FOCALLENGTH = 0.0060744561;
//const double CAMPIXELS = 0.0000042;
//const double CAMHFOV = 47.74;
//const int IMGWIDTH = 1280;
//const double DEGREE_TO_RADIAN = 0.017453293;// PI/180.0;
//const double RADIAN_TO_DEGREE = 57.295779513;// 180.0/PI;
//const double EARTH_RADIUS = 6378137;
//const double PI = 3.14159265358979323846;

const double DISTORTK_1 = 0.2392224970;
const double DISTORTK_0 = -0.4829767050;
const double DISTORTP_1 = 0.0115442229;
const double DISTORTP_2 = 0.0051512532;
const double FOCAL = 1446.3;
const double CAMCENTERX = 639.5;
const double CAMCENTERY = 539.5;
const float CAMYAW = 1.0f;//-0.2;
const float CAMPITCH = 4.10265625f;// -0.91;
const float CAMROLL = 0.0f;
const float CAMHEIGHT = 1.21f;
const float CAMPOSX = -1.605f;
const float CAMPOSY = -0.115f;
const int IMG_OFFSET_Y = 180;
const int FIRST_MOVE_DIS = 10;

struct PointGps
{
	double f_time_stamp;
	double f_longitude;
	double f_latitude;
	double f_direction;
	double f_speed;
	int n_type;   //0 for nomal, 1 for stopline, 2 for finish

	PointGps()
	{
		f_time_stamp = 0;
		f_longitude = 0;
		f_latitude = 0;
		f_direction = 0;
		f_speed = 0;
		n_type = 0;
	}
};

struct PointXY
{
	double x;
	double y;
	double theta;

	PointXY()
	{
		x = 0;
		y = 0;
		theta = 0;
	}
};

COORDINATETRANS_DLL int Sign(int);
COORDINATETRANS_DLL int Sign(float);
COORDINATETRANS_DLL int Sign(double);

COORDINATETRANS_DLL int Min(int, int);
COORDINATETRANS_DLL float Min(float, float);
COORDINATETRANS_DLL double Min(double, double);

COORDINATETRANS_DLL int Max(int, int);
COORDINATETRANS_DLL float Max(float, float);
COORDINATETRANS_DLL double Max(double, double);


//Coordinate Transform
//latitude longitude to cartesian
//East X positive
//North Y positive
COORDINATETRANS_DLL PointXY GCS2CCS(double, double, double, double);
COORDINATETRANS_DLL PointXY GCS2CCS(PointXY, PointXY);
//cartesian to latitude longitude
COORDINATETRANS_DLL PointXY CCS2GCS(double, double, double, double);

//GPS to vehicle 
//vehicle orientation Y positive
COORDINATETRANS_DLL PointXY GCST2VEH(double, double, double, double, double);
COORDINATETRANS_DLL vector<PointXY> GCST2VEH(vector<PointGps>);
COORDINATETRANS_DLL PointXY Global2Local(PointXY, PointXY);

//Distance
COORDINATETRANS_DLL double DistanceInGps(double, double, double, double);
COORDINATETRANS_DLL double DistanceInGps(PointGps, PointGps);
COORDINATETRANS_DLL double Distance(double, double);
COORDINATETRANS_DLL double Distance(double, double, double, double);
COORDINATETRANS_DLL double Distance(PointXY);
COORDINATETRANS_DLL double Distance(PointXY, PointXY);
//Direction
COORDINATETRANS_DLL double GetAngle(double, double);

COORDINATETRANS_DLL double GetAngleWithX(PointXY);

COORDINATETRANS_DLL double GetAngleWithX(PointXY, PointXY);

//Left-  Right+
COORDINATETRANS_DLL double GetAngleWithY(PointXY);

//Left-  Right+
COORDINATETRANS_DLL double GetAngleWithY(PointXY, PointXY);