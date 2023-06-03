#ifndef TOKEN_HPP
#define TOKEN_HPP


#include <string>
#include <variant>
#include <utility>


#include "location.hpp"

class GrinToken {
    // Individual tokens in a Grin program
public:
    // constructor for different variants
    GrinToken(GrinTokenKind tkind, std::variant<int, double, std::string> val, std::string txt, GrinLocation loc);
    
    GrinTokenKind kind();
    
    auto value();

    std::string text();

    GrinLocation location();

    bool operator==(const GrinToken & other);

private:

    GrinTokenKind kind;
    std::variant<int, double, std::string> value;
    std::string text;
    GrinLocation location;

};


 struct GrinTokenKind {
    // Identifies a kind of Grin token'
    GrinTokenCategory::category category;
    GrinTokenKindName::kind kind;
 };

struct GrinTokenCategory {
    // A categorization of Grin tokens based on similar purposes
    enum category {
        COMPARISON_IDENTIFIER = 1,
        IDENTIFIER = 2,
        KEYWORD = 3,
        LITERAL_VALUE = 4,
        PUNCTUATION = 5
    };
 };

struct GrinTokenKindName {
    enum kind {
        ADD = 1,
        COLON = 2,
        DIV = 3,
        DOT = 4,
        END = 5,
        EQUAL = 6,
        GOSUB = 7,
        GOTO = 8,
        GREATER_THAN = 9,
        GREATER_THAN_OR_EQUAL = 10,
        IDENTIFIER = 11,
        IF = 12,
        INNUM = 13,
        INSTR = 14,
        LESS_THAN = 15,
        LESS_THAN_OR_EQUAL = 16,
        LET = 17,
        LITERAL_FLOAT = 18,
        LITERAL_INTEGER = 19,
        LITERAL_STRING = 20,
        MULT = 20,
        NOT_EQUAL = 21,
        PRINT = 22,
        RETURN = 23,
        SUB = 24
    };
 };

#endif