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

var_map interpret_tokens(const std::vector<std::string> & lines, std::istream & in, std::ostream & out) {
    std::vector<std::vector<GrinToken>> tokens{parse(lines)};
    std::map<std::string, int> labels{map_labels(tokens)};
    std::map<std::string, data_variant> variables{};
    std::vector<int> return_line{};

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
        else {
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

        if (std::holds_alternative<int>(base_value)) {
            if (std::holds_alternative<int>(source)) {
                return data_variant(std::get<int>(base_value) * std::get<int>(source));
            }
            else if (std::holds_alternative<double>(source)) {
                return data_variant(std::get<int>(base_value) * std::get<double>(source));
            }
            else {
                if (std::get<int>(base_value) >= 0) {
                    std::string new_string{};
                    for (int i = 0; i < std::get<int>(base_value); ++i) {
                        new_string.append(std::get<std::string>(source));
                    }
                    return data_variant(new_string);
                }
                else {
                    raise_ArithmeticError("Cannot multiply strings by negative integers", base.location());
                }
            }
        }
        else if (std::holds_alternative<double>(base_value)) {
            if (std::holds_alternative<int>(source)) {
                return data_variant(std::get<double>(base_value) * std::get<int>(source));
            }
            else if (std::holds_alternative<double>(source)) {
                return data_variant(std::get<double>(base_value) * std::get<double>(source));
            }
            else {
                raise_ArithmeticError("Cannot multiply strings by doubles", base.location());
            }
        }
        else {
            if (std::holds_alternative<int>(source)) {
                if (std::get<int>(source) >= 0) {
                    std::string new_string{};
                    for (int i = 0; i < std::get<int>(source); ++i) {
                        new_string.append(std::get<std::string>(base_value));
                    }
                    return data_variant(new_string);
                }
                else {
                    raise_ArithmeticError("Cannot multiply strings by negative integers", base.location());
                }
                
            }
            else {
                raise_ArithmeticError("Cannot multiply strings non-integer types", base.location());
            }
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

        if (std::holds_alternative<int>(base_value)) {
            if (std::holds_alternative<int>(source)) {
                return data_variant(std::get<int>(base_value) / std::get<int>(source));
            }
            else if (std::holds_alternative<double>(base_value)) {
                return data_variant(std::get<int>(base_value) / std::get<double>(source));
            }
            else {
                raise_ArithmeticError("Cannot divide base type int by string", base.location());
            }
        }
        else if (std::holds_alternative<double>(base_value)) {
            if (std::holds_alternative<int>(source)) {
                return data_variant(std::get<double>(base_value) / std::get<int>(source));
            }
            else if (std::holds_alternative<double>(source)) {
                return data_variant(std::get<double>(base_value) / std::get<double>(source));
            }
            else {
                raise_ArithmeticError("Cannot divide base type double by string", base.location());
            }
        }
        else {
            raise_ArithmeticError("Cannot divide base type string", base.location());
        }
    };

    auto print_value = [&variables](const GrinToken & token, std::ostream & out) {
        if (variables.contains(token.text())) {
            if (std::holds_alternative<int>(variables[token.text()])) {
                out << std::get<int>(variables[token.text()]) << std::endl;
            }
            else if (std::holds_alternative<double>(variables[token.text()])) {
                out << std::get<double>(variables[token.text()]) << std::endl;
            }
            else {
                out << std::get<std::string>(variables[token.text()]) << std::endl;
            }
        }
        else {
            if (std::holds_alternative<int>(token.value())) {
                out << std::get<int>(token.value()) << std::endl;
            }
            else if (std::holds_alternative<double>(token.value())) {
                out << std::get<double>(token.value()) << std::endl;
            }
            else {
                out << std::get<std::string>(token.value()) << std::endl;
            }
        }
    };

    auto interpret_line = [&](const std::vector<GrinToken> & line, int & line_number){
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
            if (line[2].kind().kind == GrinTokenKindName::IDENTIFIER) {
                if (variables.contains(line[2].text())) {
                    variables[line[1].text()] = mult_tokens(line[1], variables[line[2].text()]);
                }
                else {
                    variables[line[1].text()] = mult_tokens(line[1], 0);
                }
            }
            else {
                variables[line[1].text()] = mult_tokens(line[1], line[2].value());
            }
        }
        else if (first_token.kind().kind == GrinTokenKindName::DIV) {
            if (line[2].kind().kind == GrinTokenKindName::IDENTIFIER) {
                if (variables.contains(line[2].text())) {
                    variables[line[1].text()] = div_tokens(line[1], variables[line[2].text()]);
                }
                else {
                    variables[line[1].text()] = div_tokens(line[1], 0);
                }
            }
            else {
                variables[line[1].text()] = div_tokens(line[1], line[2].value());
            }
        }
        else if (first_token.kind().kind == GrinTokenKindName::GOTO) {
            if (line.size() == 6) {
                std::vector<GrinToken> temp{};
                temp.push_back(line[3]);
                temp.push_back(line[4]);
                temp.push_back(line[5]);
                if (!run_comparison(temp, variables)){
                    return;
                }
            }
            
            if (line[1].kind().kind == GrinTokenKindName::IDENTIFIER) {
                if (variables.contains(line[1].text())) {
                    if (std::holds_alternative<int>(variables[line[1].text()])) {
                        if (line_number + std::get<int>(variables[line[1].text()]) > tokens.size() || line_number + std::get<int>(variables[line[1].text()]) < 0) {
                            raise_JumpError("Target line out of bounds", line[1].location());
                        }
                        else {
                            line_number += std::get<int>(variables[line[1].text()]) - 1;
                        }
                    }
                    else if (std::holds_alternative<std::string>(variables[line[1].text()])) {
                        if (labels.contains(std::get<std::string>(variables[line[1].text()]))) {
                            line_number = -1 + labels[std::get<std::string>(variables[line[1].text()])];
                        }
                        else {
                            line_number = -1;
                        }
                    }
                    else {
                        raise_JumpError("Type double is an invalid target", line[1].location());
                    }
                }
                else {
                    line_number = -1;
                }
            }
            else if (line[1].kind().kind == GrinTokenKindName::LITERAL_INTEGER) {
                if (line_number + std::get<int>(line[1].value()) > tokens.size() || line_number + std::get<int>(line[1].value()) < 0) {
                    raise_JumpError("Target line out of bounds", line[1].location());
                }
                else {
                    line_number += std::get<int>(line[1].value()) - 1;
                }
            }
            else if (line[1].kind().kind == GrinTokenKindName::LITERAL_STRING) {
                if (labels.contains(std::get<std::string>(line[1].value()))) {
                    line_number = -1 + labels[std::get<std::string>(line[1].value())];
                }
                else {
                    line_number = -1;
                }
            }
            else {
                raise_JumpError("Invalid target for GOTO", line[1].location());
            }
        }
        else if (first_token.kind().kind == GrinTokenKindName::GOSUB) {
            if (line.size() == 6) {
                std::vector<GrinToken> temp{};
                temp.push_back(line[3]);
                temp.push_back(line[4]);
                temp.push_back(line[5]);
                if (!run_comparison(temp, variables)){
                    return;
                }
            }
            return_line.push_back(line_number);
            if (line[1].kind().kind == GrinTokenKindName::IDENTIFIER) {
                if (variables.contains(line[1].text())) {
                    if (std::holds_alternative<int>(variables[line[1].text()])) {
                        if (line_number + std::get<int>(variables[line[1].text()]) > tokens.size() || line_number + std::get<int>(variables[line[1].text()]) < 0) {
                            raise_JumpError("Target line out of bounds", line[1].location());
                        }
                        else {
                            line_number += std::get<int>(variables[line[1].text()]) - 1;
                        }
                    }
                    else if (std::holds_alternative<std::string>(variables[line[1].text()])) {
                        if (labels.contains(std::get<std::string>(variables[line[1].text()]))) {
                            line_number = -1 + labels[std::get<std::string>(variables[line[1].text()])];
                        }
                        else {
                            line_number = -1;
                        }
                    }
                    else {
                        raise_JumpError("Type double is an invalid target", line[1].location());
                    }
                }
                else {
                    line_number = -1;
                }
            }
            else if (line[1].kind().kind == GrinTokenKindName::LITERAL_INTEGER) {
                if (line_number + std::get<int>(line[1].value()) > tokens.size() || line_number + std::get<int>(line[1].value()) < 0) {
                    raise_JumpError("Target line out of bounds", line[1].location());
                }
                else {
                    line_number += std::get<int>(line[1].value()) - 1;
                }
            }
            else if (line[1].kind().kind == GrinTokenKindName::LITERAL_STRING) {
                if (labels.contains(std::get<std::string>(line[1].value()))) {
                    line_number = -1 + labels[std::get<std::string>(line[1].value())];
                }
                else {
                    line_number = -1;
                }
            }
            else {
                raise_JumpError("Invalid target for GOSUB", line[1].location());
            }
        }
        else if (first_token.kind().kind == GrinTokenKindName::RETURN) {
            if (return_line.size()) {
                line_number = return_line.back();
                return_line.pop_back();
            }
            else {
                raise_ReturnError("Return without matching GOSUB", first_token.location());
            }
        }
        else if (first_token.kind().kind == GrinTokenKindName::PRINT) {
            print_value(line[1], out);
        }
        else if (first_token.kind().kind == GrinTokenKindName::INNUM) {
            int integer;
            double floating;
            std::string new_value;
            in >> new_value;
            try {
                integer = std::stoi(new_value);
                floating = std::stod(new_value);
            }
            catch(const std::invalid_argument & e) {
                raise_InputError("Cannot parse numeric value from string", line[1].location());
            }
            catch(const std::range_error & e) {
                raise_InputError("Numeric value was too large", line[1].location());
            }
            
            if (new_value.find(".") == std::string::npos) {
                variables[line[1].text()] = integer;
            }
            else {
                variables[line[1].text()] = floating;
            }

        }
        else if (first_token.kind().kind == GrinTokenKindName::INSTR) {
            std::string new_variable;
            std::getline(in, new_variable);
            variables[line[1].text()] = new_variable;
        }
        else if (first_token.kind().kind == GrinTokenKindName::END) {
            raise_EndError();
        }

    };

    for (int i = 0; i < tokens.size(); ++i) {
        try
        {
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
        catch(const EndError& e)
        {
            return variables;
        }
        
    }

    return variables;
}