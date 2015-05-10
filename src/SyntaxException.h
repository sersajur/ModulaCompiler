/*
 * SyntaxException.h
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */

#ifndef SYNTAXEXCEPTION_H_
#define SYNTAXEXCEPTION_H_

#include <string>

#include "CompileException.h"

using std::string;

class SyntaxException: public CompileException {
public:
	SyntaxException(const string& i_reason);
	SyntaxException(const unsigned i_line, const unsigned i_column, const string& i_errNterminal, const char* i_reason);
	SyntaxException(const TToken& i_problemToken, const char* i_reason);
	virtual ~SyntaxException();
};

#endif /* SYNTAXEXCEPTION_H_ */
