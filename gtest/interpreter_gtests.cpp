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

TEST(AdditionTests, AddIntString) {
    std::vector<std::string> lines{"LET A 1", "LET B ' latte'", "ADD A B", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}

TEST(AdditionTests, AddDoubleString) {
    std::vector<std::string> lines{"LET A 1.1", "LET B ' latte'", "ADD A B", "."};
    ASSERT_THROW(interpret_tokens(lines), ArithmeticError);
}

}
