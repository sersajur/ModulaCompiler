/*
 * SyntaxGrammar.cpp
 *
 *  Created on: May 13, 2015
 *      Author: sersajur
 */

#include "SyntaxGrammar.h"

SyntaxGrammar::SyntaxGrammar(){

}
SyntaxGrammar::SyntaxGrammar(const SyntaxRuleAtom& i_ruleBase):
m_ruleBase(i_ruleBase){

}
SyntaxGrammar::~SyntaxGrammar(){

}
SyntaxGrammar& SyntaxGrammar::InsertRule(const SyntaxRuleAtom& i_leftPart, const std::vector<SyntaxRuleAtom>& i_rightPart, Rule::TRuleNumber i_ruleNum){
	m_rulesMap.insert(std::pair<SyntaxRuleAtom,Rule>{i_leftPart, Rule{i_ruleNum, i_leftPart, i_rightPart}});
	return *this;
}
SyntaxGrammar& SyntaxGrammar::operator()(const SyntaxRuleAtom& i_leftPart, const std::vector<SyntaxRuleAtom>& i_rightPart){
	return InsertRule(i_leftPart, i_rightPart, m_rulesMap.size()+1);
}
SyntaxGrammar& SyntaxGrammar::operator()(const SyntaxRuleAtom& i_leftPart, const std::vector<SyntaxRuleAtom>& i_rightPart, Rule::TRuleNumber i_ruleNum){
	return InsertRule(i_leftPart, i_rightPart, i_ruleNum);
}
std::vector<Rule> SyntaxGrammar::getMatchedRules(const SyntaxRuleAtom& i_leftPart)const{
	auto eqRange = m_rulesMap.equal_range(i_leftPart);
	std::vector<Rule> o_matchedRules{};
	for (auto it = eqRange.first; it != eqRange.second; it++)
		o_matchedRules.push_back(it->second);
	return o_matchedRules;
}
