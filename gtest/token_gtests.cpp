#include <gtest/gtest.h>

#include "token.hpp"

TEST(TokenTests, MakeToken) {
    Token token(TokenKind(TokenKindName::ADD, TokenCategory::KEYWORD), "ADD", "ADD", Location(1, 1));
    std::variant<int, double, std::string> add{"ADD"};
    ASSERT_EQ(token.text(), "ADD");
    ASSERT_EQ(token.value(), add);
    ASSERT_EQ(token.kind(), TokenKind(TokenKindName::ADD, TokenCategory::KEYWORD));
    ASSERT_EQ(token.location(), Location(1, 1));
}

TEST(TokenTests, TokenKind) {
    TokenKind kind{TokenKindName::DIV, TokenCategory::KEYWORD};
    ASSERT_EQ(kind.category, TokenCategory::KEYWORD);
    ASSERT_EQ(kind.kind, TokenKindName::DIV);
    ASSERT_EQ(int(kind.category), 3);
}

TEST(TokenTests, PopulateMap) {
    populate_token_kind_map();
    ASSERT_EQ(TOKEN_MAP.size(), 13);
}

TEST(TokenTests, MapLookup) {
    populate_token_kind_map();
    ASSERT_EQ(TOKEN_MAP["ADD"].first, TokenKindName::ADD);
    ASSERT_EQ(TOKEN_MAP[std::string("ADD")].first, TokenKindName::ADD);
}

TEST(TokenTests, ToString) {
    const char* add = token_kind_text[static_cast<int>(TokenKindName::ADD) - 1];
    ASSERT_STREQ("ADD", add);
}