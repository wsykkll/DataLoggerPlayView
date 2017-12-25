#pragma once
#include <QStringList>
#include "global.hpp"
#include <GL/freeglut.h>

//color 3 unsigned bytes struct;
struct POINT_3F
{
	float fX;
	float fY;
	float fZ;
	POINT_3F(float x = 0.0f, float y = 0.0f, float z = 0.0f)
	{
		fX = x;
		fY = y;
		fZ = z;
	}
	const POINT_3F& operator= (const POINT_3F& src)
	{
		fX = src.fX;
		fY = src.fY;
		fZ = src.fZ;
	}

};

//color 3 unsigned bytes struct;
struct COLOR_3F
{
	float fR;
	float fG;
	float fB;
	COLOR_3F(float r = 0.0f, float g = 0.0f, float b = 0.0f)
	{
		fR = r;
		fG = g;
		fB = b;
	}
};

//color 3 unsigned bytes struct;
struct COLOR_3UB
{
	unsigned char cR;
	unsigned char cG;
	unsigned char cB;
	COLOR_3UB(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0)
	{
		cR = r;
		cG = g;
		cB = b;
	}
};

//color 4 unsigned bytes struct;
struct COLOR_4UB
{
	unsigned char cR;
	unsigned char cG;
	unsigned char cB;
	unsigned char cA;
	COLOR_4UB(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 0)
	{
		cR = r;
		cG = g;
		cB = b;
		cA = a;
	}
};
struct TEXT_3D
{
	QString strText;
	POINT_3F stPosition;

};

class CDrawElement
{
public:
	CDrawElement();
	~CDrawElement();

	void DrawDashedLine(const POINT_3F &start, const POINT_3F &end, const COLOR_3UB &color, const float lineWidth);
	void DrawLine(const POINT_3F &start, const POINT_3F &end, const COLOR_3UB& color, const float lineWidth);
	void DrawLine(const POINT_3F &start, const POINT_3F &end, const COLOR_4UB& color, const float lineWidth);
	void DrawCircle(const float radius, const COLOR_4UB& color, const float lineWidth);
	void DrawCubicLine(const float a, const float b, const float c, const float d, const float x0, const float x1);
};

