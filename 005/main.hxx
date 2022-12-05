#if !defined(MAIN_HXX)
#define MAIN_HXX

#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

std::vector<std::stack<char>> stacks{};

void
fifo_execute (const std::vector<std::string>&);

void
lifo_execute (const std::vector<std::string>&);

void
setup_stacks (const std::vector<std::string>&);

std::vector<std::string>
file_lines (const std::string&);

#endif
