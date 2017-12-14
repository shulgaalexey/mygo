#ifndef __PARSER_H_INCLUDED__
#define __PARSER_H_INCLUDED__

#include "lexer.h"

using namespace Interpreter;

namespace Parser {


inline Tokens Parse(const Tokens &tokens) {
	Tokens output;
	Tokens stack;

	for (const Token &token : tokens) {
		if (token.Type() == TokenType::Number) {
			output.push_back(token);
		} else {
			stack.push_back(token);
		}
	}
	std::copy(stack.crbegin(), stack.crend(), std::back_inserter(output));

	return output;
}

} // namespace Parser

#endif /*__PARSER_H_INCLUDED__*/
