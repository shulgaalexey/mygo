#ifndef __EVALUATOR_H_INCLUDED__
#define __EVALUATOR_H_INCLUDED__

#include "parser.h"

namespace Evaluator {

inline double Evaluate(const Tokens &tokens) {
	double result = 0.;
	for (const Token &token : tokens) {
		result = token;
	}
	return result;
}

} // namespace Evaluator

#endif/*__EVALUATOR_H_INCLUDED__*/
