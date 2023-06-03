#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iosfwd>

struct GrinLocation{
    int line;
    int column;

    friend std::ostream & operator<<(std::ostream & out, const GrinLocation & loc);

    friend std::istream & operator>>(std::istream & in, GrinLocation & loc);

};

#endif