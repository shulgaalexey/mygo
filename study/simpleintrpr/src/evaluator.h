#ifndef __EVALUATOR_H_INCLUDED__
#define __EVALUATOR_H_INCLUDED__

#include "parser.h"

namespace Evaluator {

inline double Evaluate(const Tokens &tokens) {
	std::vector<double> result{ 0. };

	auto pop = [&] () {
		double d = result.back();
		result.pop_back();
		return d;
	};

	for (const Token &token : tokens) {
		if (token.Type() == TokenType::Number) {
			result.push_back(token);
		} else if (token == Token(Operator::Plus)) {
			result.push_back(pop() + pop());
		} else if (token == Token(Operator::Minus)) {
			double d = pop();
			result.push_back(pop() - d);
		} else if (token == Token(Operator::Mul)) {
			result.push_back(pop() * pop());
		} else if (token == Token(Operator::Div)) {
			double d = pop();
			result.push_back(pop() / d);
		}
	}
	return pop();
}

} // namespace Evaluator

#endif/*__EVALUATOR_H_INCLUDED__*/
