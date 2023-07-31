#include <iostream>

#include "runtime_errors.hpp"

// Arithmetic Error
ArithmeticError::ArithmeticError(const std::string & msg, const GrinLocation & loc)
    : message(msg), error_location(loc){}

GrinLocation ArithmeticError::location() const {
    return error_location;
}

const char* ArithmeticError::what() const noexcept {
    return std::string(message + error_location.formatted()).c_str();
}

// used to throw Arithmetic Errors
void raise_ArithmeticError(const std::string & msg, const GrinLocation & loc) {
    throw ArithmeticError(msg, loc);
}


// Jump Error
JumpError::JumpError(const std::string & msg, const GrinLocation & loc) 
    : message(msg), error_location(loc){}

GrinLocation JumpError::location() const {
    return error_location;
}

const char* JumpError::what() const noexcept {
    return std::string(message + error_location.formatted()).c_str();
}

// used to throw Jump Errors
void raise_JumpError(const std::string & msg, const GrinLocation & loc) {
    throw JumpError(msg, loc);
}


// Return Error
ReturnError::ReturnError(const std::string & msg, const GrinLocation & loc)
    : message(msg), error_location(loc){}

GrinLocation ReturnError::location() const {
    return error_location;
}

const char* ReturnError::what() const noexcept {
    return std::string(message + error_location.formatted()).c_str();
}

// used to throw Return Errors
void raise_ReturnError(const std::string & msg, const GrinLocation & loc) {
    throw ReturnError(msg, loc);
}