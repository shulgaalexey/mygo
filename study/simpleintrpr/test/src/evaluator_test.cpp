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
