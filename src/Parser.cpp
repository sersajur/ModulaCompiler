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

	m_rules.insert(TRule("program", 		{"module", TToken::TTokenClass::_dot}));
	m_rules.insert(TRule("module", 		  	{"moduleheading", "block", TToken::TTokenClass::_id}));
	m_rules.insert(TRule("moduleheading", 	{TToken::TTokenClass::_module, TToken::TTokenClass::_id, TToken::TTokenClass::_semicolom}));
	m_rules.insert(TRule("block", 			{TToken::TTokenClass::_end}));
	m_rules.insert(TRule("block", 			{"statementpart", TToken::TTokenClass::_end}));
	m_rules.insert(TRule("statementpart", 	{TToken::TTokenClass::_begin, "statementsequence"}));
	m_rules.insert(TRule("statementsequence",{"statement", "fctstatement"}));
	m_rules.insert(TRule("statement", 		{"assignment"}));
	m_rules.insert(TRule("assignment", 		{"variable", TToken::TTokenClass::_ass, "expression"}));
	m_rules.insert(TRule("variable", 		{TToken::TTokenClass::_id}));
	m_rules.insert(TRule("expression", 		{TToken::TTokenClass::_intval}));
	m_rules.insert(TRule("fctstatement",	{TToken::TTokenClass::_semicolom, "statementsequence"}));
	m_rules.insert(TRule("fctstatement",	{}));

}
void Parser::setInput(const vector<TToken>& i_input){
	m_input = i_input;
}
void  Parser::Parse(){
	m_unrecognizedTerminal = m_currentInputTerminal = m_input.begin();

	if (!Parse(m_ruleBase))
		throw SyntaxException(*m_currentInputTerminal, "Unmatched token");

	if ((m_currentInputTerminal != m_input.end()))
		throw SyntaxException(*m_currentInputTerminal, "Non-empty rest of tokens started from");

}

bool Parser::Parse(const TSyntaxRuleAtom i_syntaxAtom){

	if (i_syntaxAtom.IsTerminal()){
		std::cout << TToken::ClassToString(i_syntaxAtom.getTerminal()) << endl;
		return CheckNextTerminal(i_syntaxAtom.getTerminal());
	}
	std::cout << "BEFORE: ";
	std::cout << i_syntaxAtom.getNterminal() << endl;
	bool isLambda = false;
	bool result = false;
	auto matchedRules = m_rules.equal_range(i_syntaxAtom);
	auto savedCurrentPosition = m_currentInputTerminal;
	for (auto itRule = matchedRules.first; itRule != matchedRules.second; itRule++){ // Loop possible rules
		bool oneRuleResult = true;
		isLambda = true;
		m_currentInputTerminal = savedCurrentPosition;
		for (auto itSyntaxAtom = itRule->second.begin(); itSyntaxAtom != itRule->second.end(); itSyntaxAtom++){ //Loop right rule part
			isLambda = false;
			if (!(oneRuleResult = Parse(*itSyntaxAtom)))
				break;
		}
		if ((result = oneRuleResult))
			break;
	}
	std::cout << "AFTER: ";
	std::cout << i_syntaxAtom.getNterminal() << endl;
	return result || isLambda;
}
bool Parser::CheckNextTerminal(const TToken::TTokenClass& i_tokenClassToBeCompared){
	if (m_currentInputTerminal == m_input.end())
		return false;

	std::cout << "DEBUG: terminal comparing:\t";
	//std::cout << *m_currentInputTerminal << endl;
	bool isEqual = (m_currentInputTerminal->getClass() == i_tokenClassToBeCompared);
	if (isEqual){
		std::cout << *m_currentInputTerminal << endl;
		m_currentInputTerminal++;
		m_unrecognizedTerminal = ((m_unrecognizedTerminal < m_currentInputTerminal) ? m_currentInputTerminal : m_unrecognizedTerminal);
	}

	return isEqual;
}
