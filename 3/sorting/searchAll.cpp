#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

extern int table[];

std::vector<int> searchAll(std::string& S, std::string& P)
{
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

	return answer;
}