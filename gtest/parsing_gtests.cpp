#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "parsing.hpp"

void assertParsesLine(std::string line) {
    auto tokens = to_tokens(line, 1);
    auto parsed = parse(std::vector<std::string>{line});
    ASSERT_EQ(parsed.size(), 1);
    ASSERT_EQ(parsed[0], tokens);
}

void assertRaisesError(std::string line) {
    try {
        parse(std::vector<std::string>{line});
        FAIL();
    }
    catch(const ParsingError & error) {
        ASSERT_TRUE(true);
    }
}

TEST(ParsingTests, ParseEmptyFails) {
    assertRaisesError("");
    assertRaisesError("   ");
}

TEST(ParsingTests, ParseNonKeywordFirstFails) {
    assertRaisesError(" 4 < 5");
    assertRaisesError("\"Boo\"");
}

TEST(ParsingVariableTests, ParseVariableUpdate) {
    std::vector<std::string> keywords{"LET", "ADD", "SUB", "MULT", "DIV"};
    std::vector<std::string> body{"AGE 19", "NAME TARO", "RATTLE 75.0", "NAME UBE"};

    for (std::string kw: keywords){
        for(std::string op: body) {
            std::string kwop = kw + " " + op;
            assertParsesLine(kwop);
        }
    }
}

TEST(ParsingVariableTests, ParseExtraFails) {
    assertRaisesError("LET COLOR \"TARO\" 19");
}

TEST(ParsingVariableTests, ParseMissingTokensFails) {
    assertRaisesError("LET TARO");
    assertRaisesError("ADD");
}

TEST(ParsingVariableTests, ParseInvalidTargetFails) {
    assertRaisesError("LET \"TARO\" \"taro\"");
}

TEST(ParsingVariableTests, ParseInvalidSourceFails) {
    assertRaisesError("LET TARO <");
}

TEST(ParsingPrintTests, ParsePrint) {
    std::vector<std::string> print{"PRINT TARO", "PRINT 19", "PRINT 100.00", "PRINT \"taro\""};
    for(auto s: print) {
        assertParsesLine(s);
    }
}

TEST(ParsingPrintTests, ParseMissingFails) {
    assertRaisesError("PRINT TARO 19");
}

TEST(ParsingPrintTests, ParseExtraTokensFails) {
    assertRaisesError("PRINT");
}

TEST(ParsingPrintTests, ParseInvalidSourceFails) {
    assertRaisesError("PRINT IF");
}

TEST(ParsingInputTests, ParseInput) {
    std::vector<std::string> input{"INNUM TARO", "INSTR TARO"};
    for(auto s: input) {
        assertParsesLine(s);
    }
}

TEST(ParsingInputTests, ParseExtraTokensFails) {
    assertRaisesError("INNUM TARO TARO");
    assertRaisesError("INSTR TARO TARO");
}

TEST(ParsingInputTests, ParseMissingTokensFails) {
    assertRaisesError("INNUM");
    assertRaisesError("INSTR");
}

TEST(ParsingInputTests, ParseInvalidTargetFails) {
    assertRaisesError("INNUM 99.9");
    assertRaisesError("INSTR 99.9");
}

TEST(ParsingJumpTests, ParseJump) {
    std::vector<std::string> jump{"GOTO", "GOSUB"};
    std::vector<std::string> targets{"19", "\"TARO\"", "taro"};

    for(auto j: jump) {
        for(auto t: targets) {
            std::string jump_target = j + " " + t;
            assertParsesLine(jump_target);
        }
    }
}

TEST(ParsingJumpTests, ParseJumpWithCondition) {
    std::vector<std::string> jump{"GOTO", "GOSUB"};
    std::vector<std::string> targets{"19", "\"TARO\"", "taro"};
    std::vector<std::string> values{"19", "1.1", "\"TARO\"", "taro"};
    std::vector<std::string> ops{"=", "<>", "<", "<=", ">", ">="};
    std::string if_string{" IF "};

    for(auto j: jump) {
        for(auto t: targets) {
            for(auto v1: values) {
                for(auto v2: values){
                    for(auto op: ops) {
                        std::string statement = j + " " + t + if_string + v1 + " " + op + " " + v2;
                        assertParsesLine(statement);
                    }
                }
            }
        }
    }
}

TEST(ParsingJumpTests, ParseExtraTokensFails) {
    assertRaisesError("GOTO 19 IF taro < 19 19");
    assertRaisesError("GOSUB 19 taro");
}

TEST(ParsingJumpTests, ParseMissingTokensFails) {
    assertRaisesError("GOTO");
    assertRaisesError("GOTO 19 IF");
    assertRaisesError("GOTO 19 IF TARO");
    assertRaisesError("GOTO 19 IF TARO <>");
}

TEST(ParsingJumpTests, ParseInvalidTarget) {
    assertRaisesError("GOTO 3.5");
}

TEST(ParsingJumpTests, ParseInvalidLeftSource) {
    assertRaisesError("GOTO 3 IF LET < 10");
}

TEST(ParsingJumpTests, ParseInvalidRightSource) {
    assertRaisesError("GOTO 3 IF 10 < LET");
}

TEST(ParsingJumpTests, ParseInvalidOperator) {
    assertRaisesError("GOTO 3 IF 10 X 11");
}

TEST(ParsingSingleStatements, ParseReturnAndEnd) {
    assertParsesLine("END");
    assertParsesLine("RETURN");
}

TEST(ParsingDot, ParsingEnds) {
    std::vector<std::string> cutoff{"RETURN", ".", "RETURN"};
    std::vector<std::vector<Token>> parsed = parse(cutoff);
    ASSERT_EQ(parsed.size(), 1);
    ASSERT_EQ(parsed[0].size(), 1);
}

TEST(ParsingLabel, ParsingLabel) {
    std::vector<std::string> body{"LET TARO 19", "END", "PRINT \"TARO\""};
    for(auto b: body) {
        std::string statement = "LABEL: " + b;
        assertParsesLine(statement);
    }
}

TEST(ParsingLabel, ParsingWithoutBodyFails) {
    assertRaisesError("LABEL: ");
}