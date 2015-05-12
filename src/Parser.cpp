/*
 * Parser.cpp
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */

#include <iostream>

#include "Parser.h"
#include "SyntaxException.h"

using std::cout;
using std::endl;

Parser::Parser() {

}

Parser::~Parser() {

}

void Parser::Configurate(){
	m_ruleBase = "program";
	setRule
	(1, "program", 			{"module", TToken::TTokenClass::_dot})
	(2, "module", 		  	{"moduleheading", "block", TToken::TTokenClass::_id})
	(3, "moduleheading", 	{TToken::TTokenClass::_module, TToken::TTokenClass::_id, TToken::TTokenClass::_semicolom})
	(4, "block", 			{TToken::TTokenClass::_end})
	(5, "block", 			{"statementpart", TToken::TTokenClass::_end})
	(6, "statementpart", 	{TToken::TTokenClass::_begin, "statementsequence"})
	(7, "statementsequence",{"statement", "fctstatement"})
	(8, "statement", 		{"assignment"})
	(9, "assignment", 		{"variable", TToken::TTokenClass::_ass, "expression"})
	(10, "variable", 		{TToken::TTokenClass::_id})
	(11, "expression", 		{TToken::TTokenClass::_intval})
	(12, "fctstatement",	{TToken::TTokenClass::_semicolom, "statementsequence"})
	(13, "fctstatement",	{});

}
void Parser::setInput(const vector<TToken>& i_input){
	m_input = i_input;
}
Parser& Parser::setRule(const Rule::TRuleNumber i_num, const TSyntaxRuleAtom& i_leftPart, const vector<TSyntaxRuleAtom>& i_rightPart){
	m_rules.insert(static_cast<TRulePair>(Rule{i_num, i_leftPart, i_rightPart}));
	return *this;
}
Parser& Parser::operator()(const Rule::TRuleNumber i_num, const TSyntaxRuleAtom& i_leftPart, const vector<TSyntaxRuleAtom>& i_righPart){
	return setRule(i_num, i_leftPart, i_righPart);
}
Parser::ParseTree  Parser::Parse(){
	m_currentInputTerminal = m_input.begin();
	ParseTree o_parseTree;

	if (!Parse(m_ruleBase, o_parseTree))
		throw SyntaxException(*m_currentInputTerminal, "Unmatched token");

	if ((m_currentInputTerminal != m_input.end()))
		throw SyntaxException(*m_currentInputTerminal, "Non-empty rest of tokens started from");
	return o_parseTree;
}
bool Parser::Parse(const TSyntaxRuleAtom i_syntaxAtom, ParseTree& o_parseTree){
	if (i_syntaxAtom.IsTerminal()){
		return CheckNextTerminal(i_syntaxAtom.getTerminal());
	}

	Rule matchedRule;
	vector<ParseTree> childNodes;
	auto savedCurrentPosition = m_currentInputTerminal;
	auto rulePairCandidates = m_rules.equal_range(i_syntaxAtom);
	for (auto itRulePair = rulePairCandidates.first; itRulePair != rulePairCandidates.second; itRulePair++){ // Loop possible rules

		const auto currentRule = itRulePair->second;
		if (currentRule.IsLambda() && !matchedRule.IsInit()){
			matchedRule = currentRule;
			continue;
		}

		bool isRuleParsed = false;
		m_currentInputTerminal = savedCurrentPosition;
		for (auto& syntaxAtom : currentRule.getRightPart()){ //Loop right rule part
			ParseTree childTree;
			if (!(isRuleParsed = Parse(syntaxAtom, childTree))){
				childNodes.clear();
				break;
			}
			if (!syntaxAtom.IsTerminal())
				childNodes.push_back(childTree);
		}
		if (isRuleParsed){
			matchedRule = currentRule;
			break;
		}
	}
	if (matchedRule.IsInit()){
		o_parseTree.rule = matchedRule;
		o_parseTree.childRules = childNodes;
	}
	return matchedRule.IsInit();
}
bool Parser::CheckNextTerminal(const TToken::TTokenClass& i_tokenClassToBeCompared){
	if (m_currentInputTerminal == m_input.end())
		return false;

	bool isEqual = (m_currentInputTerminal->getClass() == i_tokenClassToBeCompared);
	if (isEqual){
		m_currentInputTerminal++;
	}

	return isEqual;
}
void Parser::PrintTree(ostream& i_os, const ParseTree& i_parseTree){
	Parser::PrintTree(i_os, i_parseTree, 0);
}
void Parser::PrintTree(ostream& i_os, const ParseTree& i_parseTree, unsigned i_marginNum){
	for (auto counter = i_marginNum; counter > 0; counter--)
		i_os << '\t';
	i_os << i_parseTree.rule << endl;
	for (auto& it : i_parseTree.childRules)
		Parser::PrintTree(i_os, it, ++i_marginNum);
}
