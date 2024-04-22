#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iosfwd>

struct Location{
    int line;
    int column;

    std::string formatted() const;

    bool operator==(const Location & other) const = default;

    friend std::ostream & operator<<(std::ostream & out, const Location & loc);

    friend std::istream & operator>>(std::istream & in, Location & loc);

};

#endif