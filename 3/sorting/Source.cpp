// Алгоритм поиска Бойера-Мура
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

int main()
{

	std::string S;
	std::string P;
	std::vector<int> answer;

	//std::cout << "Enter the text and the desired fragment " << std::endl;
	//std::getline(std::cin, S);
	//std::getline(std::cin, P);

	S = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
	P = "tor";
	std::cout << S << std::endl;
	std::cout << P << std::endl;
	std::cout << "Line length " << S.size() << " fragment length " << P.size() << std::endl;

	// таблица чисел, в которой формируются расстояния символов образца до конца образца.
	int table[256][2];

	for (int i = 0; i < 256; i++) {
		table[i][0] = i;
		table[i][1] = P.size();
	}

	for (int i = 0; i < P.size() - 1; i++) {
		table[(int)P[i]][1] = P.size() - i - 1;
	}

	/*for (int i = 0; i < 256; i++) {
		std::cout << (char)table[i][0] << " " << table[i][1] << std::endl;
	}*/
	int start = 0, end = S.size();
	std::cout << "enter the beginning and end of the search:" << std::endl;
	std::cin >> start >> end;
	if (end > S.size()) end = S.size();
	if (start > end) start = end;


	std::cout << std::endl;
	std::cout << S.substr(start, end) << std::endl;
	std::cout << P << std::endl;


	int i = start + P.size() - 1;
	int j = P.size() - 1;
	int k = i;
		while (i <= end && j >= 0) {
		
				std::cout << i << " " << j << std::endl;
				std::cout << S.substr(start, i + 1) << std::endl;
				std::cout << std::setw(i + 1 - start) << P << std::endl;

				//std::cout << (int)S[k] << " " << (int)P[j] << std::endl;

				if (S[k] == P[j]) {
					k--;
					j--;
				}
				else {
					i += table[(int)S[i]][1];
					j = P.size() - 1;
					k = i;
				}

		if (j < 0) {
			answer.push_back(i - P.size() + 1);
			std::cout << i - P.size() +1 << " - found a match! " << std::endl;
			std::cout << std::endl;

			j = P.size() - 1;
			i += P.size();
		}
		}

		for (int n : answer) {
			std::cout << n << " ";
		}
		std::cout << std::endl;

	return 0;
}