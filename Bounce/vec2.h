#pragma once

#define _USE_MATH_DEFINES
#define _SCL_SECURE_NO_WARNINGS
#include <numeric>
#include <iterator>
#include <math.h>


class vec2
{
public:

	float   x;
	float   y;

	vec2() 
	{
		x = 0.f;
		y = 0.f;
	}

	vec2(float r, float s)
	{
		x = r;
		y = s;
	}

	vec2(float* r)
	{
		x = r[0];
		y = r[1];
	}

	vec2(int* r)
	{
		x = (float)r[0];
		y = (float)r[1];
	}

	vec2& Set(float r, float s)
	{
		x = r;
		y = s;
		return (*this);
	}

	float& operator [](long k)
	{
		return ((&x)[k]);
	}

	const float& operator [](long k) const
	{
		return ((&x)[k]);
	}

	vec2& operator +=(const vec2& v)
	{
		x += v.x;
		y += v.y;
		return (*this);
	}

	vec2& operator -=(const vec2& v)
	{
		x -= v.x;
		y -= v.y;
		return (*this);
	}

	vec2& operator *=(float t)
	{
		x *= t;
		y *= t;
		return (*this);
	}

	vec2& operator /=(float t)
	{
		float f = 1.0F / t;
		x *= f;
		y *= f;
		return (*this);
	}

	vec2& operator &=(const vec2& v)
	{
		x *= v.x;
		y *= v.y;
		return (*this);
	}

	vec2 operator -(void) const
	{
		return (vec2(-x, -y));
	}

	vec2 operator +(const vec2& v) const
	{
		return (vec2(x + v.x, y + v.y));
	}

	vec2 operator -(const vec2& v) const
	{
		return (vec2(x - v.x, y - v.y));
	}

	vec2 operator *(float t) const
	{
		return (vec2(x * t, y * t));
	}

	vec2 operator /(float t) const
	{
		float f = 1.0F / t;
		return (vec2(x * f, y * f));
	}

	float operator *(const vec2& v) const
	{
		return (x * v.x + y * v.y);
	}

	vec2 operator &(const vec2& v) const
	{
		return (vec2(x * v.x, y * v.y));
	}

	bool operator ==(const vec2& v) const
	{
		return ((x == v.x) && (y == v.y));
	}

	bool operator !=(const vec2& v) const
	{
		return ((x != v.x) || (y != v.y));
	}

	float Length(void)
	{
		return sqrt((x*x) + (y*y));
	}

	vec2& Normalize(void)
	{
		return (*this /= sqrtf(x * x + y * y));
	}

	vec2& Rotate(float angle);

	vec2& RotateAroundPoint(float angle, vec2 point);
};

float distance(vec2 p1, vec2 p2);

float dotProduct(vec2 v1, vec2 v2);



