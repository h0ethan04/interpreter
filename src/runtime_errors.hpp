
#include <exception>
#include <string>

#include "location.hpp"

class ArithmeticError : public std::exception {
public:
    ArithmeticError(const std::string & msg, const Location & loc);
    Location location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    Location error_location;
};

void raise_ArithmeticError(const std::string & msg, const Location & loc);


class JumpError : public std::exception {
public:
    JumpError(const std::string & msg, const Location & loc);
    Location location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    Location error_location;
};

void raise_JumpError(const std::string & msg, const Location & loc);


class ReturnError : public std::exception {
public:
    ReturnError(const std::string & msg, const Location & loc);
    Location location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    Location error_location;
};
void raise_ReturnError(const std::string msg, const Location & loc);


class EndError : public std::exception {
public:
    EndError();
    virtual const char* what() const noexcept override;
private:
    std::string message;
};

void raise_EndError();


class ComparisonError : public std::exception {
public:
    ComparisonError(const std::string & msg, const Location & loc);
    Location location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    Location error_location;
};

void raise_ComparisonError(const std::string & msg, const Location & loc);


class InputError : public std::exception {
public:
    InputError(const std::string & msg, const Location & loc);
    Location location() const;
    virtual const char* what() const noexcept override;

private:
    std::string message;
    Location error_location;
};

void raise_InputError(const std::string & msg, const Location & loc);