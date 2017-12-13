#include <limits.h>
#include "gtest/gtest.h"
#include "lexer.h"
#include <string>
#include <vector>

using namespace Interpreter;

class LexerTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TeadDown() {
		}
};

TEST_F(LexerTest, should_return_empty_token_list_when_put_empty_expression) {
	Tokens tokens = Lexer::Tokenize("");
	EXPECT_EQ(tokens.size(), 0);
}

