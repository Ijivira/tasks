#include <iostream>
#include <string>
#include <vector>

extern int table[];

int searchOne(std::string& S, std::string& P)
{
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

	return i - P.size() + 1;
}