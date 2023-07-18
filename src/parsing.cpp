#include <iostream>

#include "parsing.hpp"

// Parsing Error
ParsingError::ParsingError(const std::string & msg, const GrinLocation & loc)
    : message(msg), error_location(loc){}

GrinLocation ParsingError::location() const {
    return error_location;
}

const char* ParsingError::what() const noexcept {
    return std::string(message + error_location.formatted()).c_str();
}

void raise_error(const std::string & msg, const GrinLocation & loc) {
    throw ParsingError(msg, loc);
}

void raise_error(const std::string & msg, const GrinToken & token) {
    throw ParsingError(msg, token.location());
}



std::vector<GrinToken> parse_line(std::string line, int line_number) {
    std::vector<GrinToken> tokens(to_tokens(line, line_number));
    int index = 0;

    if (tokens.size() == 0) {
        raise_error("Program lines cannot be empty", GrinLocation(line_number, 1));
    }
    else if (tokens.size() == 1 &&
             tokens[0].kind() == GrinTokenKind(GrinTokenKindName::DOT, GrinTokenCategory::KEYWORD)) {
        return tokens;
    }
    
    // helper parsing functions
    auto detect_token = [&](std::vector<GrinTokenKind> kinds) {
        if (index < tokens.size()) {
            for (auto k: kinds) {
                if (tokens[index].kind().kind == k.kind) {
                    return true;
                }
            }
        }
        return false;
    };

    auto expect = [&](std::vector<GrinTokenKind> kinds){
        if (!detect_token(kinds)) {
            std::string msg = "";
            int i = 0;
            for ( ; i < kinds.size() - 1; ++i) {
                msg.append(token_kind_text[static_cast<int>(kinds[i].kind)]);
                msg.append(", ");
            }
            msg.append(token_kind_text[static_cast<int>(kinds[i].kind)]);

            if (index >= tokens.size()) {
                raise_error(msg, GrinLocation(line_number, index));
            }
            else {
                raise_error(msg, tokens[index].location());
            }

        };
    };

    auto parse_label = [&](){
        if (detect_token(std::vector<GrinTokenKind>{GrinTokenKind(GrinTokenKindName::IDENTIFIER, GrinTokenCategory::IDENTIFIER)})) {
            ++index;
            expect(std::vector<GrinTokenKind>{GrinTokenKind(GrinTokenKindName::COLON, GrinTokenCategory::PUNCTUATION)});
            ++index;
        };
    };

    auto parse_value = [&](){
        expect(std::vector<GrinTokenKind>{
            GrinTokenKind(GrinTokenKindName::LITERAL_INTEGER, GrinTokenCategory::LITERAL_VALUE),
            GrinTokenKind(GrinTokenKindName::LITERAL_DOUBLE, GrinTokenCategory::LITERAL_VALUE),
            GrinTokenKind(GrinTokenKindName::LITERAL_STRING, GrinTokenCategory::LITERAL_VALUE),
            GrinTokenKind(GrinTokenKindName::IDENTIFIER, GrinTokenCategory::IDENTIFIER)
        });
        ++index;
    };

    auto parse_varirable = [&](){
        expect(std::vector<GrinTokenKind>{GrinTokenKind(GrinTokenKindName::IDENTIFIER, GrinTokenCategory::IDENTIFIER)});
        ++index;
        parse_value();
    };
    
    auto parse_print = [&](){
        parse_value();
    };

    auto parse_input = [&](){
        expect(std::vector<GrinTokenKind>{GrinTokenKind(GrinTokenKindName::IDENTIFIER, GrinTokenCategory::IDENTIFIER)});
        ++index;
    };

    auto parse_target = [&](){
        expect(std::vector<GrinTokenKind>{GrinTokenKind(GrinTokenKindName::LITERAL_INTEGER, GrinTokenCategory::LITERAL_VALUE),
                                    GrinTokenKind(GrinTokenKindName::LITERAL_STRING, GrinTokenCategory::LITERAL_VALUE),
                                    GrinTokenKind(GrinTokenKindName::IDENTIFIER, GrinTokenCategory::IDENTIFIER)});
        ++index;
    };
    
    auto parse_comparison = [&](){
        expect(std::vector<GrinTokenKind>{GrinTokenKind(GrinTokenKindName::EQUAL, GrinTokenCategory::COMPARISON_OPERATOR),
                                          GrinTokenKind(GrinTokenKindName::LESS_THAN, GrinTokenCategory::COMPARISON_OPERATOR),
                                          GrinTokenKind(GrinTokenKindName::LESS_THAN_OR_EQUAL, GrinTokenCategory::COMPARISON_OPERATOR),
                                          GrinTokenKind(GrinTokenKindName::GREATER_THAN, GrinTokenCategory::COMPARISON_OPERATOR),
                                          GrinTokenKind(GrinTokenKindName::GREATER_THAN_OR_EQUAL, GrinTokenCategory::COMPARISON_OPERATOR),
                                          GrinTokenKind(GrinTokenKindName::NOT_EQUAL, GrinTokenCategory::COMPARISON_OPERATOR)});
        ++index;
    };

    auto parse_go = [&](){
        parse_target();
        if (detect_token(std::vector<GrinTokenKind>{GrinTokenKind(GrinTokenKindName::IF, GrinTokenCategory::KEYWORD)})) {
            ++index;
            parse_value();
            parse_comparison();
            parse_value();
        }
    };

    auto parse_empty = [](){};

    auto parse_body = [&](){
        auto t_kind = tokens[index].kind().kind;
        if (t_kind == GrinTokenKindName::LET) {
            ++index;
            parse_varirable();
        }
        else if (t_kind == GrinTokenKindName::PRINT) {
            ++index;
            parse_print();
        }
        else if (t_kind == GrinTokenKindName::INNUM || t_kind == GrinTokenKindName::INSTR) {
            ++index;
            parse_input();
        }
        else if (t_kind == GrinTokenKindName::ADD || t_kind == GrinTokenKindName::SUB 
                 || t_kind == GrinTokenKindName::MULT || t_kind == GrinTokenKindName::DIV) {
            ++index;
            parse_varirable();
        }
        else if (t_kind == GrinTokenKindName::GOTO || t_kind == GrinTokenKindName::GOSUB) {
            ++index;
            parse_go();
        }
        else if (t_kind == GrinTokenKindName::RETURN || t_kind == GrinTokenKindName::END || t_kind == GrinTokenKindName::DOT) {
            ++index;
            parse_empty();
        }
        else {
            raise_error("Statement keyword expected", tokens[index]);
        }
    };
    parse_label();
    
    if (index >= tokens.size()) {
        raise_error("Statement body expected", GrinLocation(line_number, line.size()));
    }

    parse_body();

    if (index < tokens.size()) {
        raise_error("Extra tokens after statement end", tokens[index]);
    }

    return tokens;

}

// public method that will be usable
std::vector<std::vector<GrinToken>> parse(const std::vector<std::string> & lines) {
    std::vector<std::vector<GrinToken>> parsed_tokens;

    for(int i = 0; i < lines.size(); ++i) {

        auto tokens = parse_line(lines[i], i+1);  
        
        if (tokens.size() == 1 && tokens[0].kind().kind == GrinTokenKindName::DOT) {
            break;
        }

        parsed_tokens.push_back(tokens);

    }
    return parsed_tokens;
}