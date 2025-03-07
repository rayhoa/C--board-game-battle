#include"point.h"
Point2d::Point2d()
{
	x = 0;
	y = 0;
}
Point2d::Point2d(int a, int b)
{
	x = a;
	y = b;
}
void Point2d::setPoint(int a, int b)
{
	x = a;
	y = b;
}