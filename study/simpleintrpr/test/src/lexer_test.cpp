#include <limits.h>
#include "gtest/gtest.h"
#include "lexer.h"

class LexerTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TeadDown() {
		}
};

TEST_F(LexerTest, Tokenize) {
	Lexer lexer;
	int res = lexer.Tokenize(13);
	EXPECT_EQ(res, 42);
}

