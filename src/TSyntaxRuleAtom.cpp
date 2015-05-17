/*
 * TSyntaxRuleAtom.cpp
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */

#include "TSyntaxRuleAtom.h"

TSyntaxRuleAtom::TSyntaxRuleAtom():
m_isTerminalFlag{false},
m_terminal{TToken::TTokenClass(-1)}{

}

TSyntaxRuleAtom::~TSyntaxRuleAtom(){

}

TSyntaxRuleAtom::TSyntaxRuleAtom(const TToken::TTokenClass& i_tokenClass):
m_isTerminalFlag{true},
m_terminal{i_tokenClass}{

}
TSyntaxRuleAtom::TSyntaxRuleAtom(const string& i_ntermName):
m_isTerminalFlag{false},
m_nterminal{i_ntermName},
m_terminal{TToken::TTokenClass(-1)}{

}
TSyntaxRuleAtom::TSyntaxRuleAtom(const char* i_ntermName):
m_isTerminalFlag{false},
m_nterminal{i_ntermName},
m_terminal{TToken::TTokenClass(-1)}{

}
TSyntaxRuleAtom::TSyntaxRuleAtom(const TToken& i_token):
m_isTerminalFlag{true},
m_terminal{i_token.getClass()}{

}
bool TSyntaxRuleAtom::operator<(const TSyntaxRuleAtom& i_rOperand)const{
	return this->getNterminal() < i_rOperand.getNterminal();
}
ostream& operator<<(ostream& io_os, const TSyntaxRuleAtom& i_synAtom){
	if (i_synAtom.IsTerminal())
		io_os << TToken::ClassToString(i_synAtom.getTerminal());
	else if (!i_synAtom.getNterminal().empty())
			io_os << '<' << i_synAtom.getNterminal() << '>';
	return io_os;
}