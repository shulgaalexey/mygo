#include <limits.h>
#include "gtest/gtest.h"
#include "lexer.h"
#include <string>
#include <vector>

class LexerTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TeadDown() {
		}
};

TEST_F(LexerTest, Tokenize) {
	std::vector<std::string> res = Lexer::Tokenize("");
	EXPECT_EQ(res.size(), 0);
}

