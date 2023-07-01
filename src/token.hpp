#ifndef TOKEN_HPP
#define TOKEN_HPP


#include <string>
#include <variant>
#include <unordered_map>
#include <utility>


#include "location.hpp"


enum struct GrinTokenCategory {
    // A categorization of Grin tokens based on similar purposes
    COMPARISON_OPERATOR = 1,
    IDENTIFIER = 2,
    KEYWORD = 3,
    LITERAL_VALUE = 4,
    PUNCTUATION = 5
 };

enum struct GrinTokenKindName {
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
    LITERAL_DOUBLE = 18,
    LITERAL_INTEGER = 19,
    LITERAL_STRING = 20,
    MULT = 21,
    NOT_EQUAL = 22,
    PRINT = 23,
    RETURN = 24,
    SUB = 25
 };

struct GrinTokenKind {
    // Identifies a kind of Grin token
    GrinTokenKindName kind;
    GrinTokenCategory category;

    bool operator==(const GrinTokenKind & other) const = default;
 };

// token kind map
extern std::unordered_map<std::string, std::pair<GrinTokenKindName, GrinTokenCategory>> TOKEN_MAP;

void populate_token_kind_map();



class GrinToken {
    // Individual tokens in a Grin program
public:
    // constructor for different variants
    GrinToken(const GrinTokenKind & tkind, const std::variant<int, double, std::string> & val, const std::string & txt, const GrinLocation & loc);
    
    GrinTokenKind kind() const;
    
    std::variant<int, double, std::string> value() const;

    std::string text() const;

    GrinLocation location() const;

    bool operator==(const GrinToken & other) const = default;

private:

    GrinTokenKind token_kind;
    std::variant<int, double, std::string> token_value;
    std::string token_text;
    GrinLocation token_location;

};


#endif