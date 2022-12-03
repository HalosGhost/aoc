#if !defined(MAIN_HXX)
#define MAIN_HXX

#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum class Shape {
    Rock,
    Paper,
    Scissors,
};

uint64_t
score (Shape, Shape);

uint64_t
outcome (Shape, Shape);

Shape
parse_shape (char);

Shape
strategize (Shape, char);

std::vector<std::string>
file_lines (const std::string&);

#endif
