#include <iostream>

#include "lexing.hpp"
#include "parsing.hpp"

// Parsing Error
ParsingError::ParsingError(const std::string & msg, const Location & loc)
    : message(msg), error_location(loc){}

Location ParsingError::location() const {
    return error_location;
}

const char* ParsingError::what() const noexcept {
    return std::string(message + error_location.formatted()).c_str();
}

void raise_error(const std::string & msg, const Location & loc) {
    throw ParsingError(msg, loc);
}

void raise_error(const std::string & msg, const Token & token) {
    throw ParsingError(msg, token.location());
}



std::vector<Token> parse_line(std::string line, int line_number) {
    std::vector<Token> tokens(to_tokens(line, line_number));
    int index = 0;

    if (tokens.size() == 0) {
        raise_error("Program lines cannot be empty", Location(line_number, 1));
    }
    else if (tokens.size() == 1 &&
             tokens[0].kind() == TokenKind(TokenKindName::DOT, TokenCategory::KEYWORD)) {
        return tokens;
    }
    
    // helper parsing functions
    auto detect_token = [&](std::vector<TokenKind> kinds) {
        if (index < tokens.size()) {
            for (auto k: kinds) {
                if (tokens[index].kind().kind == k.kind) {
                    return true;
                }
            }
        }
        return false;
    };

    auto expect = [&](std::vector<TokenKind> kinds){
        if (!detect_token(kinds)) {
            std::string msg = "";
            int i = 0;
            for ( ; i < kinds.size() - 1; ++i) {
                msg.append(token_kind_text[static_cast<int>(kinds[i].kind)]);
                msg.append(", ");
            }
            msg.append(token_kind_text[static_cast<int>(kinds[i].kind)]);

            if (index >= tokens.size()) {
                raise_error(msg, Location(line_number, index));
            }
            else {
                raise_error(msg, tokens[index].location());
            }

        };
    };

    auto parse_label = [&](){
        if (detect_token(std::vector<TokenKind>{TokenKind(TokenKindName::IDENTIFIER, TokenCategory::IDENTIFIER)})) {
            ++index;
            expect(std::vector<TokenKind>{TokenKind(TokenKindName::COLON, TokenCategory::PUNCTUATION)});
            ++index;
        };
    };

    auto parse_value = [&](){
        expect(std::vector<TokenKind>{
            TokenKind(TokenKindName::LITERAL_INTEGER, TokenCategory::LITERAL_VALUE),
            TokenKind(TokenKindName::LITERAL_DOUBLE, TokenCategory::LITERAL_VALUE),
            TokenKind(TokenKindName::LITERAL_STRING, TokenCategory::LITERAL_VALUE),
            TokenKind(TokenKindName::IDENTIFIER, TokenCategory::IDENTIFIER)
        });
        ++index;
    };

    auto parse_varirable = [&](){
        expect(std::vector<TokenKind>{TokenKind(TokenKindName::IDENTIFIER, TokenCategory::IDENTIFIER)});
        ++index;
        parse_value();
    };
    
    auto parse_print = [&](){
        parse_value();
    };

    auto parse_input = [&](){
        expect(std::vector<TokenKind>{TokenKind(TokenKindName::IDENTIFIER, TokenCategory::IDENTIFIER)});
        ++index;
    };

    auto parse_target = [&](){
        expect(std::vector<TokenKind>{TokenKind(TokenKindName::LITERAL_INTEGER, TokenCategory::LITERAL_VALUE),
                                    TokenKind(TokenKindName::LITERAL_STRING, TokenCategory::LITERAL_VALUE),
                                    TokenKind(TokenKindName::IDENTIFIER, TokenCategory::IDENTIFIER)});
        ++index;
    };
    
    auto parse_comparison = [&](){
        expect(std::vector<TokenKind>{TokenKind(TokenKindName::EQUAL, TokenCategory::COMPARISON_OPERATOR),
                                          TokenKind(TokenKindName::LESS_THAN, TokenCategory::COMPARISON_OPERATOR),
                                          TokenKind(TokenKindName::LESS_THAN_OR_EQUAL, TokenCategory::COMPARISON_OPERATOR),
                                          TokenKind(TokenKindName::GREATER_THAN, TokenCategory::COMPARISON_OPERATOR),
                                          TokenKind(TokenKindName::GREATER_THAN_OR_EQUAL, TokenCategory::COMPARISON_OPERATOR),
                                          TokenKind(TokenKindName::NOT_EQUAL, TokenCategory::COMPARISON_OPERATOR)});
        ++index;
    };

    auto parse_go = [&](){
        parse_target();
        if (detect_token(std::vector<TokenKind>{TokenKind(TokenKindName::IF, TokenCategory::KEYWORD)})) {
            ++index;
            parse_value();
            parse_comparison();
            parse_value();
        }
    };

    auto parse_empty = [](){};

    auto parse_body = [&](){
        auto t_kind = tokens[index].kind().kind;
        if (t_kind == TokenKindName::LET) {
            ++index;
            parse_varirable();
        }
        else if (t_kind == TokenKindName::PRINT) {
            ++index;
            parse_print();
        }
        else if (t_kind == TokenKindName::INNUM || t_kind == TokenKindName::INSTR) {
            ++index;
            parse_input();
        }
        else if (t_kind == TokenKindName::ADD || t_kind == TokenKindName::SUB 
                 || t_kind == TokenKindName::MULT || t_kind == TokenKindName::DIV) {
            ++index;
            parse_varirable();
        }
        else if (t_kind == TokenKindName::GOTO || t_kind == TokenKindName::GOSUB) {
            ++index;
            parse_go();
        }
        else if (t_kind == TokenKindName::RETURN || t_kind == TokenKindName::END || t_kind == TokenKindName::DOT) {
            ++index;
            parse_empty();
        }
        else {
            raise_error("Statement keyword expected", tokens[index]);
        }
    };
    parse_label();
    
    if (index >= tokens.size()) {
        raise_error("Statement body expected", Location(line_number, line.size()));
    }

    parse_body();

    if (index < tokens.size()) {
        raise_error("Extra tokens after statement end", tokens[index]);
    }

    return tokens;

}

// public method that will be usable
std::vector<std::vector<Token>> parse(const std::vector<std::string> & lines) {
    std::vector<std::vector<Token>> parsed_tokens;

    for(int i = 0; i < lines.size(); ++i) {

        auto tokens = parse_line(lines[i], i+1);  
        
        if (tokens.size() == 1 && tokens[0].kind().kind == TokenKindName::DOT) {
            break;
        }

        parsed_tokens.push_back(tokens);

    }
    return parsed_tokens;
}