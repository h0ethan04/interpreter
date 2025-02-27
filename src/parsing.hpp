#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <exception>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "token.hpp"
#include "lexing.hpp"
#include "location.hpp"

class ParsingError : public std::exception {
public:
    ParsingError(const std::string & msg, const Location & loc);
    Location location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    Location error_location;
};

std::vector<std::vector<Token>> parse(const std::vector<std::string> & lines);


#endif