#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "interpreter.hpp"
#include "parsing.hpp"
#include "runtime_errors.hpp"

typedef std::variant<int, double, std::string> data_variant;

namespace LetTests{
// Variable assignment tests
TEST(LetTests, AssignInt) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines {"LET A 1", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(LetTests, AssignDouble) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines {"LET A 1.1", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1.1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(LetTests, AssignString) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines {"LET A \"TARO\"", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TARO";
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(LetTests, AssignVariableInt) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines {"LET A 1", "LET B A", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    var["B"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(LetTests, AssignVariableDouble) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines {"LET A 1.1", "LET B A", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1.1;
    var["B"] = 1.1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(LetTests, AssignVariableString) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines {"LET A \"TARO\"", "LET B A", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TARO";
    var["B"] = "TARO";
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(LetTests, ReassignInt) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines {"LET A \"TARO\"", "LET B 1", "LET A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    var["B"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(LetTests, ReassignDouble) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines {"LET A 1", "LET B 1.1", "LET A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1.1;
    var["B"] = 1.1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(LetTests, ReassignString) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines {"LET A 1", "LET B \"TARO\"", "LET A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TARO";
    var["B"] = "TARO";
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}
};

namespace AddTests{
    // Addition tests
TEST(AdditionTests, AddInt) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"ADD A 1", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(AdditionTests, AddDouble) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"ADD A 1.1", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1.1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(AdditionTests, AddStrings) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A \"TARO\"", "ADD A \" MILK TEA\"", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TARO MILK TEA";
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(AdditionTests, AddIntVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1", "LET B 5", "ADD A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 6;
    var["B"] = 5;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(AdditionTests, AddDoubleVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1.1", "LET B 5.5", "ADD A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 6.6;
    var["B"] = 5.5;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(AdditionTests, AddStringVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A \"MATCHA\"", "LET B \" LATTE\"", "ADD A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "MATCHA LATTE";
    var["B"] = " LATTE";
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(AdditionTests, AddIntStringVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1", "LET B \" latte\"", "ADD A B", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), ArithmeticError);
}

TEST(AdditionTests, AddDoubleStringVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1.1", "LET B \" latte\"", "ADD A B", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), ArithmeticError);
}

}

namespace SubTests{
    // Subtraction Tests
TEST(SubtractionTests, SubtractInt) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1", "SUB A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = -1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(SubtractionTests, SubtractDouble) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1.1", "SUB A 2.2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = -1.1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(SubtractionTests, SubtractIntVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1", "LET B 2", "SUB A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = -1;
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(SubtractionTests, SubtractDoubleVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1.1", "LET B 2.2", "SUB A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = -1.1;
    var["B"] = 2.2;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(SubtractionTests, SubtractString) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 2", "SUB A \"TARO\"", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), ArithmeticError);
}

TEST(SubtractionTests, SubtractStringVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A \"TARO\"", "LET B \"MILK\"", "SUB A B", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), ArithmeticError);
}
}

namespace MultTests{
    // Multiplication Tests

TEST(MultiplicationTests, MultiplyInt) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1", "MULT A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 2;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(MultiplicationTests, MultiplyDouble) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1.2", "MULT A 0.5", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0.6;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(MultiplicationTests, MultiplyIntString) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A \"Taro\"", "MULT A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TaroTaro";
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(MultiplicationTests, MultiplyDoubleString) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A \"Taro\"", "MULT A 2.1", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), ArithmeticError);
}

TEST(MultiplicationTests, MultiplyNegIntString) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A \"Taro\"", "MULT A -1", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), ArithmeticError);
}

TEST(MultiplicationTests, MultiplyStringDouble) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 2.1", "MULT A \"TARO\"", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), ArithmeticError);
}

TEST(MultiplicationTests, MultiplyIntVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1", "LET B 2", "MULT A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 2;
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(MultiplicationTests, MultiplyDoubleVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1.4", "LET B 2.5", "MULT A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 3.5;
    var["B"] = 2.5;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(MultiplicationTests, MultiplyStringVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A \"TARO\"", "LET B 2", "MULT A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = "TAROTARO";
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

}

namespace DivTests{
    // Division Tests
TEST(DivisionTests, DivideInt) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 4", "DIV A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 2;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(DivisionTests, DivideDouble) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1.5", "DIV A 2", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0.75;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(DivisionTests, DivideString) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A \"TARO\"", "DIV A 2", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), ArithmeticError);
}

TEST(DivisionTests, DivideIntVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1", "LET B 2", "DIV A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0;
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(DivisionTests, DivideFloatVariable) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1.5", "LET B 2", "DIV A B", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0.75;
    var["B"] = 2;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

}

namespace GoToTests {
    // GOTO tests

TEST(GotoTests, JumpForwards) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 4", "GOTO 2 IF A < 5", "DIV A 2", "DIV A 4", "GOTO 11 IF A <= -11", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(GotoTests, JumpOne) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 4", "GOTO 1", "DIV A 2", "DIV A 4", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(GotoTests, JumpBackwards) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 4", "GOTO \"X\" IF \"A\" < \"B\"",  "END", "X: DIV A 4", "GOTO -2 IF 5 > A", "ADD A 11", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(GotoTests, JumpForwardsOut) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"GOTO 2", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), JumpError);
}

TEST(GotoTests, JumpBackwardsOut) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"GOTO -1", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), JumpError);
}
}

namespace GoSubTests {
TEST(GosubTests, JumpForwards) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 4", "GOSUB 2 IF A < 5", "DIV A 2", "DIV A 4", "GOSUB 11 IF A <= -11", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(GosubTests, JumpOne) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 4", "GOSUB 1", "DIV A 2", "DIV A 4", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 0;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(GosubTests, JumpBackwards) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 4", "GOSUB \"x\" IF \"A\" < \"B\"",  "END", "x: DIV A 4", "GOSUB -2 IF 5 > A", "ADD A 11", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

TEST(GosubTests, JumpForwardsOut) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"GOSUB 2", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), JumpError);
}

TEST(GosubTests, JumpBackwardsOut) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"GOSUB -1", "."};
    ASSERT_THROW(std::stringstream in;interpret_tokens(lines, in, out), JumpError);
}

TEST(GosubTests, Return) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 8", "GOSUB 3", "DIV A 2", "END", "DIV A 4", "RETURN", "."};
    std::map<std::string, data_variant> var{};
    var["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var);
}

}

namespace PrintingTests {
    // Print Tests
TEST(PrintTests, PrintInt) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"PRINT 1", "."};
    interpret_tokens(lines, in, out);
    ASSERT_EQ(out.str(), "1\n");
}

TEST(PrintTests, PrintIntVar) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1", "PRINT A", "."};
    interpret_tokens(lines, in, out);
    ASSERT_EQ(out.str(), "1\n");
}

TEST(PrintTests, PrintDouble) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"PRINT 1.5", "."};
    interpret_tokens(lines, in, out);
    ASSERT_EQ(out.str(), "1.5\n");
}

TEST(PrintTests, PrintDoubleVar) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A 1.5", "PRINT A", "."};
    interpret_tokens(lines, in, out);
    ASSERT_EQ(out.str(), "1.5\n");
}

TEST(PrintTests, PrintString) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"PRINT \"taro\"", "."};
    interpret_tokens(lines, in, out);
    ASSERT_EQ(out.str(), "taro\n");
}

TEST(PrintTests, PrintStringVar) {
    std::stringstream out; std::stringstream in;
    std::vector<std::string> lines{"LET A \"taro\"", "PRINT A", "."};
    interpret_tokens(lines, in, out);
    ASSERT_EQ(out.str(), "taro\n");
}

}

namespace InputTests {

TEST(InnumTest, ReadInt) {
    std::stringstream out; std::stringstream in{"1"};
    std::vector<std::string> lines{"INNUM A", "."};
    std::map<std::string, data_variant> var_map;
    var_map["A"] = 1;
    ASSERT_EQ(interpret_tokens(lines, in, out), var_map);
}

TEST(InnumTest, ReadDouble) {
    std::stringstream out; std::stringstream in{"1.5"};
    std::vector<std::string> lines{"INNUM A", "."};
    std::map<std::string, data_variant> var_map;
    var_map["A"] = 1.5;
    ASSERT_EQ(interpret_tokens(lines, in, out), var_map);
}

TEST(InnumTest, ReadString) {
    std::stringstream out; std::stringstream in{"taro"};
    std::vector<std::string> lines{"INNUM A", "."};
    ASSERT_THROW(interpret_tokens(lines, in, out), InputError);
}

TEST(InstrTest, ReadString) {
    std::stringstream out; std::stringstream in{"1 1.5 hello world\n won't be included"};
    std::vector<std::string> lines{"INSTR A", "."};
    std::map<std::string, data_variant> var_map;
    var_map["A"] = "1 1.5 hello world";
    ASSERT_EQ(interpret_tokens(lines, in, out), var_map);
}
}