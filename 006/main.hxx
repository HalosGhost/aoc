#if !defined(MAIN_HXX)
#define MAIN_HXX

#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

size_t
end_of_marker (const std::string&, size_t);

std::vector<std::string>
file_lines (const std::string&);

#endif
