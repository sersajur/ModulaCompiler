/*
 * Rule.cpp
 *
 *  Created on: 11 трав. 2015
 *      Author: sersajur
 */

#include "Rule.h"

Rule::Rule(TRuleNumber i_num, const TSyntaxRuleAtom& i_leftPart, const vector<TSyntaxRuleAtom>& i_rightPart):
m_isInit{true},
m_number{i_num},
m_leftPart{i_leftPart},
m_rightPart{i_rightPart}{

}
Rule::~Rule(){

}
Rule::operator pair<TSyntaxRuleAtom, Rule>(){
	return pair<TSyntaxRuleAtom, Rule>{m_leftPart, *this};
}
ostream& operator<<(ostream& io_os, const Rule& i_rule){
	io_os << i_rule.m_number << ": "
		  << i_rule.m_leftPart  << "::=";
	for (auto& it: i_rule.m_rightPart)
		io_os << it << ' ';
	return io_os;
}
