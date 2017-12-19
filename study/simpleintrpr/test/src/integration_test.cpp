#include "gtest/gtest.h"
#include "evaluator.h"
#include "assert_range.h"
#include <iostream>
#include <string>

using namespace Interpreter;

class IntegrationTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TeadDown() {
		}
};

// Should return 0. if passed empty expression
T_F(IntegrationTest, should_interpret_empty_expression) {
	double resutl = Interpreter::InterpreteExpression(L" ");
	EXPECT_EQ(0., result);
}

// 1 + 2 = 3
TEST_F(IntegrationTest, should_return_zero_when_evaluate_empty_list) {
	double result = Interpreter::InterpretExpression(L"1 + 2");
	EXPECT_EQ(3., result);
}
