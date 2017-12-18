#ifndef __EVALUATOR_H_INCLUDED__
#define __EVALUATOR_H_INCLUDED__

#include "parser.h"
#include <functional>

namespace Evaluator {

namespace Detail {

class StackEvaluator {
public:
	StackEvaluator(const Tokens &tokens)
		: m_current(tokens.cbegin())
		, m_end(tokens.cend()) {}

	void Evaluate() {
		for (; m_current != m_end; ++m_current) {
			EvaluateCurrentToken();
		}
	}

	double Result() const { return m_stack.empty() ? 0 : m_stack.back(); }

private:
	void EvaluateCurrentToken() {
		switch (m_current->Type()) {
		case TokenType::Operator:
			EvaluateOperator();
			break;
		case TokenType::Number:
			EvaluateNumber();
			break;
		default:
			throw std::out_of_range("TokenType");
		}
	}

	void EvaluateOperator() {
		double second = PopOperand();
		double first = PopOperand();
		m_stack.push_back(BinaryFunctionFor(*m_current)(first, second));
	}

	void EvaluateNumber() {
		m_stack.push_back(*m_current);
	}

	double PopOperand() {
		double back = m_stack.back();
		m_stack.pop_back();
		return back;
	}

	static const std::function<double(double, double)> &BinaryFunctionFor(
			Operator op) {
		static const std::map<Operator,
		     std::function<double(double, double)>> functions {
			     {Operator::Plus, std::plus<double>() },
			     {Operator::Minus, std::minus<double>() },
			     {Operator::Mul, std::multiplies<double>() },
			     {Operator::Div, std::divides<double>() }
		     };

		auto found = functions.find(op);
		if (found == functions.cend()) {
			throw std::logic_error("Operator not found");
		}
		return found->second;
	}

private:
	Tokens::const_iterator m_current;
	Tokens::const_iterator m_end;
	std::vector<double> m_stack;
};




} // namespace Detail

inline double Evaluate(const Tokens &tokens) {
	Detail::StackEvaluator evaluator(tokens);
	evaluator.Evaluate();
	return evaluator.Result();
}


} // namespace Evaluator



namespace Interpreter {

inline double InterpreteExpression(const std::wstring &expression) {
	return Evaluator::Evaluate(Parser::Parse(Lexer::Tokenize(expression)));
}

} // namespace Interpreter

#endif/*__EVALUATOR_H_INCLUDED__*/
