
#include <exception>
#include <string>

#include "location.hpp"

class ArithmeticError : public std::exception {
public:
    ArithmeticError(const std::string & msg, const GrinLocation & loc);
    GrinLocation location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    GrinLocation error_location;
};

void raise_ArithmeticError(const std::string & msg, const GrinLocation & loc);


class JumpError : public std::exception {
public:
    JumpError(const std::string & msg, const GrinLocation & loc);
    GrinLocation location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    GrinLocation error_location;
};

void raise_JumpError(const std::string & msg, const GrinLocation & loc);


class ReturnError : public std::exception {
public:
    ReturnError(const std::string & msg, const GrinLocation & loc);
    GrinLocation location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    GrinLocation error_location;
};
void raise_ReturnError(const std::string & msg, const GrinLocation & loc);