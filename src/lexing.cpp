#include <iostream>

#include "lexing.hpp"

// Lexing Error
LexingError::LexingError(const std::string & msg, const Location & loc) 
    : message(msg), error_location(loc){}

Location LexingError::location() const {
    return error_location;
}

const char* LexingError::what() const noexcept {
    return std::string(message + error_location.formatted()).c_str();
}

// used to throw Lexing errors
void raise_lexing_error(const std::string & msg, const Location & loc) {
    throw LexingError(msg, loc);
}


std::vector<Token> to_tokens(const std::string & line, int line_number) {
    populate_token_kind_map();
    int index = 0;
    int start = 0;
    int len = line.length();
    std::vector<Token> line_to_tokens{};
    auto make_token = [&line, &line_number, &index, &start] 
                      (const TokenKind & kind, const std::variant<int, double, std::string> & value) {
                        return Token(kind, value, line.substr(start, index-start), Location(line_number, start+1));
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

                line_to_tokens.push_back(make_token(TokenKind(tk_parts.first, tk_parts.second), substring));
            }
            else {
                TOKEN_MAP.insert(std::pair<std::string, std::pair<TokenKindName, TokenCategory>> (substring, std::pair(TokenKindName::IDENTIFIER, TokenCategory::IDENTIFIER)));

                line_to_tokens.push_back(make_token(TokenKind(TokenKindName::IDENTIFIER, TokenCategory::IDENTIFIER), substring));
            }
        }
        else if (line[index] == '\'') {
            ++index;

            while (index < len && line[index] != '\'') {
                ++index;
            }

            if (index == len) {
                raise_lexing_error("Newline in string literal", Location(line_number, index));
            }
            ++index;
            line_to_tokens.push_back(make_token(TokenKind(TokenKindName::LITERAL_STRING, TokenCategory::LITERAL_VALUE),
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
                raise_lexing_error("Negation must be followed by at least one digit", Location(line_number, index));
            }
            else if (index < len && line[index] == '.') {
                ++index;
                while (index < len && isdigit(line[index])) {
                    ++index;
                }
                line_to_tokens.push_back(make_token(TokenKind(TokenKindName::LITERAL_DOUBLE, TokenCategory::LITERAL_VALUE),
                    std::stod(line.substr(start, index-start))));
            }
            else {
                line_to_tokens.push_back(make_token(TokenKind(TokenKindName::LITERAL_INTEGER, TokenCategory::LITERAL_VALUE),
                    std::stoi(line.substr(start, index-start))));
            }
        }
        else if (line[index] == ':') {
            ++index;
            line_to_tokens.push_back(make_token(TokenKind(TokenKindName::COLON, TokenCategory::PUNCTUATION), ":"));
        }
        else if (line[index] == '.') {
            ++index;
            line_to_tokens.push_back(make_token(TokenKind(TokenKindName::DOT, TokenCategory::PUNCTUATION), "."));
        }
        else if (line[index] == '=') {
            ++index;
            line_to_tokens.push_back(make_token(TokenKind(TokenKindName::EQUAL, TokenCategory::COMPARISON_OPERATOR), "="));
        }
        else if (line[index] == '<') {
            ++index;
            if (index < len && line[index] == '>') {
                ++index;
                line_to_tokens.push_back(make_token(TokenKind(TokenKindName::NOT_EQUAL, TokenCategory::COMPARISON_OPERATOR), "<>"));
            }
            else if (index < len && line[index] == '=') {
                ++index;
                line_to_tokens.push_back(make_token(TokenKind(TokenKindName::LESS_THAN_OR_EQUAL, TokenCategory::COMPARISON_OPERATOR), "<="));
            }
            else {
                line_to_tokens.push_back(make_token(TokenKind(TokenKindName::LESS_THAN, TokenCategory::COMPARISON_OPERATOR), "<"));
            }
        }
        else if (line[index] == '>') {
            ++index;
            if (index < len && line[index] == '=') {
                ++index;
                line_to_tokens.push_back(make_token(TokenKind(TokenKindName::GREATER_THAN_OR_EQUAL, TokenCategory::COMPARISON_OPERATOR), ">="));
            }
            else {
                line_to_tokens.push_back(make_token(TokenKind(TokenKindName::GREATER_THAN, TokenCategory::COMPARISON_OPERATOR), ">"));
            }
        }
        else {
            raise_lexing_error("Invalid character", Location(line_number, index));
        }
    }
    
    return line_to_tokens;
}