// Задача коммивояжёра эврестический метод, 3 пример из лекции

#include <stdio.h>
#include <random>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <iomanip>


//**** реализация Алгоритма Дейкстры ***//
bool permutation(int* cities, int n)
{

	//Находим максимальное значение i такое, что 0 < i < n и P[i] < P[i+1].
	int i = n - 2;
	while (i > 0 && cities[i + 1] <= cities[i]) {
		i--;
	}

	//Если такого i не существует, то процесс завершен
	if (i == 0) return 0;

	//Находим максимальное значение j такое, что i < j <= n и P[i] < P[j].
	int j = n;
	while (j > i && cities[j] < cities[i]) {
		j--;
	}

	//Меняем P[i] и P[j] местами
	std::swap(cities[j], cities[i]);

	// Инвертируем порядок с i + 1 по n.
	std::reverse(&cities[i + 1], &cities[n]);

	return 1;
}


//**** вывод перестановки на экран ***//
void print(int* cities, int n)
{
	for (int i = 0; i < n; i++) {
		std::cout << cities[i] + 1 << " ";
	}
	//std::cout << std::endl;
}



int main()
{
	std::chrono::high_resolution_clock::time_point timeBegin;
	std::chrono::high_resolution_clock::time_point timeEnd;
	std::chrono::microseconds interval;

	// Инициализация генератора случайных чисел
	std::random_device rd; // Источник энтропии
	std::mt19937 gen(rd()); // Mersenne Twister, seed из random_device

	int rangeStart = 1, rangeEnd = 10;
	//std::cout << "cost range:" << std::endl;
	//std::cin >> rangeStart >> rangeEnd;

	std::uniform_int_distribution<int> distrib(rangeStart, rangeEnd);

	int N, City_1 = 1;
	for (N = 2; N <= 10; N++) {
		std::cout << "N = "<< N << std::endl;
		//std::cout << "number of cities:" << std::endl;
		//std::cin >> N;

		//std::cout << "first city:" << std::endl;
		//std::cin >> City_1;

		// Заполнение матрицы стоимости
		int** matrix = new int* [N];
		for (int i = 0; i < N; ++i) {
			matrix[i] = new int[N];
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matrix[i][j] = distrib(gen);
				if (i == j) matrix[i][j] = 0;
			}
		}

		/*// Вывод матрицы стоимости
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				std::cout << std::setw(3) << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		
		*/


		//**** Алгоритм Дейкстры ***//
		timeBegin = std::chrono::high_resolution_clock::now();

		int Min_trip_cost = 0;
		int Max_trip_cost = 0;
		int* answer = new int[N];
		int* answer_max = new int[N];
		int* cities = new int[N];

		// начальная перестановка
		cities[0] = City_1 - 1;

		for (int i = 1, k = 0; i < N; i++, k++) {
			if (k == City_1 - 1) k++;
			cities[i] = k;
		}

		// Сохраняем начальную перестановку в качестве ответа
		for (int i = 0; i < N; i++) {
			answer[i] = cities[i];
			answer_max[i] = cities[i];
		}

		// Сумма пути
		for (int i = 0; i < N - 1; i++) {
			Min_trip_cost += matrix[cities[i]][cities[i + 1]];
			Max_trip_cost += matrix[cities[i]][cities[i + 1]];
		}
		Min_trip_cost += matrix[cities[N - 1]][cities[0]];

		Max_trip_cost += matrix[cities[N - 1]][cities[0]];

		// Выполняем перестановки и расчет пути
		do {
			int trip_cost = 0;
			// Сумма пути
			for (int i = 0; i < N - 1; i++) {
				trip_cost += matrix[cities[i]][cities[i + 1]];
			}
			trip_cost += matrix[cities[N - 1]][cities[0]];

			if (trip_cost < Min_trip_cost) {
				std::copy(cities, &cities[N], answer);
				Min_trip_cost = trip_cost;
			}
			if (trip_cost > Max_trip_cost) {
				std::copy(cities, &cities[N], answer_max);
				Max_trip_cost = trip_cost;
			}

		} while (permutation(cities, N));

		timeEnd = std::chrono::high_resolution_clock::now();
		interval = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin);


		// Вывод ответа
		std::cout << "minimum path:";
		print(answer, N);
		std::cout << "(" << Min_trip_cost << ")" << std::endl;

		std::cout << "maximum path:";
		print(answer_max, N);
		std::cout << "("<<Max_trip_cost<< ")" << std::endl;

		std::cout << "calculation time:" << interval.count() << std::endl;

		std::cout << std::endl;




		//**** эвристический алгоритм ***//

		timeBegin = std::chrono::high_resolution_clock::now();

		// расчетная матрица

		int** temporary = new int* [N];
		for (int i = 0; i < N; ++i) {
			temporary[i] = new int[N];
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				temporary[i][j] = matrix[i][j];
			}
		}

		int* answer2 = new int[N + 1];

		answer2[0] = 0;

		for (int i = 0; i < N; i++) {
			temporary[i][0] = 0;
		}

		for (int k = 0; k < N - 1; k++) {

			int row = answer2[k];
			int min_el = rangeEnd + 1;
			int column = N + 1;

			// минимальное значение в строке
			for (int j = 0; j < N; j++) {
				if (temporary[row][j] != 0 && temporary[row][j] < min_el) {
					min_el = matrix[row][j];
					column = j;
				}
			}

			// сохраняем ответ
			answer2[k + 1] = column;

			// убираем строку и столбец
			for (int j = 0; j < N; j++) temporary[row][j] = 0;
			for (int i = 0; i < N; i++) temporary[i][column] = 0;
		}

		int trip_cost = 0;

		// Сумма пути
		for (int i = 0; i < N - 1; i++) {
			trip_cost += matrix[answer2[i]][answer2[i + 1]];
		}
		trip_cost += matrix[answer2[N - 1]][answer2[0]];

		timeEnd = std::chrono::high_resolution_clock::now();
		interval = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin);

		// Вывод ответа
		std::cout << "greedy way:";
		print(answer2, N);
		std::cout << "(" << trip_cost << ")" << std::endl;

		std::cout << "calculation time:" << interval.count() << std::endl;
		if (Max_trip_cost != Min_trip_cost) {
			std::cout << "Accuracy "<<100 - (trip_cost - Min_trip_cost) * 100 / (Max_trip_cost - Min_trip_cost) << " %" << std::endl;
		}
		else std::cout << "Accuracy " << 100 << "%" << std::endl;
		std::cout << "************************" << std::endl;
		std::cout << std::endl;


		delete[] cities;
		delete[] answer;
		delete[] answer2;

		for (int i = 0; i < N; ++i) {
			delete[] temporary[i];
		}
		delete[] temporary;
		temporary = nullptr;

		for (int i = 0; i < N; ++i) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;

	}
	return 0;
}