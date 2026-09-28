// Алгоритм поиска Бойера-Мура
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Header.h"

int table[256];

int main()
{
	std::string S;
	std::string P;
	
	//std::cout << "Enter the text and the desired fragment " << std::endl;
	//std::getline(std::cin, S);
	//std::getline(std::cin, P);

	S = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
	P = "tor";
	std::cout << S << std::endl;
	std::cout << P << std::endl;
	std::cout << "Line length " << S.size() << " fragment length " << P.size() << std::endl;
	std::cout << std::endl;

	// таблица чисел, в которой формируются расстояния символов образца до конца образца.
	for (int i = 0; i < 256; i++) 
	{
		table[i] = P.size();
	}
	for (int i = 0; i < P.size() - 1; i++) 
	{
		table[(int)P[i]] = P.size() - i - 1;
	}

	searchOne(S, P);
	std::cout << std::endl;
	
	searchAll(S, P);
	std::cout << std::endl;
	

	// задание границ поиска
	int start, end;
	std::cout << "enter the beginning and end of the search:" << std::endl;
	std::cin >> start >> end;
	
	if (end<0 || end > S.size()) {
		end = S.size();
	}
	if (start<0 || start > end) {
		start = 0;
	}

	searchAll_gap(S, P, start, end);

	return 0;
}