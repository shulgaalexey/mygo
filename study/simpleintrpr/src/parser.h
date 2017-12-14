#ifndef __PARSER_H_INCLUDED__
#define __PARSER_H_INCLUDED__

#include "lexer.h"

using namespace Interpreter;

namespace Parser {


inline Tokens Parse(const Tokens &tokens) {
	Tokens output;
	Tokens stack;

	auto popAll = [&]() {
		while (!stack.empty()) {
			output.push_back(stack.back());
			stack.pop_back();
		}
	};

	for (const Token &token : tokens) {
		if (token.Type() == TokenType::Operator) {
			popAll();
			stack.push_back(token);
			continue;
		}
		output.push_back(token);
	}

	popAll();

	return output;
}

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


} // namespace Parser

#endif /*__PARSER_H_INCLUDED__*/
