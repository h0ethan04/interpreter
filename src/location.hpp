#ifndef LOCATION_HPP
#define LOCATION_HPP

struct GrinLocation{
    int line;
    int column;
};
inline std::ostream & operator<<(std::ostream & out, const GrinLocation & loc);

inline std::ostream & operator>>(std::ostream & in, GrinLocation & loc);

#endif