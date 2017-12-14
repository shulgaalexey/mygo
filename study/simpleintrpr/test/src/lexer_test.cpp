#include "gtest/gtest.h"
#include "lexer.h"
#include "assert_range.h"

using namespace Interpreter;

class LexerTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TeadDown() {
		}
};

TEST_F(LexerTest, should_return_empty_token_list_when_put_empty_expression) {
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
}

TEST_F(LexerTest, should_tokenize_floating_point_number) {
	Tokens tokens = Lexer::Tokenize(L"12.34");
	AssertRange::AreEqual({ 12.34 }, tokens);
}

TEST_F(LexerTest, should_tokenize_plus_and_number) {
	Tokens tokens = Lexer::Tokenize(L"+12.34");
	AssertRange::AreEqual({ Token(Operator::Plus), Token(12.34) }, tokens);
}

TEST_F(LexerTest, shlould_skip_spaces) {
	Tokens tokens = Lexer::Tokenize(L" 1 + 12.34  ");
	AssertRange::AreEqual(
			{ Token(1.0), Token(Operator::Plus), Token(12.34) },
			tokens);
}
