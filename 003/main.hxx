#if !defined(MAIN_HXX)
#define MAIN_HXX

#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cctype>
#include <algorithm>

char
badge (const std::vector<std::string>&);

char
compartment_duplicate (const std::string&);

uint64_t
priority (char);

std::vector<std::string>
file_lines (const std::string&);

#endif
