#include <gtest/gtest.h>

#include <iostream>

#include "lexing.hpp"

void assertEmpty(std::string line) {
    auto l = to_tokens(line, 1);
    ASSERT_EQ(l.size(), 0);
}

void assertOneToken(std::string line, TokenKind kind, std::string text, 
                    std::variant<int, double, std::string> value) {
    auto token = to_tokens(line, 1);
    ASSERT_EQ(token.size(), 1);
    ASSERT_EQ(token.at(0).kind(), kind);
    ASSERT_EQ(token.at(0).text(), text);
    ASSERT_EQ(token.at(0).value(), value);
}

TEST(LexingTests, StartsEmpty) {
    assertEmpty("   ");
}

TEST(LexingTests, DetectsKeywords) {
    assertOneToken("ADD", TokenKind(TokenKindName::ADD, TokenCategory::KEYWORD), "ADD", "ADD");
    assertOneToken("DIV", TokenKind(TokenKindName::DIV, TokenCategory::KEYWORD), "DIV", "DIV");
    assertOneToken("END", TokenKind(TokenKindName::END, TokenCategory::KEYWORD), "END", "END");
    assertOneToken("GOSUB", TokenKind(TokenKindName::GOSUB, TokenCategory::KEYWORD), "GOSUB", "GOSUB");
    assertOneToken("GOTO", TokenKind(TokenKindName::GOTO, TokenCategory::KEYWORD), "GOTO", "GOTO");
    assertOneToken("IF", TokenKind(TokenKindName::IF, TokenCategory::KEYWORD), "IF", "IF");
    assertOneToken("INNUM", TokenKind(TokenKindName::INNUM, TokenCategory::KEYWORD), "INNUM", "INNUM");
    assertOneToken("INSTR", TokenKind(TokenKindName::INSTR, TokenCategory::KEYWORD), "INSTR", "INSTR");
    assertOneToken("LET", TokenKind(TokenKindName::LET, TokenCategory::KEYWORD), "LET", "LET");
    assertOneToken("MULT", TokenKind(TokenKindName::MULT, TokenCategory::KEYWORD), "MULT", "MULT");
    assertOneToken("PRINT", TokenKind(TokenKindName::PRINT, TokenCategory::KEYWORD), "PRINT", "PRINT");
    assertOneToken("RETURN", TokenKind(TokenKindName::RETURN, TokenCategory::KEYWORD), "RETURN", "RETURN");
    assertOneToken("SUB", TokenKind(TokenKindName::SUB, TokenCategory::KEYWORD), "SUB", "SUB");
}

TEST(LexingTests, DetectsNonKeywords) {
    assertOneToken("HELLO", TokenKind(TokenKindName::IDENTIFIER, TokenCategory::IDENTIFIER), "HELLO", "HELLO");
}

TEST(LexingTests, DetectsSpecialChars) {
    assertOneToken(":", TokenKind(TokenKindName::COLON, TokenCategory::PUNCTUATION), ":", ":");
    assertOneToken(".", TokenKind(TokenKindName::DOT, TokenCategory::PUNCTUATION), ".", ".");
    assertOneToken("<", TokenKind(TokenKindName::LESS_THAN, TokenCategory::COMPARISON_OPERATOR), "<", "<");
    assertOneToken("<>", TokenKind(TokenKindName::NOT_EQUAL, TokenCategory::COMPARISON_OPERATOR), "<>", "<>");
    assertOneToken("<=", TokenKind(TokenKindName::LESS_THAN_OR_EQUAL, TokenCategory::COMPARISON_OPERATOR), "<=", "<=");
    assertOneToken(">", TokenKind(TokenKindName::GREATER_THAN, TokenCategory::COMPARISON_OPERATOR), ">", ">");
    assertOneToken(">=", TokenKind(TokenKindName::GREATER_THAN_OR_EQUAL, TokenCategory::COMPARISON_OPERATOR), ">=", ">=");
    assertOneToken("=", TokenKind(TokenKindName::EQUAL, TokenCategory::COMPARISON_OPERATOR), "=", "=");
}

TEST(LexingTests, DetectsLiterals) {
    assertOneToken("\"BOO\"", TokenKind(TokenKindName::LITERAL_STRING, TokenCategory::LITERAL_VALUE), "\"BOO\"", "BOO");
    assertOneToken("\"\"", TokenKind(TokenKindName::LITERAL_STRING, TokenCategory::LITERAL_VALUE), "\"\"", "");
    assertOneToken("1", TokenKind(TokenKindName::LITERAL_INTEGER, TokenCategory::LITERAL_VALUE), "1", 1);
    assertOneToken("0", TokenKind(TokenKindName::LITERAL_INTEGER, TokenCategory::LITERAL_VALUE), "0", 0);    
    assertOneToken("-1", TokenKind(TokenKindName::LITERAL_INTEGER, TokenCategory::LITERAL_VALUE), "-1", -1);
    assertOneToken("0.5", TokenKind(TokenKindName::LITERAL_DOUBLE, TokenCategory::LITERAL_VALUE), "0.5", 0.5);
    assertOneToken("-0.1", TokenKind(TokenKindName::LITERAL_DOUBLE, TokenCategory::LITERAL_VALUE), "-0.1", -0.1);
}

TEST(LexingTests, LexesMultipleTokens) {
    auto tokens = to_tokens("LET BOO 3", 1);
    std::variant<int, double, std::string> let_val("LET");
    std::variant<int, double, std::string> boo_val("BOO");
    std::variant<int, double, std::string> three_val(3);
    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(tokens.at(0).text(), "LET");
    ASSERT_EQ(tokens.at(0).value(), let_val);
    ASSERT_EQ(tokens.at(1).text(), "BOO");
    ASSERT_EQ(tokens.at(1).value(), boo_val);
    ASSERT_EQ(tokens.at(2).text(), "3");
    ASSERT_EQ(tokens.at(2).value(), three_val);
    ASSERT_EQ(std::get<int>(tokens.at(2).value()), 3);

    ASSERT_EQ(tokens.at(0).kind(), TokenKind(TokenKindName::LET, TokenCategory::KEYWORD));
    ASSERT_EQ(tokens.at(1).kind(), TokenKind(TokenKindName::IDENTIFIER, TokenCategory::IDENTIFIER));
    ASSERT_EQ(tokens.at(2).kind(), TokenKind(TokenKindName::LITERAL_INTEGER, TokenCategory::LITERAL_VALUE));
}
