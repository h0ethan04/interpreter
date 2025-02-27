
#include <iostream>

#include "location.hpp"

std::string Location::formatted() const {
    return std::string(std::string("Line ") + std::to_string(line) + std::string(" Column ") + std::to_string(column));
}

std::ostream & operator<<(std::ostream & out, const Location & loc) {
    out << "Line " << loc.line << " Column " << loc.column;
    return out;
}

std::istream & operator>>(std::istream & in, Location & loc) {
    in >> loc.line;
    in >> loc.column;
    return in;
}