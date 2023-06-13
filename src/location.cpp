
#include <iostream>
#include "location.hpp"

std::ostream & operator<<(std::ostream & out, const GrinLocation & loc) {
    out << "Line " << loc.line << " Column " << loc.column;
}

std::istream & operator>>(std::istream & in, GrinLocation & loc) {
    in >> loc.line;
    in >> loc.column;
}