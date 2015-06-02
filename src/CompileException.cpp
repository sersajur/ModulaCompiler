/*
 * CompileException.cpp
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */

#include <sstream>
#include "CompileException.h"


CompileException::CompileException(const string& i_reason):
runtime_error("Compile error"),
m_what(i_reason){

}
CompileException::CompileException
(const unsigned i_line, const unsigned i_column, const string& i_errLexeme, const char* i_reason):
runtime_error("Compile error"){
	std::ostringstream ostr{};
	ostr << i_line << ":" << i_column
		<< " in \'" << i_errLexeme << "\' <-- "
		<< i_reason;
	m_what = ostr.str();
}

CompileException::CompileException(const TToken& i_problemToken, const char* i_reason):
runtime_error("Compile error"){
	std::ostringstream ostr{};
	auto pos = i_problemToken.getPosition();
	ostr << pos.line << ":" << pos.column
		<< " in \'" << i_problemToken.getLexeme() << "\' <-- "
		<< i_reason;
	m_what = ostr.str();
}

const char* CompileException::what() const throw(){
	return m_what.c_str();
}

CompileException::~CompileException(){

}
