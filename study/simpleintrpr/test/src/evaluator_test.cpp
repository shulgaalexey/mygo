#include "gtest/gtest.h"
#include "evaluator.h"
#include "assert_range.h"
#include <iostream>
#include <string>

using namespace Evaluator;

class EvaluatorTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TeadDown() {
		}
};

// Pass empty list, return 0
TEST_F(EvaluatorTest, should_return_zero_when_evaluate_empty_list) {
	double result = Evaluator::Evaluate({});
	EXPECT_EQ(0., result);
}

// Pass list with single number, return that number
TEST_F(EvaluatorTest, shoudl_return_number_when_evaluate_list_with_number) {
	double result = Evaluator::Evaluate({ _1 });
	EXPECT_EQ(1., result);
}

// Pass [1 2 +], return 3
TEST_F(EvaluatorTest, should_eval_expression_with_one_operator) {
	double result = Evaluator::Evaluate({ _1, _2, plus });
	EXPECT_EQ(3., result);
}

// Pass [1 2 *], return 2
TEST_F(EvaluatorTest, should_eval_expression_with_one_multiplication) {
	double result = Evaluator::Evaluate({ _1, _2, mul });
	EXPECT_EQ(2., result);
}

// Pass [2 3 -], return -1
TEST_F(EvaluatorTest, should_evaluate_with_one_subtraction) {
	double result = Evaluator::Evaluate({ _2, _3, minus });
	EXPECT_EQ( -1., result);
}

// Pass [5 2 /], return 2.5
TEST_F(EvaluatorTest, should_evaluate_with_one_division) {
	double result = Evaluator::Evaluate({ _5, _2, Interpreter::div });
	EXPECT_EQ(2.5, result);
}

// (4 + 1) * 2 / (4 / (3 - 1)) = 4 1 + 2 * 4 3 1 - / / = 5
TEST_F(EvaluatorTest, should_eval_complex_expression) {
	double result = Evaluator::Evaluate({
		_4, _1, plus, _2, mul, _4, _3, _1, minus,
		Interpreter::div, Interpreter::div });
	EXPECT_EQ( 5., result);
}
