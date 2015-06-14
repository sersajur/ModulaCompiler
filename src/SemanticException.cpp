/*
 * SemanticException.cpp
 *
 *  Created on: May 25, 2015
 *      Author: sersajur
 */

#include "SemanticException.h"

SemanticException::SemanticException(const string& i_reason):
CompileException(i_reason){

}

SemanticException::SemanticException(const TToken& i_problemToken, const char* i_reason):
CompileException{i_problemToken, i_reason}{

}
SemanticException::SemanticException(const TToken& i_problemToken, const std::string& i_reason):
CompileException{i_problemToken, i_reason.c_str()}{

}
SemanticException::~SemanticException(){

}
