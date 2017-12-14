#include "gtest/gtest.h"
#include "lexer.h"
#include "assert_range.h"
#include <iostream>
#include <string>

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

/*
TEST_F(LexerTest, should_tokenize_complex_expressions) {
	Tokens tokens = Lexer::Tokenize(L"1+2*3/(4-5)");

	for (size_t i = 0; i < tokens.size(); i++) {
		//std::wstring token_string = ToString(tokens[i].Type());
		//std::wcout << token_string << std::endl;
		Token t = tokens[i];
		switch (t.Type()) {
		case TokenType::Operator:
			std::cout << "operator" << std::endl;
			break;
		case TokenType::Number:
			std::cout << "number" << std::endl;
			break;
		default:
			std::cout << "unknown type" << std::endl;
		}
	}

	AssertRange::AreEqual({
			Token(1.),
			Token(Operator::Plus),
			Token(2.),
			Token(Operator::Mul),
			Token(3.),
			Token(Operator::Div),
			Token(Operator::LParen),
			Token(4.),
			Token(Operator::Minus),
			Token(5.),
			Token(Operator::LParen)}, tokens);
}
*/
