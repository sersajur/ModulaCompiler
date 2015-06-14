/*
 * SemanticException.h
 *
 *  Created on: May 25, 2015
 *      Author: sersajur
 */

#ifndef SRC_SEMANTICEXCEPTION_H_
#define SRC_SEMANTICEXCEPTION_H_


#include <string>

#include "CompileException.h"

class SemanticException: public CompileException {
public:
	SemanticException(const std::string& i_reason);
	SemanticException(const TToken& i_problemToken, const char* i_reason);
	SemanticException(const TToken& i_problemToken, const std::string& i_reason);
	virtual ~SemanticException();
};

#endif /* SRC_SEMANTICEXCEPTION_H_ */
