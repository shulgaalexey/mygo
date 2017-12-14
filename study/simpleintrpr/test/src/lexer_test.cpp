#include <limits.h>
#include "gtest/gtest.h"
#include "lexer.h"
#include <string>
#include <vector>
#include <iostream>

using namespace Interpreter;
using namespace std;


namespace AssertRange {

template<class T, class ActualRange>
static void AreEqual(initializer_list<T> expect, const ActualRange &actual) {
	auto actualIter = begin(actual);
	auto expectIter = begin(expect);


	auto expectDist = distance(expectIter, end(expect));
	auto actualDist = distance(actualIter, end(actual));

	if (expectDist != actualDist)
		cerr << L"Size differs." << endl;
	EXPECT_EQ(expectDist, actualDist);

	for (; expectIter != end(expect) && actualIter != end(actual);
			++expectIter, ++actualIter) {
		auto message = L"Mismatch in position " +
			to_wstring(distance(begin(expect), expectIter));
		if (*expectIter != *actualIter)
			cerr << message.c_str() << endl;

		EXPECT_EQ(*expectIter, *actualIter);
	}
}

} // namespace AssertRange


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
