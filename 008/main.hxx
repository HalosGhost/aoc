#if !defined(MAIN_HXX)
#define MAIN_HXX

#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::size_t
scenic_score (const std::vector<std::vector<uint8_t>>&, std::size_t, std::size_t);

std::size_t
count_visible (const std::vector<std::vector<uint8_t>>&);

bool
is_visible (const std::vector<std::vector<uint8_t>>&, std::size_t, std::size_t);

std::vector<std::vector<uint8_t>>
get_grid (const std::vector<std::string>&);

std::vector<std::string>
file_lines (const std::string&);

#endif
