#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

#include "token.hpp"

std::vector<std::string> read_input(std::istream & in);

std::map<std::string, int> map_labels(const std::vector<std::vector<Token>> & tokens);

#endif