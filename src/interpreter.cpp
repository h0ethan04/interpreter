#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

#include "interpreter.hpp"
#include "parsing.hpp"
#include "runtime_errors.hpp"

typedef std::variant<int, double, std::string> data_variant;
typedef std::map<std::string, data_variant> var_map;

var_map interpret_tokens(std::vector<std::string> & lines) {
    std::vector<std::vector<GrinToken>> tokens{parse(lines)};
    std::map<std::string, int> labels{map_labels(tokens)};
    std::map<std::string, data_variant> variables{};

    auto add_tokens = [&variables](const GrinToken & base, data_variant source) {
        data_variant base_value;
        if (variables.contains(base.text())) {
            base_value = variables[base.text()];
        }
        else {
            base_value = 0;
        }

        if (std::holds_alternative<int>(base_value)) {
            if (std::holds_alternative<int>(source)) {
                return data_variant(std::get<int>(base_value) + std::get<int>(source));
            }
            else if (std::holds_alternative<double>(source)) {
                return data_variant(std::get<int>(base_value) + std::get<double>(source));
            }
            else {
                raise_ArithmeticError("Cannot add type string to base type int", base.location());
            }
        }
        else if (std::holds_alternative<double>(base_value)) {
            if (std::holds_alternative<int>(source)) {
                return data_variant(std::get<double>(base_value) + std::get<int>(source));
            }
            else if (std::holds_alternative<double>(source)) {
                return data_variant(std::get<double>(base_value) + std::get<double>(source));
            }
            else {
                raise_ArithmeticError("Cannot add type string to base type double", base.location());
            }
        }
        else if (std::holds_alternative<std::string>(base_value)) {
            if (std::holds_alternative<std::string>(source)) {
                return data_variant(std::get<std::string>(base_value) + std::get<std::string>(source));
            }
            else {
                raise_ArithmeticError("Cannot add non-string type to base type string", base.location());
            }
        }
    };

    auto sub_tokens = [&variables](const GrinToken & base, data_variant source) {
        data_variant base_value;
        if (variables.contains(base.text())) {
            base_value = variables[base.text()];
        }
        else {
            base_value = 0;
        }

        if (std::holds_alternative<int>(base_value)) {
            if (std::holds_alternative<int>(source)) {
                return data_variant(std::get<int>(base_value) - std::get<int>(source));
            }
            else if (std::holds_alternative<double>(source)) {
                return data_variant(std::get<int>(base_value) - std::get<double>(source));
            }
            else {
                raise_ArithmeticError("Cannot subtract type string from base type int", base.location());
            }
        }
        else if (std::holds_alternative<double>(base_value)) {
            if (std::holds_alternative<int>(source)) {
                return data_variant(std::get<double>(base_value) - std::get<int>(source));
            }
            else if (std::holds_alternative<double>(source)) {
                return data_variant(std::get<double>(base_value) - std::get<double>(source));
            }
            else {
                raise_ArithmeticError("Cannot subtract type string from base type double", base.location());
            }
        }
        else {
            raise_ArithmeticError("Cannot subtract non-numeric types", base.location());
        }
    };

    auto mult_tokens = [&variables](const GrinToken & base, data_variant source) {
        data_variant base_value;
        if (variables.contains(base.text())) {
            base_value = variables[base.text()];
        }
        else {
            base_value = 0;
        }
    };

    auto div_tokens = [&variables](const GrinToken & base, data_variant source) {
        data_variant base_value;
        if (variables.contains(base.text())) {
            base_value = variables[base.text()];
        }
        else {
            base_value = 0;
        }
    };


    auto interpret_line = [&](const std::vector<GrinToken> & line, int line_number){
        GrinToken first_token = line[0];
        if (first_token.kind().kind == GrinTokenKindName::LET){
            if (line[2].kind().kind == GrinTokenKindName::IDENTIFIER) {
                if (variables.contains(line[2].text())) {
                    variables[line[1].text()] = variables[line[2].text()];
                }
                else {
                    variables[line[1].text()] = 0;
                }
            }
            else {
                variables[line[1].text()] = line[2].value();
            }
        }
        else if (first_token.kind().kind == GrinTokenKindName::ADD) {
            if (line[2].kind().kind == GrinTokenKindName::IDENTIFIER) {
                if (variables.contains(line[2].text())) {
                    variables[line[1].text()] = add_tokens(line[1], variables[line[2].text()]);
                }
                else {
                    variables[line[1].text()] = add_tokens(line[1], 0);
                }
            }
            else {
                variables[line[1].text()] = add_tokens(line[1], line[2].value());
            }
        }
        else if (first_token.kind().kind == GrinTokenKindName::SUB) {
            if (line[2].kind().kind == GrinTokenKindName::IDENTIFIER) {
                if (variables.contains(line[2].text())) {
                    variables[line[1].text()] = sub_tokens(line[1], variables[line[2].text()]);
                }
                else {
                    variables[line[1].text()] = sub_tokens(line[1], 0);
                }
            }
            else {
                variables[line[1].text()] = sub_tokens(line[1], line[2].value());
            }
        }
        else if (first_token.kind().kind == GrinTokenKindName::MULT) {

        }
        else if (first_token.kind().kind == GrinTokenKindName::DIV) {

        }
        else if (first_token.kind().kind == GrinTokenKindName::GOTO) {

        }
        else if (first_token.kind().kind == GrinTokenKindName::GOSUB) {

        }
        else if (first_token.kind().kind == GrinTokenKindName::RETURN) {
            
        }
        else if (first_token.kind().kind == GrinTokenKindName::INNUM) {

        }
        else if (first_token.kind().kind == GrinTokenKindName::INSTR) {

        }
        else if (first_token.kind().kind == GrinTokenKindName::END) {

        }

    };

    for (unsigned int i = 0; i < tokens.size(); ++i) {
        if (tokens[i][0].kind().kind == GrinTokenKindName::IDENTIFIER && 
            tokens[i][1].kind().kind == GrinTokenKindName::COLON) {
            std::vector<GrinToken> temp{};
            for (int j = 2; j < tokens[i].size(); ++j) {
                temp.push_back(tokens[i][j]);
            }
            interpret_line(temp, i);
        }
        else {
            interpret_line(tokens[i], i);
        }
    }

    return variables;
}