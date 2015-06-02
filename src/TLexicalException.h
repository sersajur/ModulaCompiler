/*
 * TLexicalException.h
 *
 *  Created on: Apr 28, 2015
 *      Author: sersajur
 */

#ifndef SRC_TLEXICALEXCEPTION_H_
#define SRC_TLEXICALEXCEPTION_H_

#include <stdexcept>
#include <string>

#include "TToken.h"

class TLexicalException: public std::runtime_error {
public:
	TLexicalException(const std::string& i_reason);
	TLexicalException(const unsigned i_line, const unsigned i_column, const std::string& i_errLexeme, const char* i_reason);
	const char* what() const throw() override;
	virtual ~TLexicalException();
private:
	std::string m_what;
};

#endif /* SRC_TLEXICALEXCEPTION_H_ */
