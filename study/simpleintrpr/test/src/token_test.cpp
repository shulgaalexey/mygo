#include "gtest/gtest.h"
#include "lexer.h"

using namespace Interpreter;

class TokenTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TeadDown() {
		}
};

TEST_F(TokenTest, should_check_for_equality_operator_tokens) {
	EXPECT_EQ(minus, minus);
	EXPECT_NE(minus, plus);
	EXPECT_NE(minus, _1);
}

TEST_F(TokenTest, should_check_for_equality_number_tokens) {
	EXPECT_EQ(_1, _1);
	EXPECT_NE(_1, _2);
	EXPECT_NE(_1, minus);
}

TEST_F(TokenTest, should_get_operator_code_from_operator_token) {
	Token token(Operator::Plus);
	EXPECT_EQ(Operator::Plus, token);
}

TEST_F(TokenTest, should_get_number_value_from_number_token) {
	Token token(1.23);
	EXPECT_EQ(1.23, token);
}
