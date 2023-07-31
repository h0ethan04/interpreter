#ifndef COMPARISON_HPP
#define COMPARISON_HPP

#include <map>
#include <string>
#include <variant>
#include <vector>

#include "token.hpp"


bool run_comparison(const std::vector<GrinToken> & line,
                    const std::map<std::string, std::variant<int, double, std::string>> & variables);


#endif