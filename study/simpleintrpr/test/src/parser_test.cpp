#include "gtest/gtest.h"
#include "parser.h"
#include "assert_range.h"
#include <iostream>
#include <string>

using namespace Parser;

class ParserTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TeadDown() {
		}
};

// Receives empty list, returns epmty list
TEST_F(ParserTest, should_return_empty_list_when_put_empty_list) {
	Tokens tokens = Parser::Parse({});
	EXPECT_EQ(tokens.size(), 0);
}

// Receives list with a single number, returns list with this number
TEST_F(ParserTest, should_parse_single_number) {
	Tokens tokens = Parser::Parse({ Token(1) });
	AssertRange::AreEqual( {Token(1) }, tokens);
}

// Receives [1 + 2], returns [1 2 +]
TEST_F(ParserTest, should_parse_num_plus_num) {
	Tokens tokens = Parser::Parse({
			Token(1),
			Token(Operator::Plus),
		       	Token(2) });

	AssertRange::AreEqual( {
			Token(1),
			Token(2),
 			Token(Operator::Plus) }, tokens);
}

// Receives [1 + 2 + 3], returns [1 2 + 3 +]
TEST_F(ParserTest, should_parse_two_additions) {
	Tokens tokens = Parser::Parse({
			Token(1),
			Token(Operator::Plus),
		       	Token(2),
 			Token(Operator::Plus),
			Token(3) });

	AssertRange::AreEqual( {
			Token(1),
			Token(2),
 			Token(Operator::Plus),
 			Token(3),
			Token(Operator::Plus) }, tokens);
}

// Operators + and - should have similar priorities
// Operators * and / should have similar priorities
TEST_F(ParserTest, should_get_same_precenece_for_operator_pairs) {
	EXPECT_EQ(Parser::PrecedenceOf(Operator::Plus),
			Parser::PrecedenceOf(Operator::Minus));

	EXPECT_EQ(Parser::PrecedenceOf(Operator::Mul),
			Parser::PrecedenceOf(Operator::Div));
}

// Operators */ should have greater priority than +-
TEST_F(ParserTest, should_get_greater_precedence_for_mul_operator) {
	EXPECT_GT(Parser::PrecedenceOf(Operator::Mul),
			Parser::PrecedenceOf(Operator::Plus));
}

// Receives [1 * 2 + 3], returns [1 2 * 3 +]

// Receives [1 + 2 * 3], returns [1 2 3 * +]
