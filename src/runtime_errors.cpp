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

EndError::EndError() : message("End token detected") {}

const char* EndError::what() const noexcept {
    return message.c_str();
}

// used to throw EndError
void raise_EndError() {
    throw EndError();
}


ComparisonError::ComparisonError(const std::string & msg, const GrinLocation & loc)
    : message(msg), error_location(loc){}

GrinLocation ComparisonError::location() const {
    return error_location;
}

const char* ComparisonError::what() const noexcept {
    return std::string(message + error_location.formatted()).c_str();
}


// used to throw Comparison Errors
void raise_ComparisonError(const std::string & msg, const GrinLocation & loc) {
    throw ComparisonError(msg, loc);
}


InputError::InputError(const std::string & msg, const GrinLocation & loc)
    : message(msg), error_location(loc){}

GrinLocation InputError::location() const {
    return error_location;
}

const char* InputError::what() const noexcept {
    return std::string(message + error_location.formatted()).c_str();
}

void raise_InputError(const std::string & msg, const GrinLocation & loc) {
    throw InputError(msg, loc);
}