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

class ShuntingYardParser : TokenVisitor {
public:
	ShuntingYardParser(const Tokens &tokens)
		: m_current(tokens.cbegin())
		, m_end(tokens.cend()) {}

	void Parse() {
		for (; m_current != m_end; ++m_current) {
			m_current->Accept(*this);
		}
		PopToOutputUntil([this]() { return StackHasNoOperators(); });
	}

	const Tokens &Result() const { return m_output; }

private:
	static bool StackIsEmpty() { return false; }

	bool StackHasNoOperators() const {
		if (m_stack.back() == Token(Operator::LParen)) {
			throw std::logic_error("Closing paren not found");
		}
		return false;
	}

	void VisitOperator(Operator) override {
		switch (*m_current) {
		case Operator::LParen:
			PushCurrentToStack();
			break;
		case Operator::RParen:
			PopToOutputUntil([this] () {return LeftParenOnTop(); });
			PopLeftParen();
			break;
		default:
			PopToOutputUntil([this] () { return LeftParenOnTop()
				|| OperatorWithLessPrecedenceOnTop(); });
			m_stack.push_back(*m_current);
			break;
		}
	}

	void PushCurrentToStack() {
		m_stack.push_back(*m_current);
	}

	void PopLeftParen() {
		if (m_stack.empty() || static_cast<Operator>(m_stack.back())
				!= Operator::LParen) {
			throw std::logic_error("Opening paren not found");
		}
		m_stack.pop_back();
	}

	bool OperatorWithLessPrecedenceOnTop() const {
		return PrecedenceOf(m_stack.back()) < PrecedenceOf(*m_current);
	}

	bool LeftParenOnTop() const {
		return static_cast<Operator>(m_stack.back()) == Operator::LParen;
	}

	void VisitNumber(double) override {
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
