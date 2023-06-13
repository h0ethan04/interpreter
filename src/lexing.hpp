#ifndef LEXING_HPP
#define LEXING_HPP

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <variant>

#include "token.hpp"
#include "location.hpp" 

void raise_error(std::string msg);

std::vector<GrinToken> to_tokens(std::string linen, int line_number);





#endif
