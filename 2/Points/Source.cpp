#include <iostream>
#include <cmath>

#include "Point.h"

int main()
{
	// создадим две точки
	Point P1(3, 4, 0);
	Point P2;

	// ввод/вывод одной из координат точки;
	std::cout << "change the x coordinate at the second point:" << std::endl;
	double x_change = 10;
	//std::cin >> x_change;
	P2.set_x(x_change);
	std::cout << "P2 x = " << P2.get_x() << std::endl;

	// ввод/вывод точки;
	P2.input();
	std::cout << "change the second point." << std::endl;
	P2.set_point(0, 5, 6);
	std::cout << std::endl;

	//лежит ли точка на координатной плоскости xOy, xOz, yOz
	P2.plane();

	//лежат ли две точки в одном октанте
	(P1.octant(P2)) ? std::cout << "P1 and P2 in one octant" << std::endl : 
		std::cout << "are not in an octant" << std::endl;

	//симметричны ли две точки относительно начала координат;
	Point P3(0, 1, 0);
	(P1.symmetry(P3))? std::cout << "P1 and P3 symmetric" << std::endl : 
		std::cout << "P1 and P3 not symmetric" << std::endl;

	//симметричны ли две точки относительно оси Ox, Oy или Oz
	P1.symmetryAxis(P3);
	std::cout << std::endl;
	
	//нахождение расстояния между двумя точками
	std::cout << "distance between points P1 and P3: " << P1 - P3 << std::endl;

	//сравнение двух точек
	(P1 > P3) ? (std::cout << "P1 > P3: " << std::endl) :
		(std::cout << "P1 < P3: " << std::endl);

	//умножение точки на число
	Point P4 = P1*1;
	P4.input();

	//нахождение расстояния от точки до координатных осей
	std::cout << "distance from the point P4 to the axis X: " << P4.distanceX() << std::endl;
	std::cout << "distance from the point P4 to the axis Y: " << P4.distanceY() << std::endl;
	std::cout << "distance from the point P4 to the axis Z: " << P4.distanceZ() << std::endl;
	std::cout << std::endl;

	//проверка, образуют ли три точки треугольник;
	P1.input();
	P2.input();
	P4.input();

	P1.triangle(P2, P4) ? (std::cout << "three points form a triangle" << std::endl) :
		(std::cout << "It's not a triangle" << std::endl);
	std::cout << std::endl;

	// нахождение площади треугольника, образованного тремя точками.
	P1.input();
	P2.input();
	P3.input();

	std::cout << "S = " << P1.square(P2, P3) << std::endl;

}