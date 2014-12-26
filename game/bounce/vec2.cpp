#include "vec2.h"

vec2& vec2::Rotate(float angle)
{
	angle /= 57.2957f;
	float s = sinf(angle);
	float c = cosf(angle);

	float nx = c * x - s * y;
	float ny = s * x + c * y;

	x = nx;
	y = ny;

	return (*this);
}

vec2& vec2::RotateAroundPoint(float angle, vec2 origin)
{
	float radian = -(angle * (float)M_PI / 180);
	float s = sin(radian);
	float c = cos(radian);

	// translate point back to origin:  
	x -= origin.x;
	y -= origin.y;

	// rotate point   
	float xnew = x * c - y * s;
	float ynew = x * s + y * c;

	// translate point back to global coords:
	x = xnew + origin.x;
	y = ynew + origin.y;

	return (*this);
}

float distance(vec2 p1, vec2 p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	return sqrt((x*x) + (y*y));
}

float dotProduct(vec2 v1, vec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

