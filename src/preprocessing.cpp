#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "preprocessing.hpp"

std::vector<std::string> read_input(std::istream & in) {
    std::vector<std::string> lines;
    std::string line;
    while(std::getline(in, line)) {
        lines.push_back(line);
        std::erase_if(line, [](char c){ return isspace(c); });
        if ("." == line) {
            lines.pop_back();
            lines.push_back(".");
            break;
        }
    }
    return lines;
}

std::map<std::string, int> map_labels(std::vector<std::vector<GrinToken>> tokens) {
    std::map<std::string, int> labels{};
    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens[i].size() > 2 
            && tokens[i][0].kind().kind == GrinTokenKindName::IDENTIFIER
            && tokens[i][1].kind().kind == GrinTokenKindName::COLON) {
            labels.insert(std::pair{tokens[i][0].text(), i});
        }
    }
    return labels;
}