/*
 * TLexicalException.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: sersajur
 */

#include <sstream>

#include "TLexicalException.h"

TLexicalException::TLexicalException(const std::string& i_reason):
std::runtime_error("Lexical error"),
m_what(i_reason){

}

TLexicalException::TLexicalException
(const unsigned i_line, const unsigned i_column, const std::string& i_errLexeme, const char* i_reason):
std::runtime_error("Lexical error"){
	std::ostringstream ostr{};
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

