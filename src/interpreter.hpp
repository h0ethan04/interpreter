#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <vector>

#include "comparison.hpp"
#include "preprocessing.hpp"
#include "token.hpp"

// use std::holds_alternative<X> to check if the data type is X
//     ^^^^^^^^^^^^^^^^^^^^^^^^^ returns a bool
// use std::get<X> to get type X from the std::variant
typedef std::map<std::string, std::variant<int, double, std::string>> var_map;
var_map interpret_tokens(const std::vector<std::string> & lines);


#endif
