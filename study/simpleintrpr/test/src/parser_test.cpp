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


// Receives [1 + 2 + 3], returns [1 2 + 3 +]

// Receives [1 * 2 + 3], returns [1 2 * 3 +]

// Receives [1 + 2 * 3], returns [1 2 3 * +]
