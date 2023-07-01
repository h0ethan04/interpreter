#include <gtest/gtest.h>

#include <iostream>

#include "lexing.hpp"

void assertEmpty(std::string line) {
    auto l = to_tokens(line, 1);
    ASSERT_EQ(l.size(), 0);
}

void assertOneToken(std::string line, GrinTokenKind kind, std::string text, 
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
    assertOneToken("ADD", GrinTokenKind(GrinTokenKindName::ADD, GrinTokenCategory::KEYWORD), "ADD", "ADD");
    assertOneToken("DIV", GrinTokenKind(GrinTokenKindName::DIV, GrinTokenCategory::KEYWORD), "DIV", "DIV");
    assertOneToken("END", GrinTokenKind(GrinTokenKindName::END, GrinTokenCategory::KEYWORD), "END", "END");
    assertOneToken("GOSUB", GrinTokenKind(GrinTokenKindName::GOSUB, GrinTokenCategory::KEYWORD), "GOSUB", "GOSUB");
    assertOneToken("GOTO", GrinTokenKind(GrinTokenKindName::GOTO, GrinTokenCategory::KEYWORD), "GOTO", "GOTO");
    assertOneToken("IF", GrinTokenKind(GrinTokenKindName::IF, GrinTokenCategory::KEYWORD), "IF", "IF");
    assertOneToken("INNUM", GrinTokenKind(GrinTokenKindName::INNUM, GrinTokenCategory::KEYWORD), "INNUM", "INNUM");
    assertOneToken("INSTR", GrinTokenKind(GrinTokenKindName::INSTR, GrinTokenCategory::KEYWORD), "INSTR", "INSTR");
    assertOneToken("LET", GrinTokenKind(GrinTokenKindName::LET, GrinTokenCategory::KEYWORD), "LET", "LET");
    assertOneToken("MULT", GrinTokenKind(GrinTokenKindName::MULT, GrinTokenCategory::KEYWORD), "MULT", "MULT");
    assertOneToken("PRINT", GrinTokenKind(GrinTokenKindName::PRINT, GrinTokenCategory::KEYWORD), "PRINT", "PRINT");
    assertOneToken("RETURN", GrinTokenKind(GrinTokenKindName::RETURN, GrinTokenCategory::KEYWORD), "RETURN", "RETURN");
    assertOneToken("SUB", GrinTokenKind(GrinTokenKindName::SUB, GrinTokenCategory::KEYWORD), "SUB", "SUB");
}

TEST(LexingTests, DetectsNonKeywords) {
    assertOneToken("HELLO", GrinTokenKind(GrinTokenKindName::IDENTIFIER, GrinTokenCategory::IDENTIFIER), "HELLO", "HELLO");
}

TEST(LexingTests, DetectsSpecialChars) {
    assertOneToken(":", GrinTokenKind(GrinTokenKindName::COLON, GrinTokenCategory::PUNCTUATION), ":", ":");
    assertOneToken(".", GrinTokenKind(GrinTokenKindName::DOT, GrinTokenCategory::PUNCTUATION), ".", ".");
    assertOneToken("<", GrinTokenKind(GrinTokenKindName::LESS_THAN, GrinTokenCategory::COMPARISON_OPERATOR), "<", "<");
    assertOneToken("<>", GrinTokenKind(GrinTokenKindName::NOT_EQUAL, GrinTokenCategory::COMPARISON_OPERATOR), "<>", "<>");
    assertOneToken("<=", GrinTokenKind(GrinTokenKindName::LESS_THAN_OR_EQUAL, GrinTokenCategory::COMPARISON_OPERATOR), "<=", "<=");
    assertOneToken(">", GrinTokenKind(GrinTokenKindName::GREATER_THAN, GrinTokenCategory::COMPARISON_OPERATOR), ">", ">");
    assertOneToken(">=", GrinTokenKind(GrinTokenKindName::GREATER_THAN_OR_EQUAL, GrinTokenCategory::COMPARISON_OPERATOR), ">=", ">=");
    assertOneToken("=", GrinTokenKind(GrinTokenKindName::EQUAL, GrinTokenCategory::COMPARISON_OPERATOR), "=", "=");
}

TEST(LexingTests, DetectsLiterals) {
    assertOneToken("'BOO'", GrinTokenKind(GrinTokenKindName::LITERAL_STRING, GrinTokenCategory::LITERAL_VALUE), "'BOO'", "BOO");
    assertOneToken("''", GrinTokenKind(GrinTokenKindName::LITERAL_STRING, GrinTokenCategory::LITERAL_VALUE), "''", "");
    assertOneToken("1", GrinTokenKind(GrinTokenKindName::LITERAL_INTEGER, GrinTokenCategory::LITERAL_VALUE), "1", 1);
    assertOneToken("0", GrinTokenKind(GrinTokenKindName::LITERAL_INTEGER, GrinTokenCategory::LITERAL_VALUE), "0", 0);    
    assertOneToken("-1", GrinTokenKind(GrinTokenKindName::LITERAL_INTEGER, GrinTokenCategory::LITERAL_VALUE), "-1", -1);
    assertOneToken("0.5", GrinTokenKind(GrinTokenKindName::LITERAL_DOUBLE, GrinTokenCategory::LITERAL_VALUE), "0.5", 0.5);
    assertOneToken("-0.1", GrinTokenKind(GrinTokenKindName::LITERAL_DOUBLE, GrinTokenCategory::LITERAL_VALUE), "-0.1", -0.1);
}
