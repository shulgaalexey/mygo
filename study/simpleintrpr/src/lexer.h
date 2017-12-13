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

struct Token {};

typedef std::vector<Token> Tokens;

namespace Lexer {

inline Tokens Tokenize(const std::string &expr) {
	Tokens tokens;
	return tokens;
}

}; // namespace Lexer

}; // namespace Interpreter

#endif /*__LEXER_H_INCLUDED__*/
