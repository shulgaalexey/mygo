#ifndef __LEXER_H_INCLUDED__
#define __LEXER_H_INCLUDED__

#include <string>
#include <vector>
#include <stdexcept>
#include <cwctype>
#include <cwchar>
#include <algorithm>

namespace Interpreter {


enum class Operator : wchar_t {
	Plus = L'+',
	Minus = L'-',
	Mul = L'*',
	Div = L'/',
	LParen = L'(',
	RParen = L')'
};


enum class TokenType {
	Operator,
	Number
};

class Token {
	public:
		Token(Operator op) : m_type(TokenType::Operator), m_operator(op) {}
		Token(double num) : m_type(TokenType::Number), m_number(num) {}
		TokenType Type() const { return m_type; }

		operator Operator() const {
			if (m_type != TokenType::Operator)
				throw std::logic_error("Should be operator token!");
			return m_operator;
		}

		operator double() const {
			if (m_type != TokenType::Number)
				throw std::logic_error("Should be number token!");
			return m_number;
		}

		bool operator == (const Token &ref) const {
			if (m_type != ref.m_type)
				return false;

			switch (m_type) {
			case TokenType::Number:
				if (m_number != ref.m_number)
					return false;
				break;
			case TokenType::Operator:
				if (m_operator != ref.m_operator)
					return false;
				break;
			default:
				throw std::logic_error("Not supported token type at operator ==");
			}

			return true;
		}

		bool operator != (const Token &ref) const {
			return !(*this == ref);
		}

	private:
		TokenType m_type;
		union {
			Operator m_operator;
			double m_number;
		};
};

inline std::wstring ToString(const Operator &op) {
	return{ static_cast<wchar_t>(op) };
}

inline std::wstring ToString(const Token &token) {
	switch(token.Type()) {
	case TokenType::Number:
		return std::to_wstring(static_cast<double>(token));
	case TokenType::Operator:
		return ToString(static_cast<Operator>(token));
	default:
		throw std::out_of_range("TokenType");
	}
}

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
