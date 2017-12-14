#ifndef __LEXER_H_INCLUDED__
#define __LEXER_H_INCLUDED__

#include <string>
#include <vector>

/*
class Lexer {
	public:
		static std::vector<std::string> Tokenize(const std::string &str);
};
*/

namespace Interpreter {

//struct Token {};
enum class Operator : wchar_t {
	Plus = L'+',
};
typedef Operator Token;

inline std::wstring ToString(const Token &token) {
	return{ static_cast<wchar_t>(token) };
}


typedef std::vector<Token> Tokens;

namespace Lexer {

/**
 * @brief Splits expression on tokens
 *
 * @details Tokenizer satisfies following requirements and assumptions:
 * - when expr is empty string, returns empty token list
 * - when expr is a string with operator, returns token with operator
 * - when expr is a digit, returns token with a number
 * - when expr is a floating point number, returns token with this number
 * - when expr is simple expression, returns a list of corresponding tokens
 * - whitespaces between numbers and operators are ignored
 *
 * @remarks no remarks so far
 *
 * @param[in] expr expression which sould be tokenized
 * @return the list of tokens, extracted from the input expression
 *
 * @pre no preconditions
 *
 * @see other methods of the interpreter
 */
inline Tokens Tokenize(std::wstring expr) {
	//Tokens tokens;
	//return tokens;
	if (expr.empty())
		return {};

	return{ static_cast<Operator>(expr[0]) };
}

}; // namespace Lexer

}; // namespace Interpreter

#endif /*__LEXER_H_INCLUDED__*/
