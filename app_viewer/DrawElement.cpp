#include "DrawElement.h"


CDrawElement::CDrawElement()
{
}


CDrawElement::~CDrawElement()
{
}

/**@brief draw dashed line between start point and end point;
*
* draw dashed line between start point and end point, the line color and width is specified by the input parameters;
*@param start [IN]: the start point of the line;
*@param end [IN]: the end point of the line;
*@param color [IN]: the color of the line;
*@param lineWidth [IN]: the line width of the line;
*@return void;
*@note
*/
void CDrawElement::DrawDashedLine(const POINT_3F &start, const POINT_3F &end, const COLOR_3UB &color, const float lineWidth)
{
	glColor3ub(color.cR, color.cG, color.cB);
	glLineWidth(lineWidth);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(5, 0x5555);
	glBegin(GL_LINES);
	glVertex3f(start.fX, start.fY, start.fZ);
	glVertex3f(end.fX, end.fY, end.fZ);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

/**@brief draw solid line between start point and end point;
*
* draw solid line between start point and end point, the line color and width is specified by the input parameters;
*@param start [IN]: the start point of the line;
*@param end [IN]: the end point of the line;
*@param color [IN]: the color of the line;
*@param lineWidth [IN]: the line width of the line;
*@return void;
*@note
*/
void CDrawElement::DrawLine(const POINT_3F &start, const POINT_3F &end, const COLOR_3UB& color, const float lineWidth)
{
	glColor3ub(color.cR, color.cG, color.cB);
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	glVertex3f(start.fX, start.fY, start.fZ);
	glVertex3f(end.fX, end.fY, end.fZ);
	glEnd();
}

/**@brief draw solid line between start point and end point;
*
* draw solid line between start point and end point, the line color and width is specified by the input parameters;
*@param start [IN]: the start point of the line;
*@param end [IN]: the end point of the line;
*@param color [IN]: the color of the line;
*@param lineWidth [IN]: the line width of the line;
*@return void;
*@note the color A is also used;
*/
void CDrawElement::DrawLine(const POINT_3F &start, const POINT_3F &end, const COLOR_4UB& color, const float lineWidth)
{
	glEnable(GL_BLEND);
	glColor4ub(color.cR, color.cG, color.cB, color.cA);
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	glVertex3f(start.fX, start.fY, start.fZ);
	glVertex3f(end.fX, end.fY, end.fZ);
	glEnd();
	glDisable(GL_BLEND);
}


/**@brief draw circle in the opengl;
*
* draw specified circle in the opengl, the radius, color and line width could be specified by the input parameters;
*@param radius [IN]: the radius of the circle to be drawn;
*@param color [IN]: the circle color;
*@param lineWidth [IN]: the line width used to draw the circle;
*@return void;
*@note the color A is also enabled;
*/
void CDrawElement::DrawCircle(const float radius, const COLOR_4UB &color, const float lineWidth)
{
	glEnable(GL_BLEND);
	glColor4ub(color.cR, color.cG, color.cB, color.cA);
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 360; i += 10)
	{
		glVertex3f(radius*cos(i*DEGREE_TO_RADIAN), radius*sin(i*DEGREE_TO_RADIAN), 0.0f);
	}
	glEnd();
	glDisable(GL_BLEND);
}

/**@brief draw cubic line in the opengl;
*
* draw cubic line defined by parameters (a,b,c,d), start from x0 to x1;
*@param a [IN]: the param a;
*@param b [IN]: the param b;
*@param c [IN]: the param c;
*@param d [IN]: the param d;
*@param x0 [IN]: the start of the lane line, x0 < x1;
*@param x1 [IN]: the end of the the lane line;
*@return void;
*@note the cubic line is defined as y=a+b*x+c*x*x+d*x*x*x, x in [x0, x1];
*@note the line color and line style should be defined before calling this function;
*/
void CDrawElement::DrawCubicLine(const float a, const float b, const float c, const float d, const float x0, const float x1)
{
	float x = 0.0f, y = 0.0f;
	for (x = x0; x<x1; x += 1.0f)
	{
		y = (a + b*x + c*x*x + d*x*x*x);
		glVertex3f(x*100.0f, -y*100.0f, 0.0f);
	}

	//draw the last point;
	x = x1;
	y = (a + b*x + c*x*x + d*x*x*x);
	glVertex3f(x*100.0f, -y*100.0f, 0.0f);
}
