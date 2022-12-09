#if !defined(MAIN_HXX)
#define MAIN_HXX

#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Dir {
    std::vector<std::string> path_segments {};
    std::size_t sz {};
};

bool
is_prefix_of (const std::vector<std::string>&, const std::vector<std::string>&);

std::size_t
get_size (const std::vector<Dir>&, const std::vector<std::string>&);

std::vector<Dir>
get_dirs (const std::vector<std::string>&);

std::vector<std::string>
file_lines (const std::string&);

#endif
