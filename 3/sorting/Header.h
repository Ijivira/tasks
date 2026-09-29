#pragma once
#include <vector>
#include <string>

int searchOne(const std::string& S, const std::string& P);

std::vector<int> searchAll(const std::string& S, const std::string& P);

std::vector<int> searchAll_gap(const std::string& S, const std::string& P, int start, int end);
