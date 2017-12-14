#ifndef __PARSER_H_INCLUDED__
#define __PARSER_H_INCLUDED__

#include "lexer.h"

using namespace Interpreter;

namespace Parser {

inline int PrecedenceOf(Operator op) {
	switch (op) {
	case Operator::Plus:
	case Operator::Minus:
		return 0;
	case Operator::Mul:
	case Operator::Div:
		return 1;
	default:
		throw std::logic_error("Unsupported type of operator at Parser::PrecedenceOf");
	}
}


inline Tokens Parse(const Tokens &tokens) {
	Tokens output;
	Tokens stack;

	auto popToOutput = [&output, &stack](auto whenToEnd) {
		while (!stack.empty() && !whenToEnd(stack.back())) {
			output.push_back(stack.back());
			stack.pop_back();
		}
	};

	for (const Token &current : tokens) {
		if (current.Type() == TokenType::Operator) {
			popToOutput([&] (Operator top) {
				return PrecedenceOf(top) < PrecedenceOf(current);
			});
			stack.push_back(current);
			continue;
		}
		output.push_back(current);
	}

	popToOutput([] (auto) { return false; });

	return output;
}


} // namespace Parser

#endif /*__PARSER_H_INCLUDED__*/
