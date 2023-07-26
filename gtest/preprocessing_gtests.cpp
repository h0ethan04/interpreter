#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <sstream>
#include <utility>

#include "preprocessing.hpp"
#include "parsing.hpp"

TEST(InputTests, ReadingIstreams) {
    std::stringstream stream("HELLO WORLD\n     MY NAME IS ETHAN     \n             .       ");
    std::vector<std::string> output{"HELLO WORLD", "     MY NAME IS ETHAN     ", "."};
    ASSERT_EQ(read_input(stream), output);
}

TEST(LabelTests, LabelsMappedToLines) {
    std::vector<std::string> lines{"LABEL: PRINT 0", "LET X 0", "ALSOALABEL: INSTR X", "."};
    
    std::vector<std::vector<GrinToken>> tokenized{parse(lines)};
    std::map<std::string, int> output(map_labels(tokenized));

    std::pair<std::string, int> line_zero{"LABEL", 0};
    std::pair<std::string, int> line_two{"ALSOALABEL", 2};
    std::map<std::string, int> mapped_labels;
    mapped_labels.insert(line_zero);
    mapped_labels.insert(line_two);

    ASSERT_EQ(mapped_labels, output);

}