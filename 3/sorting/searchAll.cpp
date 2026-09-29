#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

std::vector<int> searchAll(const std::string& S, const std::string& P)
{
	int table[256];
	// таблица чисел, в которой формируются расстояния символов образца до конца образца.
	for (int i = 0; i < 256; i++)
	{
		table[i] = P.size();
	}
	for (int i = 0; i < P.size() - 1; i++)
	{
		table[(int)P[i]] = P.size() - i - 1;
	}

	std::vector<int> answer;

	int i = P.size() - 1;
	int j = P.size() - 1;
	int k = i;

	while (i <= S.size() && j >= 0) {

		if (S[k] == P[j]) {
			k--;
			j--;
		}
		else {
			i += table[(int)S[i]];
			j = P.size() - 1;
			k = i;
		}

		if (j < 0) {
			answer.push_back(i - P.size() + 1);
			j = P.size() - 1;
			i += P.size();
		}
	}

	for (int n : answer) {
		std::cout << n << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	return answer;
}