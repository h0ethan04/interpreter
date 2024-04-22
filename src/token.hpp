#ifndef TOKEN_HPP
#define TOKEN_HPP


#include <string>
#include <variant>
#include <unordered_map>
#include <utility>
#include <iosfwd>


#include "location.hpp"


enum struct TokenCategory {
    // A categorization of tokens based on similar purposes
    COMPARISON_OPERATOR = 1,
    IDENTIFIER = 2,
    KEYWORD = 3,
    LITERAL_VALUE = 4,
    PUNCTUATION = 5
 };

extern const char* token_cat_text[];

enum struct TokenKindName {
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

extern const char* token_kind_text[];

struct TokenKind {
    // Identifies a kind of token
    TokenKindName kind;
    TokenCategory category;

    bool operator==(const TokenKind & other) const = default;
 };

// token kind map
extern std::unordered_map<std::string, std::pair<TokenKindName, TokenCategory>> TOKEN_MAP;

void populate_token_kind_map();



class Token {
    // Individual tokens in a program
public:
    // constructor for different variants
    Token(const TokenKind & tkind, const std::variant<int, double, std::string> & val, const std::string & txt, const Location & loc);
    
    TokenKind kind() const;
    
    std::variant<int, double, std::string> value() const;

    std::string text() const;

    Location location() const;

    bool operator==(const Token & other) const = default;

    friend std::ostream & operator<<(std::ostream & ostream, const Token & token);

private:

    TokenKind token_kind;
    std::variant<int, double, std::string> token_value;
    std::string token_text;
    Location token_location;

};


#endif