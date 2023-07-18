#include <iostream>

#include "lexing.hpp"

// Lexing Error
LexingError::LexingError(const std::string & msg, const GrinLocation & loc) 
    : message(msg), error_location(loc){}

GrinLocation LexingError::location() const {
    return error_location;
}

const char* LexingError::what() const noexcept {
    return std::string(message + error_location.formatted()).c_str();
}

// used to throw Lexing errors
void raise_lexing_error(const std::string & msg, const GrinLocation & loc) {
    throw LexingError(msg, loc);
}


std::vector<GrinToken> to_tokens(const std::string & line, int line_number) {
    populate_token_kind_map();
    int index = 0;
    int start = 0;
    int len = line.length();
    std::vector<GrinToken> line_to_tokens{};
    auto make_token = [&line, &line_number, &index, &start] 
                      (const GrinTokenKind & kind, const std::variant<int, double, std::string> & value) {
                        return GrinToken(kind, value, line.substr(start, index-start), GrinLocation(line_number, start+1));
                      };
    while(true) {
        while(index < len && line[index] == ' ') {
            ++index;
        }
        
        if (index == len || index < 0) {
            break;
        }

        start = index;

        if (isalpha(line[index])) {
            ++index;

            while(index < len && isalnum(line[index])) {
                ++index;
            }
            std::string substring = line.substr(start, index-start);
            if (TOKEN_MAP.contains(substring)) {
                auto tk_parts = TOKEN_MAP[substring];

                line_to_tokens.push_back(make_token(GrinTokenKind(tk_parts.first, tk_parts.second), substring));
            }
            else {
                TOKEN_MAP.insert(std::pair<std::string, std::pair<GrinTokenKindName, GrinTokenCategory>> (substring, std::pair(GrinTokenKindName::IDENTIFIER, GrinTokenCategory::IDENTIFIER)));

                line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::IDENTIFIER, GrinTokenCategory::IDENTIFIER), substring));
            }
        }
        else if (line[index] == '\'') {
            ++index;

            while (index < len && line[index] != '\'') {
                ++index;
            }

            if (index == len) {
                raise_lexing_error("Newline in string literal", GrinLocation(line_number, index));
            }
            ++index;
            line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::LITERAL_STRING, GrinTokenCategory::LITERAL_VALUE),
                line.substr(start + 1, index-start-2)));
        }
        else if (line[index] == '-' || isdigit(line[index])) {
            bool negated = line[index] == '-';
            ++index;

            int digits = negated ? 0 : 1;
            while (index < len && isdigit(line[index])) {
                ++index;
                ++digits;
            }
            if (negated && !digits) {
                raise_lexing_error("Negation must be followed by at least one digit", GrinLocation(line_number, index));
            }
            else if (index < len && line[index] == '.') {
                ++index;
                while (index < len && isdigit(line[index])) {
                    ++index;
                }
                line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::LITERAL_DOUBLE, GrinTokenCategory::LITERAL_VALUE),
                    std::stod(line.substr(start, index-start))));
            }
            else {
                line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::LITERAL_INTEGER, GrinTokenCategory::LITERAL_VALUE),
                    std::stoi(line.substr(start, index-start))));
            }
        }
        else if (line[index] == ':') {
            ++index;
            line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::COLON, GrinTokenCategory::PUNCTUATION), ":"));
        }
        else if (line[index] == '.') {
            ++index;
            line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::DOT, GrinTokenCategory::PUNCTUATION), "."));
        }
        else if (line[index] == '=') {
            ++index;
            line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::EQUAL, GrinTokenCategory::COMPARISON_OPERATOR), "="));
        }
        else if (line[index] == '<') {
            ++index;
            if (index < len && line[index] == '>') {
                ++index;
                line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::NOT_EQUAL, GrinTokenCategory::COMPARISON_OPERATOR), "<>"));
            }
            else if (index < len && line[index] == '=') {
                ++index;
                line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::LESS_THAN_OR_EQUAL, GrinTokenCategory::COMPARISON_OPERATOR), "<="));
            }
            else {
                line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::LESS_THAN, GrinTokenCategory::COMPARISON_OPERATOR), "<"));
            }
        }
        else if (line[index] == '>') {
            ++index;
            if (index < len && line[index] == '=') {
                ++index;
                line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::GREATER_THAN_OR_EQUAL, GrinTokenCategory::COMPARISON_OPERATOR), ">="));
            }
            else {
                line_to_tokens.push_back(make_token(GrinTokenKind(GrinTokenKindName::GREATER_THAN, GrinTokenCategory::COMPARISON_OPERATOR), ">"));
            }
        }
        else {
            raise_lexing_error("Invalid character", GrinLocation(line_number, index));
        }
    }
    
    return line_to_tokens;
}