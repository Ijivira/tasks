#include <iostream>
#include <cmath>

#include "Point.h"

int main()
{
	// создадим две точки
	Point P1(1, 2, 3);
	Point P2;

	// ввод/вывод одной из координат точки;
	std::cout << "change the x coordinate at the second point:" << std::endl;
	double x_change;
	std::cin >> x_change;
	P2.set_x(x_change);
	std::cout << "P2 x = " << P2.get_x() << std::endl;

	// ввод/вывод точки;
	P2.input();
	std::cout << "change the second point." << std::endl;
	P2.set_point(0, 5, 6);

	P2.plane();
	std::cout << "two points in one octant?" << std::endl;
	(P1.octant(P2)) ? std::cout << "yes" << std::endl : std::cout << "no" << std::endl;

}