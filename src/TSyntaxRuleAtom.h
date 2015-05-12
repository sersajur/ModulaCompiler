/*
 * TSyntaxRuleAtom.h
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */

#ifndef TSYNTAXRULEATOM_H_
#define TSYNTAXRULEATOM_H_

#include <string>
#include <iostream>

#include "TToken.h"

using std::string;
using std::ostream;

class TSyntaxRuleAtom {
private:
	bool m_isTerminalFlag;
	//TODO: research if there is more optimal way to keep XOR-data (or use union otherwise)
	string m_nterminal;
	TToken::TTokenClass m_terminal;
public:
	TSyntaxRuleAtom();
	TSyntaxRuleAtom(const TToken::TTokenClass& i_tokenClass);
	TSyntaxRuleAtom(const string& i_ntermName);
	TSyntaxRuleAtom(const char* i_ntermName);
	TSyntaxRuleAtom(const TToken& i_token);
	virtual ~TSyntaxRuleAtom();

	bool operator<(const TSyntaxRuleAtom& i_rOperand)const;

	bool IsTerminal() const {return m_isTerminalFlag;}
	TToken::TTokenClass getTerminal() const {return m_terminal;}
	string getNterminal() const {return m_nterminal;}

	friend ostream& operator<<(ostream& io_os, const TSyntaxRuleAtom& i_synAtom);
};

#endif /* TSYNTAXRULEATOM_H_ */
