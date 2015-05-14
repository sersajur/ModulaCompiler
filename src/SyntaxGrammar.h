/*
 * SyntaxGrammar.h
 *
 *  Created on: May 13, 2015
 *      Author: sersajur
 */

#ifndef SRC_SYNTAXGRAMMAR_H_
#define SRC_SYNTAXGRAMMAR_H_

#include <map>

#include "TSyntaxRuleAtom.h"
#include "Rule.h"

using std::multimap;

class SyntaxGrammar {
	TSyntaxRuleAtom m_ruleBase;
	multimap<TSyntaxRuleAtom, Rule> m_rulesMap;
public:
	SyntaxGrammar();
	SyntaxGrammar(const TSyntaxRuleAtom& i_ruleBase);
	virtual ~SyntaxGrammar();

	SyntaxGrammar& InsertRule(const TSyntaxRuleAtom& i_leftPart, const vector<TSyntaxRuleAtom>& i_rightPart, Rule::TRuleNumber i_rulNum);
	SyntaxGrammar& operator()(const TSyntaxRuleAtom& i_leftPart, const vector<TSyntaxRuleAtom>& i_rightPart);
	SyntaxGrammar& operator()(const TSyntaxRuleAtom& i_leftPart, const vector<TSyntaxRuleAtom>& i_rightPart, Rule::TRuleNumber i_ruleNum);

	vector<Rule> getMatchedRules(const TSyntaxRuleAtom& i_leftPart)const;
	TSyntaxRuleAtom getRuleBase()const {return m_ruleBase;}
};

#endif /* SRC_SYNTAXGRAMMAR_H_ */
