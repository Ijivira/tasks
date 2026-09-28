#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

extern int table[];

std::vector<int> searchAll_gap(std::string& S, std::string& P, int start, int end)
{
	std::vector<int> answer;
	
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

	return answer;
}