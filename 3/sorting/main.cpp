// Алгоритм поиска Бойера-Мура
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Header.h"

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

	searchOne(S, P);
	searchAll(S, P);
	
	// задание границ поиска
	int start, end;
	std::cout << "enter the beginning and end of the search:" << std::endl;
	std::cin >> start >> end;
	
	searchAll_gap(S, P, start, end);

	return 0;
}