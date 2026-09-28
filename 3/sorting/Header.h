#pragma once
#include <vector>
#include <string>

int searchOne(std::string& S, std::string& P);

std::vector<int> searchAll(std::string& S, std::string& P);

std::vector<int> searchAll_gap(std::string& S, std::string& P, int start, int end);
