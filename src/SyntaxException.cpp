/*
 * SyntaxException.cpp
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */
#include <sstream>

#include "SyntaxException.h"

using std::ostringstream;

SyntaxException::SyntaxException(const string& i_reason):
CompileException(i_reason){

}

SyntaxException::SyntaxException
(const unsigned i_line, const unsigned i_column, const string& i_errLexeme, const char* i_reason):
CompileException{i_line, i_column, i_errLexeme, i_reason}{

}

SyntaxException::SyntaxException(const TToken& i_problemToken, const char* i_reason):
CompileException{i_problemToken, i_reason}{

}

SyntaxException::~SyntaxException(){

}
