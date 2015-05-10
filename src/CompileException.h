/*
 * CompileException.h
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */

#ifndef COMPILEEXCEPTION_H_
#define COMPILEEXCEPTION_H_

#include <stdexcept>
#include <string>

#include "TToken.h"

using std::runtime_error;
using std::string;

class CompileException: public runtime_error {
public:
	CompileException(const string& i_reason);
	CompileException(const unsigned i_line, const unsigned i_column, const string& i_errLexeme, const char* i_reason);
	CompileException(const TToken& i_problemToken, const char* i_reason);
	const char* what() const throw() override;
	virtual ~CompileException();

private:
	string m_what;
};

#endif /* COMPILEEXCEPTION_H_ */
