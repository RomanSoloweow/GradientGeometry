#pragma once

#include <ostream>
using namespace std;
class Point
{
public:
	int X, Y;
	Point(int x, int y);
	Point();
	friend ostream& operator<<(ostream& os, Point& Point);
};

