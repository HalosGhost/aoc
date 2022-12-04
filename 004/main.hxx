#if !defined(MAIN_HXX)
#define MAIN_HXX

#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

struct Interval {
    uint64_t lower;
    uint64_t upper;
};

bool
ival_overlaps (const Interval&, const Interval&);

bool
ival_contains (const Interval&, const Interval&);

std::vector<std::string>
file_lines (const std::string&);

#endif
