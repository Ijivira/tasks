#include <iostream>
#include <cmath>
#include <numbers>

#include "Point.h"

Point::Point()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;

	std::cout << "Point has been created:" << std::endl;
	std::cout << "x = " << x << " y = " << y << " z = " << z << std::endl;
}


Point::Point(const double p_x, const double p_y, const double p_z)
{
	x = p_x;
	y = p_y;
	z = p_z;

	std::cout << "Point has been created:" << std::endl;
	std::cout << "x = " << x << " y = " << y << " z = " << z << std::endl;
}

double Point::get_x() const { return x; }
void Point::set_x(const double p_x) { x = p_x; }

double Point::get_y() const { return x; }
void Point::set_y(const double p_x) { x = p_x; }

double Point::get_z() const { return x; }
void Point::set_z(const double p_x) { x = p_x; }

void Point::input()
{
	std::cout << "Coordinates of the point:" << std::endl;
	std::cout << "x = " << x << " y = " << y << " z = " << z << std::endl;
}

void Point::set_point(const double p_x, const double p_y, const double p_z)
{
	x = p_x;
	y = p_y;
	z = p_z;

	std::cout << "new values:" << std::endl;
	std::cout << "x = " << x << " y = " << y << " z = " << z << std::endl;
}

void Point::plane()const
{
	if (x == 0) {
		std::cout << "point lies in the yz plane" << std::endl;
	}
	else if (y == 0) {
		std::cout << "point lies in the xz plane" << std::endl;
	}
	else if (z == 0)
	{
		std::cout << "point lies in the xy plane" << std::endl;
	}
	else
	{
		std::cout << "the point does not lie on the coordinate plane" << std::endl;
	}
}

bool Point::octant(const Point& other) const
{
	return (x * other.x >= 0 && y * other.y >= 0 && z * other.z >= 0);
}

bool Point::symmetry(const Point& other) const
{
	return (x == -other.x && y == -other.y && z == -other.z);
}

void Point::symmetryAxis(const Point& other) const
{
	if (x == other.x && y == -other.y && z == -other.z) {
		std::cout << "points are symmetrical about the axis Ox" << std::endl;
	} else if (y == other.y && x == -other.x && z == -other.z) {
		std::cout << "points are symmetrical about the axis Oy" << std::endl;
	} else if (z == other.z && y == -other.y && x == -other.x) {
		std::cout << "points are symmetrical about the axis Oz" << std::endl;
	} else
		std::cout << "points are not symmetrical about the axis" << std::endl;
}


double Point::operator -(const Point& other) const
{ 
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2)) ;
}

double Point::abs() const
{
	return sqrt(x* x + y*y + z*z);
}

bool Point::operator >(const Point& other) const
{
	return abs()>other.abs();
}

Point Point::operator *(const double A) const
{
	Point temp;
	temp.x = A*x;
	temp.y = A*y;
	temp.z = A*z;
	return temp;
}

double Point::distanceX() const
{
	return sqrt(y * y + z * z);
}
double Point::distanceY() const
{
	return sqrt(x * x + z * z);
}
double Point::distanceZ() const
{
	return sqrt(x * x + y * y);
}

bool Point::triangle(const Point& second, const Point& third) const
{
	double a, b, c;
	a = third - *this;
	b = third - second;
	c = third - *this;

	if ((a + b > c) && (a + c > b) && (b + c > a)) {return 1;}
	else { return 0; }
}

double Point::square(const Point& second, const Point& third) const
{
	return 0.5 * sqrt(pow((second.y - y)*(third.z - z) - (second.z - z)*(third.y - y), 2) +
		pow((second.z - z)*(third.x - x) - (second.x - x)*(third.z - z), 2) +
		pow((second.x - x)*(third.y - y) - (second.y - y)*(third.x - x), 2));
}