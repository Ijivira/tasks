#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


std::vector<int> searchAll_gap(const std::string& S, const std::string& P, int start, int end)
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

	if (end<0 || end > S.size()) {
		end = S.size();
	}
	if (start<0 || start > end) {
		start = 0;
	}
	
	int i = start + P.size() - 1;
	int j = P.size() - 1;
	int k = i;

	while (i <= end && j >= 0) {
		/*
		std::cout << i << " " << j << std::endl;
		std::cout << S.substr(start, i + 1) << std::endl;
		std::cout << std::setw(i + 1 - start) << P << std::endl;*/

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
			//std::cout << i - P.size() + 1 << " - found a match! " << std::endl;
			//std::cout << std::endl;

			j = P.size() - 1;
			i += P.size();
		}
	}

	for (int n : answer) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	return answer;
}