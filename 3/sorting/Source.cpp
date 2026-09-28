// поиск Бауэра и Мура
#include <iostream>
#include <vector>
#include <string>

int main()
{

	std::string S;
	std::string P;

	//std::cout << "Enter the text and the desired fragment " << std::endl;
	//std::getline(std::cin, S);
	//std::getline(std::cin, P);

	S = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
	P = "tor";

	std::cout << "Line length " << S.size() << std::endl;


	int table[256][2];
	
	for (int i = 0; i < 256; i++) {
		table[i][0] = i;
		table[i][1] = 4;
		for (int n : P) {
			if ((int)P[n] == i) 
				table[i][1] = P.size() - 4;
		}
		std::cout << (char)table[i][0] << " " << table[i][1] << std::endl;
	}

	return 0;
}