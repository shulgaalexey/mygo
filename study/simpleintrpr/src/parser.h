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


namespace Detail {

class ShuntingYardParser {
	public:
		ShuntingYardParser(const Tokens &tokens)
			: m_current(tokens.cbegin())
			, m_end(tokens.cend()) {}

		void Parse() {
			for (; m_current != m_end; ++m_current) {
				ParseCurrentToken();
			}
			PopToOutputUntil(StackIsEmpty);
		}

		const Tokens &Result() const { return m_output; }

	private:
		static bool StackIsEmpty() { return false; }

		void ParseCurrentToken() {
			switch (m_current->Type()) {
			case TokenType::Operator:
				ParseOperator();
				break;
			case TokenType::Number:
				ParseNumber();
				break;
			default:
				throw std::out_of_range("TokenType");
			}
		}

		void ParseOperator() {
			PopToOutputUntil([this] () {
				return PrecedenceOf(m_stack.back())
					< PrecedenceOf(*m_current); });
			m_stack.push_back(*m_current);
		}

		void ParseNumber() {
			m_output.push_back(*m_current);
		}

		template<class T>
		void PopToOutputUntil(T whenToEnd) {
			while (!m_stack.empty() && !whenToEnd()) {
				m_output.push_back(m_stack.back());
				m_stack.pop_back();
			}
		}

	private:
		Tokens::const_iterator m_current;
		Tokens::const_iterator m_end;
		Tokens m_output;
		Tokens m_stack;
};

} // namespace Detail


inline Tokens Parse(const Tokens &tokens) {
	Detail::ShuntingYardParser parser(tokens);
	parser.Parse();
	return parser.Result();
}


} // namespace Parser

#endif /*__PARSER_H_INCLUDED__*/
