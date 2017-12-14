#include <limits.h>
#include "gtest/gtest.h"
#include "lexer.h"
#include "assert_range.h"

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
