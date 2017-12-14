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

TEST_F(TokenTest, should_get_type_for_operator_token) {
	Token opToken(Operator::Plus);
	EXPECT_EQ(TokenType::Operator, opToken.Type());
}

TEST_F(TokenTest, should_get_type_for_number_token) {
	Token numToken(1.2);
	EXPECT_EQ(TokenType::Number, numToken.Type());
}

TEST_F(TokenTest, should_get_operator_code_from_operator_token) {
	Token token(Operator::Plus);
	EXPECT_EQ(Operator::Plus, token);
}

TEST_F(TokenTest, should_get_number_value_from_number_token) {
	Token token(1.23);
	EXPECT_EQ(1.23, token);
}
