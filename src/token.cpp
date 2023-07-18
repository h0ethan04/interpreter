#include <iostream>
#include "token.hpp"

std::ostream & operator<<(std::ostream & ostream, const GrinToken & token){
        ostream << token.text() << std::endl;   
        return ostream;
    }

GrinToken::GrinToken(const GrinTokenKind & tkind,
                    const std::variant<int, double, std::string> & val, 
                    const std::string & txt, 
                    const GrinLocation & loc) 
    : token_kind(tkind), token_value(val), token_text(txt), token_location(loc) {}

GrinTokenKind GrinToken::kind() const {
    return token_kind;
}

std::variant<int, double, std::string> GrinToken::value() const {
    return token_value;
}

std::string GrinToken::text() const {
    return token_text;
}

GrinLocation GrinToken::location() const {
    return token_location;
}

std::unordered_map<std::string, std::pair<GrinTokenKindName, GrinTokenCategory>> TOKEN_MAP;

void populate_token_kind_map() {
    TOKEN_MAP.insert(std::pair("ADD",std::pair(GrinTokenKindName::ADD, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("DIV", std::pair(GrinTokenKindName::DIV, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("END", std::pair(GrinTokenKindName::END, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("GOSUB", std::pair(GrinTokenKindName::GOSUB, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("GOTO", std::pair(GrinTokenKindName::GOTO, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("IF", std::pair(GrinTokenKindName::IF, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("INNUM", std::pair(GrinTokenKindName::INNUM, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("INSTR", std::pair(GrinTokenKindName::INSTR, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("LET", std::pair(GrinTokenKindName::LET, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("MULT", std::pair(GrinTokenKindName::MULT, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("PRINT", std::pair(GrinTokenKindName::PRINT, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("RETURN", std::pair(GrinTokenKindName::RETURN, GrinTokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("SUB", std::pair(GrinTokenKindName::SUB, GrinTokenCategory::KEYWORD)));
}


const char* token_cat_text[] = { "COMPARISON_OPERATOR", "IDENTIFIER", "KEYWORD", "LITERAL_VALUE", "PUNCTUATION"};

const char* token_kind_text[] = {"ADD", "COLON", "DIV", "DOT", "END", "EQUAL", "GOSUB", "GOTO", "GREATER_THAN",
                           "GREATER_THAN_OR_EQUAL", "IDENTIFIER", "IF", "INNUM", "INSTR", "LESS_THAN",
                           "LESS_THAN_OR_EQUAL", "LET", "LITERAL_DOUBLE", "LITERAL_INTEGER", "LITERAL_STRING",
                           "MULT", "NOT_EQUAL", "PRINT", "RETURN", "SUB"};
