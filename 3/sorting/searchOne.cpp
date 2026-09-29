#include <iostream>
#include <string>
#include <vector>

int searchOne(const std::string& S, const std::string& P)
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
	}
	std::cout << i - P.size() + 1 << std::endl;
	std::cout << std::endl;

	return i - P.size() + 1;
}