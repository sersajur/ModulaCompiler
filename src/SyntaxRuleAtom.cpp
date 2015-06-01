/*
 * TSyntaxRuleAtom.cpp
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */

#include "SyntaxRuleAtom.h"

SyntaxRuleAtom::SyntaxRuleAtom():
m_isTerminalFlag{false},
m_terminal{TToken::TTokenClass(-1)}{

}

SyntaxRuleAtom::~SyntaxRuleAtom(){

}

SyntaxRuleAtom::SyntaxRuleAtom(const TToken::TTokenClass& i_tokenClass):
m_isTerminalFlag{true},
m_terminal{i_tokenClass}{

}
SyntaxRuleAtom::SyntaxRuleAtom(const string& i_ntermName):
m_isTerminalFlag{false},
m_nterminal{i_ntermName},
m_terminal{TToken::TTokenClass(-1)}{

}
SyntaxRuleAtom::SyntaxRuleAtom(const char* i_ntermName):
m_isTerminalFlag{false},
m_nterminal{i_ntermName},
m_terminal{TToken::TTokenClass(-1)}{

}
SyntaxRuleAtom::SyntaxRuleAtom(const TToken& i_token):
m_isTerminalFlag{true},
m_terminal{i_token.getClass()}{

}
bool SyntaxRuleAtom::operator<(const SyntaxRuleAtom& i_rOperand)const{
	return this->getNterminal() < i_rOperand.getNterminal();
}
ostream& operator<<(ostream& io_os, const SyntaxRuleAtom& i_synAtom){
	if (i_synAtom.IsTerminal())
		io_os << TToken::ClassToString(i_synAtom.getTerminal());
	else if (!i_synAtom.getNterminal().empty())
			io_os << '<' << i_synAtom.getNterminal() << '>';
	return io_os;
}
