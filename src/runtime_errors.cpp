#include <iostream>

#include "runtime_errors.hpp"

// Arithmetic Error
ArithmeticError::ArithmeticError(const std::string & msg, const Location & loc)
    : message(msg + ": " + loc.formatted()), error_location(loc){}

Location ArithmeticError::location() const {
    return error_location;
}

const char* ArithmeticError::what() const noexcept {
    return message.c_str();
}

// used to throw Arithmetic Errors
void raise_ArithmeticError(const std::string & msg, const Location & loc) {
    throw ArithmeticError(msg, loc);
}


// Jump Error
JumpError::JumpError(const std::string & msg, const Location & loc) 
    : message(msg + ": " + loc.formatted()), error_location(loc){}

Location JumpError::location() const {
    return error_location;
}

const char* JumpError::what() const noexcept {
    return message.c_str();
}

// used to throw Jump Errors
void raise_JumpError(const std::string & msg, const Location & loc) {
    throw JumpError(msg, loc);
}


// Return Error
ReturnError::ReturnError(const std::string & msg, const Location & loc)
    : message(msg + ": " + loc.formatted()), error_location(loc){}

Location ReturnError::location() const {
    return error_location;
}

const char* ReturnError::what() const noexcept {
    return message.c_str();
}

// used to throw Return Errors
void raise_ReturnError(const std::string msg, const Location & loc) {
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


ComparisonError::ComparisonError(const std::string & msg, const Location & loc)
    : message(msg + ": " + loc.formatted()), error_location(loc){}

Location ComparisonError::location() const {
    return error_location;
}

const char* ComparisonError::what() const noexcept {
    return message.c_str();
}


// used to throw Comparison Errors
void raise_ComparisonError(const std::string & msg, const Location & loc) {
    throw ComparisonError(msg, loc);
}


InputError::InputError(const std::string & msg, const Location & loc)
    : message(msg + ": " + loc.formatted()), error_location(loc){}

Location InputError::location() const {
    return error_location;
}

const char* InputError::what() const noexcept {
    return message.c_str();
}

void raise_InputError(const std::string & msg, const Location & loc) {
    throw InputError(msg, loc);
}