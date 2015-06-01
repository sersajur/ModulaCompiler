/*
 * SyntaxGrammar.h
 *
 *  Created on: May 13, 2015
 *      Author: sersajur
 */

#ifndef SRC_SYNTAXGRAMMAR_H_
#define SRC_SYNTAXGRAMMAR_H_

#include <map>

#include "SyntaxRuleAtom.h"
#include "Rule.h"

using std::multimap;

class SyntaxGrammar {
	SyntaxRuleAtom m_ruleBase;
	multimap<SyntaxRuleAtom, Rule> m_rulesMap;
public:
	SyntaxGrammar();
	SyntaxGrammar(const SyntaxRuleAtom& i_ruleBase);
	virtual ~SyntaxGrammar();

	SyntaxGrammar& InsertRule(const SyntaxRuleAtom& i_leftPart, const vector<SyntaxRuleAtom>& i_rightPart, Rule::TRuleNumber i_rulNum);
	SyntaxGrammar& operator()(const SyntaxRuleAtom& i_leftPart, const vector<SyntaxRuleAtom>& i_rightPart);
	SyntaxGrammar& operator()(const SyntaxRuleAtom& i_leftPart, const vector<SyntaxRuleAtom>& i_rightPart, Rule::TRuleNumber i_ruleNum);

	vector<Rule> getMatchedRules(const SyntaxRuleAtom& i_leftPart)const;
	SyntaxRuleAtom getRuleBase()const {return m_ruleBase;}
};

#endif /* SRC_SYNTAXGRAMMAR_H_ */
