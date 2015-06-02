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

#include "SyntaxRuleAtom.h"

class Rule {
public:
	typedef unsigned TRuleNumber;
	typedef std::vector<SyntaxRuleAtom> TRightPart;

	Rule():
		m_isInit{false}, m_number{0}
	{}
	Rule(TRuleNumber i_num, const SyntaxRuleAtom& i_leftPart, const std::vector<SyntaxRuleAtom>& i_rightPart);
	virtual ~Rule();
	operator std::pair<SyntaxRuleAtom, Rule>();
	TRightPart getRightPart()const {return m_rightPart;}
	bool IsInit()const {return m_isInit;}
	bool IsLambda() const {return m_isInit && m_rightPart.empty();}
	friend ostream& operator<<(ostream& io_os, const Rule& i_rule);
	friend class ParseTree;
private:
	bool m_isInit;
	TRuleNumber m_number;
	SyntaxRuleAtom m_leftPart;
	TRightPart m_rightPart;
};

#endif /* RULE_H_ */
