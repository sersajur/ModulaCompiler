/*
 * SyntaxRuleAtom.h
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */

#ifndef SYNTAXRULEATOM_H_
#define SYNTAXRULEATOM_H_

#include <string>
#include <iostream>

#include "TToken.h"

using std::string;
using std::ostream;

class SyntaxRuleAtom {
private:
	bool m_isTerminalFlag;
	//TODO: research if there is more optimal way to keep XOR-data (or use union otherwise)
	string m_nterminal;

	TToken::TTokenClass m_terminal;
	TToken m_associatedToken; //TODO: re-engineering needed
public:
	SyntaxRuleAtom();
	SyntaxRuleAtom(const TToken::TTokenClass& i_tokenClass);
	SyntaxRuleAtom(const string& i_ntermName);
	SyntaxRuleAtom(const char* i_ntermName);
	SyntaxRuleAtom(const TToken& i_token);
	virtual ~SyntaxRuleAtom();

	bool operator<(const SyntaxRuleAtom& i_rOperand)const;

	bool IsTerminal() const {return m_isTerminalFlag;}
	TToken::TTokenClass getTerminal() const {return m_terminal;}
	string getNterminal() const {return m_nterminal;}

	void setAssociatedToken(const TToken& i_token) {m_associatedToken = i_token;} //TODO: re-engineering needed
	const TToken getAssociatedToken()const {return m_associatedToken;} //TODO: re-engineering needed

	friend ostream& operator<<(ostream& io_os, const SyntaxRuleAtom& i_synAtom);
};

#endif /* SYNTAXRULEATOM_H_ */
