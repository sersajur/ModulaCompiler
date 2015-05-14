/*
 * Rule.h
 *
 *  Created on: 11 трав. 2015
 *      Author: sersajur
 */

#ifndef RULE_H_
#define RULE_H_

#include <vector>
#include <iostream>

#include "TSyntaxRuleAtom.h"

using std::vector;
using std::pair;
using std::ostream;

class Rule {
public:
	typedef unsigned TRuleNumber;
	typedef vector<TSyntaxRuleAtom> TRightPart;

	Rule():
		m_isInit{false}, m_number{0}
	{}
	Rule(TRuleNumber i_num, const TSyntaxRuleAtom& i_leftPart, const vector<TSyntaxRuleAtom>& i_rightPart);
	virtual ~Rule();
	operator pair<TSyntaxRuleAtom, Rule>();
	TRightPart getRightPart()const {return m_rightPart;}
	bool IsInit()const {return m_isInit;}
	bool IsLambda() const {return m_isInit && m_rightPart.empty();}
	friend ostream& operator<<(ostream& io_os, const Rule& i_rule);
private:
	bool m_isInit;
	TRuleNumber m_number;
	TSyntaxRuleAtom m_leftPart;
	TRightPart m_rightPart;
};

#endif /* RULE_H_ */
