#include <gtest/gtest.h>

#include <iostream>
#include <utility>
#include <vector>

#include "interpreter.hpp"
#include "parsing.hpp"
#include "runtime_errors.hpp"

typedef std::variant<int, double, std::string> data_variant;

namespace LetTests{
// Variable assignment tests
TEST(LetTests, AssignInt) {
    std::vector<std::string> lines {"LET A 1", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(LetTests, AssignDouble) {
    std::vector<std::string> lines {"LET A 1.1", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1.1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(LetTests, AssignString) {
    std::vector<std::string> lines {"LET A 'TARO'", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TARO";
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(LetTests, AssignVariableInt) {
    std::vector<std::string> lines {"LET A 1", "LET B A", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    var["B"] = 1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(LetTests, AssignVariableDouble) {
    std::vector<std::string> lines {"LET A 1.1", "LET B A", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1.1;
    var["B"] = 1.1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(LetTests, AssignVariableString) {
    std::vector<std::string> lines {"LET A 'TARO'", "LET B A", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TARO";
    var["B"] = "TARO";
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(LetTests, ReassignInt) {
    std::vector<std::string> lines {"LET A 'TARO'", "LET B 1", "LET A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    var["B"] = 1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(LetTests, ReassignDouble) {
    std::vector<std::string> lines {"LET A 1", "LET B 1.1", "LET A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1.1;
    var["B"] = 1.1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(LetTests, ReassignString) {
    std::vector<std::string> lines {"LET A 1", "LET B 'TARO'", "LET A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TARO";
    var["B"] = "TARO";
    ASSERT_EQ(interpret_tokens(lines), var);
}
};

namespace AddTests{
    // Addition tests
TEST(AdditionTests, AddInt) {
    std::vector<std::string> lines{"ADD A 1", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(AdditionTests, AddDouble) {
    std::vector<std::string> lines{"ADD A 1.1", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1.1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(AdditionTests, AddStrings) {
    std::vector<std::string> lines{"LET A 'TARO'", "ADD A ' MILK TEA'", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TARO MILK TEA";
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(AdditionTests, AddIntVariable) {
    std::vector<std::string> lines{"LET A 1", "LET B 5", "ADD A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 6;
    var["B"] = 5;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(AdditionTests, AddDoubleVariable) {
    std::vector<std::string> lines{"LET A 1.1", "LET B 5.5", "ADD A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 6.6;
    var["B"] = 5.5;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(AdditionTests, AddStringVariable) {
    std::vector<std::string> lines{"LET A 'MATCHA'", "LET B ' LATTE'", "ADD A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "MATCHA LATTE";
    var["B"] = " LATTE";
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(AdditionTests, AddIntStringVariable) {
    std::vector<std::string> lines{"LET A 1", "LET B ' latte'", "ADD A B", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}

TEST(AdditionTests, AddDoubleStringVariable) {
    std::vector<std::string> lines{"LET A 1.1", "LET B ' latte'", "ADD A B", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}

}

namespace SubTests{
    // Subtraction Tests
TEST(SubtractionTests, SubtractInt) {
    std::vector<std::string> lines{"LET A 1", "SUB A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = -1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(SubtractionTests, SubtractDouble) {
    std::vector<std::string> lines{"LET A 1.1", "SUB A 2.2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = -1.1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(SubtractionTests, SubtractIntVariable) {
    std::vector<std::string> lines{"LET A 1", "LET B 2", "SUB A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = -1;
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(SubtractionTests, SubtractDoubleVariable) {
    std::vector<std::string> lines{"LET A 1.1", "LET B 2.2", "SUB A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = -1.1;
    var["B"] = 2.2;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(SubtractionTests, SubtractString) {
    std::vector<std::string> lines{"LET A 2", "SUB A 'TARO'", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}

TEST(SubtractionTests, SubtractStringVariable) {
    std::vector<std::string> lines{"LET A 'TARO'", "LET B 'MILK'", "SUB A B", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}
}

namespace MultTests{
    // Multiplication Tests

TEST(MultiplicationTests, MultiplyInt) {
    std::vector<std::string> lines{"LET A 1", "MULT A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 2;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(MultiplicationTests, MultiplyDouble) {
    std::vector<std::string> lines{"LET A 1.2", "MULT A 0.5", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0.6;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(MultiplicationTests, MultiplyIntString) {
    std::vector<std::string> lines{"LET A 'Taro'", "MULT A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TaroTaro";
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(MultiplicationTests, MultiplyDoubleString) {
    std::vector<std::string> lines{"LET A 'Taro'", "MULT A 2.1", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}

TEST(MultiplicationTests, MultiplyNegIntString) {
    std::vector<std::string> lines{"LET A 'Taro'", "MULT A -1", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}

TEST(MultiplicationTests, MultiplyStringDouble) {
    std::vector<std::string> lines{"LET A 2.1", "MULT A 'TARO'", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}

TEST(MultiplicationTests, MultiplyIntVariable) {
    std::vector<std::string> lines{"LET A 1", "LET B 2", "MULT A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 2;
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(MultiplicationTests, MultiplyDoubleVariable) {
    std::vector<std::string> lines{"LET A 1.4", "LET B 2.5", "MULT A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 3.5;
    var["B"] = 2.5;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(MultiplicationTests, MultiplyStringVariable) {
    std::vector<std::string> lines{"LET A 'TARO'", "LET B 2", "MULT A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TAROTARO";
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines), var);
}

}

namespace DivTests{
    // Division Tests
TEST(DivisionTests, DivideInt) {
    std::vector<std::string> lines{"LET A 4", "DIV A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 2;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(DivisionTests, DivideDouble) {
    std::vector<std::string> lines{"LET A 1.5", "DIV A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0.75;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(DivisionTests, DivideString) {
    std::vector<std::string> lines{"LET A 'TARO'", "DIV A 2", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}

TEST(DivisionTests, DivideIntVariable) {
    std::vector<std::string> lines{"LET A 1", "LET B 2", "DIV A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0;
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(DivisionTests, DivideFloatVariable) {
    std::vector<std::string> lines{"LET A 1.5", "LET B 2", "DIV A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0.75;
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines), var);
}

}

namespace GoToTests {
    // GOTO tests

TEST(GotoTests, JumpForwards) {
    std::vector<std::string> lines{"LET A 4", "GOTO 2 IF A < 5", "DIV A 2", "DIV A 4", "GOTO 11 IF A <= -11", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(GotoTests, JumpOne) {
    std::vector<std::string> lines{"LET A 4", "GOTO 1", "DIV A 2", "DIV A 4", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0;
    ASSERT_EQ(interpret_tokens(lines), var);
}

TEST(GotoTests, JumpBackwards) {
    std::vector<std::string> lines{"LET A 4", "GOTO 2 IF 'A' < 'B'",  "END", "DIV A 4", "GOTO -2 IF 5 > A", "ADD A 11", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines), var);
}

}

namespace GoSubTests {

}