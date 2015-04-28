/*
 * TLexicalException.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: sersajur
 */

#include <sstream>

#include "TLexicalException.h"

using std::ostringstream;

TLexicalException::TLexicalException(const string& i_reason):
runtime_error("Lexical error"),
m_what(i_reason){

}

TLexicalException::TLexicalException
(const unsigned i_line, const unsigned i_column, const string& i_errLexeme, const char* i_reason):
runtime_error("Lexical error"){
	ostringstream ostr;
	ostr << i_line << ":" << i_column
		 << " in \'" << i_errLexeme << "\' <-- "
		 << i_reason;
	m_what = ostr.str();
}

const char* TLexicalException::what() const throw(){
	return m_what.c_str();
}

TLexicalException::~TLexicalException() {

}

