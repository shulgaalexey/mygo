#include <limits.h>
#include "gtest/gtest.h"
#include "lexer.h"
#include "assert_range.h"
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

/*TEST_F(LexerTest, should_return_empty_token_list_when_put_empty_expression) {
	Tokens tokens = Lexer::Tokenize(L"");
	EXPECT_EQ(tokens.size(), 0);
}

TEST_F(LexerTest, should_tokenize_single_plus_operator) {
	Tokens tokens = Lexer::Tokenize(L"+");
	AssertRange::AreEqual({ Operator::Plus }, tokens);
}

TEST_F(LexerTest, shoud_tokenize_single_digit) {
	Tokens tokens = Lexer::Tokenize(L"1");
	AssertRange::AreEqual({ 1.0 }, tokens);
}*/
