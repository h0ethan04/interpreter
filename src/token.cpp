#include <iostream>
#include "token.hpp"

std::ostream & operator<<(std::ostream & ostream, const Token & token){
        ostream << token.text() << std::endl;   
        return ostream;
    }

Token::Token(const TokenKind & tkind,
                    const std::variant<int, double, std::string> & val, 
                    const std::string & txt, 
                    const Location & loc) 
    : token_kind(tkind), token_value(val), token_text(txt), token_location(loc) {}

TokenKind Token::kind() const {
    return token_kind;
}

std::variant<int, double, std::string> Token::value() const {
    return token_value;
}

std::string Token::text() const {
    return token_text;
}

Location Token::location() const {
    return token_location;
}

std::unordered_map<std::string, std::pair<TokenKindName, TokenCategory>> TOKEN_MAP;

void populate_token_kind_map() {
    TOKEN_MAP.insert(std::pair("ADD",std::pair(TokenKindName::ADD, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("DIV", std::pair(TokenKindName::DIV, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("END", std::pair(TokenKindName::END, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("GOSUB", std::pair(TokenKindName::GOSUB, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("GOTO", std::pair(TokenKindName::GOTO, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("IF", std::pair(TokenKindName::IF, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("INNUM", std::pair(TokenKindName::INNUM, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("INSTR", std::pair(TokenKindName::INSTR, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("LET", std::pair(TokenKindName::LET, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("MULT", std::pair(TokenKindName::MULT, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("PRINT", std::pair(TokenKindName::PRINT, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("RETURN", std::pair(TokenKindName::RETURN, TokenCategory::KEYWORD)));
    TOKEN_MAP.insert(std::pair("SUB", std::pair(TokenKindName::SUB, TokenCategory::KEYWORD)));
}


const char* token_cat_text[] = { "COMPARISON_OPERATOR", "IDENTIFIER", "KEYWORD", "LITERAL_VALUE", "PUNCTUATION"};

const char* token_kind_text[] = {"ADD", "COLON", "DIV", "DOT", "END", "EQUAL", "GOSUB", "GOTO", "GREATER_THAN",
                           "GREATER_THAN_OR_EQUAL", "IDENTIFIER", "IF", "INNUM", "INSTR", "LESS_THAN",
                           "LESS_THAN_OR_EQUAL", "LET", "LITERAL_DOUBLE", "LITERAL_INTEGER", "LITERAL_STRING",
                           "MULT", "NOT_EQUAL", "PRINT", "RETURN", "SUB"};
