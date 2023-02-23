#include "Vector2d.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Vector2d::Vector2d()
{
	x = y = 0;
}

Vector2d::Vector2d(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2d Vector2d::operator+(Vector2d other)
{
	return Vector2d(x + other.x, y + other.y);
}

Vector2d Vector2d::operator-(Vector2d other)
{
	return Vector2d(x - other.x, y - other.y);
}

Vector2d Vector2d::operator+=(Vector2d other)
{
	return Vector2d(x += other.x, y += other.y);
}

Vector2d Vector2d::operator-=(Vector2d other)
{
	return Vector2d(x -= other.x, y -= other.y);
}

Vector2d Vector2d::operator=(Vector2d other)
{
	return Vector2d(x=other.x, y= other.y);
}

bool Vector2d::operator==(Vector2d other)
{
	return x == other.x && y == other.y;
}

Vector2d Vector2d::operator*(float a)
{
	return Vector2d(a * x, a * y);
}

Vector2d Vector2d::operator*=(float a)
{
	return Vector2d( x*=a, y*=a);
}

float Vector2d::Dot(Vector2d other)
{
	return x * other.x + y * other.y;
}

float Vector2d::getMagnitude()
{
	return sqrt(x * x + y * y);
}

Vector2d Vector2d::getNormalized()
{
	float mag = getMagnitude();
	return Vector2d(x/mag, y/mag);
}

void Vector2d::normalize()
{
	float mag = getMagnitude();
	x /= mag; y /= mag;
}

Vector2d::operator Vector2f()
{
	return Vector2f(x, y);
}

Vector2d Vector2d::getNormal()
{
	return Vector2d(-y,x);
}

void Vector2d::print()
{
	cout << "<" << x << " , " << y << ">" << endl;
}

Vector2d operator*(float a, Vector2d vector)
{
	return vector * a;
}
Vector2d operator*=(float a, Vector2d vector)
{
	return vector *= a;
}
