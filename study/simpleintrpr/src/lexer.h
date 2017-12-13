#ifndef __LEXER_H_INCLUDED__
#define __LEXER_H_INCLUDED__

#include <string>
#include <vector>


class Lexer {
	public:
		static std::vector<std::string> Tokenize(const std::string &str);
};

#endif /*__LEXER_H_INCLUDED__*/
