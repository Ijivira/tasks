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