#ifndef __LEXER_H_INCLUDED__
#define __LEXER_H_INCLUDED__

#include <string>
#include <vector>
#include <stdexcept>
#include <cwctype>
#include <cwchar>
#include <algorithm>
#include <memory>

namespace Interpreter {


enum class Operator : wchar_t {
	Plus = L'+',
	Minus = L'-',
	Mul = L'*',
	Div = L'/',
	LParen = L'(',
	RParen = L')'
};

inline std::wstring ToString(const Operator &op) {
	return{ static_cast<wchar_t>(op) };
}


enum class TokenType {
	Operator,
	Number
};

struct TokenVisitor {
	virtual void VisitNumber(double) {}
	virtual void VisitOperator(Operator) {}
protected:
	~TokenVisitor() {}
};

class Token {

	struct TokenConcept {
		virtual ~TokenConcept() {}
		virtual void Accept(TokenVisitor &) const = 0;
		virtual std::wstring ToString() const = 0;
		virtual bool Equals(const TokenConcept &) const = 0;
		virtual TokenType Type() const = 0;
		virtual double ToNumber() const {
			throw std::logic_error("Invalid token type");
		}
		virtual Operator ToOperator() const {
			throw std::logic_error("Invalid token type");
		}
	};

	struct NumberToken : TokenConcept {
		NumberToken(double val) : m_number(val) {}
		void Accept(TokenVisitor &visitor) const override {
			visitor.VisitNumber(m_number);
		}
		std::wstring ToString() const override {
			return std::to_wstring(m_number);
		}
		bool Equals(const TokenConcept &other) const override {
			return other.Type() == Type()
				&& other.ToNumber() == m_number;
		}
		TokenType Type() const override {
			return TokenType::Number;
		}
		double ToNumber() const override { return m_number; }
	private:
		double m_number;
	};

	struct OperatorToken : TokenConcept {
		OperatorToken(Operator val) : m_operator(val) {}
		void Accept(TokenVisitor &visitor) const override {
			visitor.VisitOperator(m_operator);
		}
		std::wstring ToString() const override {
			return Interpreter::ToString(m_operator);
		}
		bool Equals(const TokenConcept &other) const override {
			return other.Type() == Type()
				&& other.ToOperator() == m_operator;
		}
		TokenType Type() const override {
			return TokenType::Operator;
		}
		Operator ToOperator() const override { return m_operator; }
	private:
		Operator m_operator;
	};

public:
	Token(Operator op) : m_concept(std::make_shared<OperatorToken>(op)) {}
	Token(double num) : m_concept(std::make_shared<NumberToken>(num)) {}
	TokenType Type() const { return m_concept->Type(); }

	void Accept(TokenVisitor &visitor) const {
		m_concept->Accept(visitor);
	}

	operator Operator() const {
		return m_concept->ToOperator();
	}

	operator double() const {
		return m_concept->ToNumber();
	}

	/*friend inline bool operator == (const Token &left, const Token &right) {
		return left.m_concept->Equals(*right.m_concept);
	}*/

	/*friend inline bool operator != (const Token &left, const Token &right) {
		return !(left == right);
	}*/

	bool operator == (const Token &ref) const {
		return m_concept->Equals(*ref.m_concept);
	}

	bool operator != (const Token &ref) const {
		return !(*this == ref);
	}

	friend inline std::wstring ToString(const Token &token) {
		return token.m_concept->ToString();
	}

private:
	std::shared_ptr<const TokenConcept> m_concept;
};

static const Token plus(Operator::Plus);
static const Token minus(Operator::Minus);
static const Token mul(Operator::Mul);
static const Token div(Operator::Div);
static const Token pLeft(Operator::LParen);
static const Token pRight(Operator::RParen);
static const Token _1(1);
static const Token _2(2);
static const Token _3(3);
static const Token _4(4);
static const Token _5(5);


/*inline std::wstring ToString(const Token &token) {
	switch(token.Type()) {
	case TokenType::Number:
		return std::to_wstring(static_cast<double>(token));
	case TokenType::Operator:
		return ToString(static_cast<Operator>(token));
	default:
		throw std::out_of_range("TokenType");
	}
}*/

inline std::wstring ToString(const TokenType &type) {
	switch(type) {
	case TokenType::Operator:
		return L"Operator";
	case TokenType::Number:
		return L"Number";
	default:
		throw std::out_of_range("TokenType");
	}
}


typedef std::vector<Token> Tokens;


namespace Detail {

class Tokenizer {
	public:
		Tokenizer(const std::wstring &expr) : m_current(expr.c_str()) {}

		void Tokenize() {
			while (!EndOfExpression()) {
				if (IsNumber()) {
					ScanNumber();
				} else if (IsOperator()) {
					ScanOperator();
				} else {
					MoveNext();
				}
			}
		}

		const Tokens &Result() const { return m_result; }

	private:
		bool EndOfExpression() const { return *m_current == L'\0'; }

		bool IsNumber() const {return iswdigit(*m_current) != 0; }

		void ScanNumber() {
			wchar_t *end = nullptr;
			m_result.push_back(wcstod(m_current, &end));
			m_current = end;
		}

		bool IsOperator() const {
			auto all = {
				Operator::Plus,
				Operator::Minus,
				Operator::Mul,
				Operator::Div,
				Operator::LParen,
				Operator::RParen
			};

			return std::any_of(
				all.begin(), all.end(), [this](Operator o) {
					return *m_current == static_cast<wchar_t>(o);
				});

		}

		void ScanOperator() {
			m_result.push_back(static_cast<Operator>(*m_current));
			MoveNext();
		}

		void MoveNext() { ++m_current; }

	private:
		const wchar_t *m_current;
		Tokens m_result;
};

} // namespace Detail


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
	Detail::Tokenizer tokenizer(expr);
	tokenizer.Tokenize();
	return tokenizer.Result();
}

}; // namespace Lexer

}; // namespace Interpreter

#endif /*__LEXER_H_INCLUDED__*/
