#ifndef LEXING_HPP
#define LEXING_HPP

#include <iosfwd>
#include <exception>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>
#include <variant>
#include <utility>

#include "token.hpp"
#include "location.hpp" 

class LexingError : public std::exception {
public:
    LexingError(const std::string & msg, const Location & loc);
    Location location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    Location error_location;
};



void raise_error(const std::string & msg, const Location & loc);

std::vector<Token> to_tokens(const std::string & line, int line_number);


#endif
