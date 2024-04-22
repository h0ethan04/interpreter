
#include "comparison.hpp"
#include "runtime_errors.hpp"


typedef std::variant<int, double, std::string> data_variant;

bool less_than(const Token & left_token, const Token & right_token, const std::map<std::string, data_variant> & variables) {
    data_variant left;
    data_variant right;
    if (left_token.kind().kind == TokenKindName::IDENTIFIER) {
        if (variables.contains(left_token.text())) {
            left = variables.at(left_token.text());
        }
        else {
            left = 0;
        }
    }
    else {
        left = left_token.value();
    }

    if (right_token.kind().kind == TokenKindName::IDENTIFIER) {
        if (variables.contains(right_token.text())) {
            right = variables.at(right_token.text());
        }
        else {
            right = 0;
        }
    }
    else {
        right = right_token.value();
    }
    
    if (std::holds_alternative<int>(left)) {
        if (std::holds_alternative<int>(right)) {
            return std::get<int>(left) < std::get<int>(right);
        }
        else if (std::holds_alternative<double>(right)) {
            return std::get<int>(left) < std::get<double>(right);
        }
        else {
            raise_ComparisonError("Cannot compare numeric types to type string", left_token.location());
        }
    }
    else if (std::holds_alternative<double>(left)) {
        if (std::holds_alternative<int>(right)) {
            return std::get<double>(left) < std::get<int>(right);
        }
        else if (std::holds_alternative<double>(right)) {
            return std::get<double>(left) < std::get<double>(right);
        }
        else {
            raise_ComparisonError("Cannot compare numeric types to type string", left_token.location());
        }
    }
    else {
        if (std::holds_alternative<std::string>(right)) {
            return std::get<std::string>(left) < std::get<std::string>(right);
        }
        else {
            raise_ComparisonError("Cannot compare numeric types to type string", left_token.location());
        }
    }
}



bool equal(const Token & left_token, const Token & right_token, const std::map<std::string, data_variant> & variables) {
        data_variant left;
    data_variant right;
    if (left_token.kind().kind == TokenKindName::IDENTIFIER) {
        if (variables.contains(left_token.text())) {
            left = variables.at(left_token.text());
        }
        else {
            left = 0;
        }
    }
    else {
        left = left_token.value();
    }

    if (right_token.kind().kind == TokenKindName::IDENTIFIER) {
        if (variables.contains(right_token.text())) {
            right = variables.at(right_token.text());
        }
        else {
            right = 0;
        }
    }
    else {
        right = right_token.value();
    }
    
    if (std::holds_alternative<int>(left)) {
        if (std::holds_alternative<int>(right)) {
            return std::get<int>(left) == std::get<int>(right);
        }
        else if (std::holds_alternative<double>(right)) {
            return std::get<int>(left) == std::get<double>(right);
        }
        else {
            raise_ComparisonError("Cannot compare numeric types to type string", left_token.location());
        }
    }
    else if (std::holds_alternative<double>(left)) {
        if (std::holds_alternative<int>(right)) {
            return std::get<double>(left) == std::get<int>(right);
        }
        else if (std::holds_alternative<double>(right)) {
            return std::get<double>(left) == std::get<double>(right);
        }
        else {
            raise_ComparisonError("Cannot compare numeric types to type string", left_token.location());
        }
    }
    else {
        if (std::holds_alternative<std::string>(right)) {
            return std::get<std::string>(left) == std::get<std::string>(right);
        }
        else {
            raise_ComparisonError("Cannot compare numeric types to type string", left_token.location());
        }
    }
}


bool run_comparison(const std::vector<Token> & line,
                    const std::map<std::string, data_variant> & variables) {
    auto comp = line[1].kind().kind;
    if (comp == TokenKindName::LESS_THAN) {
        return less_than(line[0], line[2], variables);
    }
    else if (comp == TokenKindName::GREATER_THAN) {
        return !(less_than(line[0], line[2], variables) || equal(line[0], line[2], variables));
    }
    else if (comp == TokenKindName::EQUAL) {
        return equal(line[0], line[2], variables);
    }
    else if (comp == TokenKindName::NOT_EQUAL) {
        return !equal(line[0], line[2], variables);
    }
    else if (comp == TokenKindName::LESS_THAN_OR_EQUAL) {
        return less_than(line[0], line[2], variables) || equal(line[0], line[2], variables);
    }
    else if (comp == TokenKindName::GREATER_THAN_OR_EQUAL) {
        return !less_than(line[0], line[2], variables);
    }
    
}