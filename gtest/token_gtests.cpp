#include <gtest/gtest.h>

#include "token.hpp"

TEST(TokenTests, MakeToken) {
    GrinToken token(GrinTokenKind(GrinTokenKindName::ADD, GrinTokenCategory::KEYWORD), "ADD", "ADD", GrinLocation(1, 1));
    std::variant<int, double, std::string> add{"ADD"};
    ASSERT_EQ(token.text(), "ADD");
    ASSERT_EQ(token.value(), add);
    ASSERT_EQ(token.kind(), GrinTokenKind(GrinTokenKindName::ADD, GrinTokenCategory::KEYWORD));
    ASSERT_EQ(token.location(), GrinLocation(1, 1));
}

TEST(TokenTests, TokenKind) {
    GrinTokenKind kind{GrinTokenKindName::DIV, GrinTokenCategory::KEYWORD};
    ASSERT_EQ(kind.category, GrinTokenCategory::KEYWORD);
    ASSERT_EQ(kind.kind, GrinTokenKindName::DIV);
    ASSERT_EQ(int(kind.category), 3);
}

TEST(TokenTests, PopulateMap) {
    populate_token_kind_map();
    ASSERT_EQ(TOKEN_MAP.size(), 13);
}

TEST(TokenTests, MapLookup) {
    populate_token_kind_map();
    ASSERT_EQ(TOKEN_MAP["ADD"].first, GrinTokenKindName::ADD);
    ASSERT_EQ(TOKEN_MAP[std::string("ADD")].first, GrinTokenKindName::ADD);
}