#pragma once

#include "Point.h"
using namespace std;

Point::Point(int x, int y) :X(x), Y(y) {};
Point::Point() :X(0), Y(0) {};


/// <summary>
/// Output for Point
/// </summary>
/// <param name="os">ostream</param>
/// <param name="Point">Point</param>
/// <returns>ostream</returns>
ostream& operator<<(ostream& os, Point& point)
{
	os << "X: " << point.X << ", Y: " << point.Y;
	return os;
}

/// <summary>
/// Swap Point
/// </summary>
/// <param name="A">Point A</param>
/// <param name="B">Point B</param>
void Swap(Point& a, Point& b)
{
	int temp = a.X;
	a.X = b.X;
	b.X = temp;
	temp = a.Y;
	a.Y = b.Y;
	b.Y = temp;
}

