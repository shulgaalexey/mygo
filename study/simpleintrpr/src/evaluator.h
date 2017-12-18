#ifndef __EVALUATOR_H_INCLUDED__
#define __EVALUATOR_H_INCLUDED__

#include "parser.h"
#include <functional>

namespace Evaluator {

namespace Detail {

class StackEvaluator : TokenVisitor {
public:
	void Evaluate(const Tokens &tokens) {
		for (const Token &token : tokens) {
			token.Accept(*this);
		}
	}

	double Result() const { return m_stack.empty() ? 0 : m_stack.back(); }

private:

	void VisitOperator(Operator op) override {
		double second = PopOperand();
		double first = PopOperand();
		m_stack.push_back(BinaryFunctionFor(op)(first, second));
	}

	void VisitNumber(double number) override {
		m_stack.push_back(number);
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
	std::vector<double> m_stack;
};




} // namespace Detail

inline double Evaluate(const Tokens &tokens) {
	Detail::StackEvaluator evaluator;
	evaluator.Evaluate(tokens);
	return evaluator.Result();
}


} // namespace Evaluator



namespace Interpreter {

inline double InterpreteExpression(const std::wstring &expression) {
	return Evaluator::Evaluate(Parser::Parse(Lexer::Tokenize(expression)));
}

} // namespace Interpreter

#endif/*__EVALUATOR_H_INCLUDED__*/
