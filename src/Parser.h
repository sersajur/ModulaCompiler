/*
 * Parser.h
 *
 *  Created on: 10 трав. 2015
 *      Author: sersajur
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <map>

#include "TToken.h"
#include "TSyntaxRuleAtom.h"

using std::vector;
using std::multimap;
using std::pair;

class Parser {
	typedef multimap<TSyntaxRuleAtom, vector<TSyntaxRuleAtom>> TRules;
	typedef pair<TSyntaxRuleAtom, vector<TSyntaxRuleAtom>> TRule;

	TSyntaxRuleAtom m_ruleBase;
	TRules m_rules;
	vector<TToken> m_input;


	vector<TToken>::iterator m_currentInputTerminal, m_unrecognizedTerminal;
	bool CheckNextTerminal(const TToken::TTokenClass& i_tokenClassToBeCompared);
	bool Parse(const TSyntaxRuleAtom i_ruleAtom);
public:
	Parser();
	virtual ~Parser();

	void setInput(const vector<TToken>& i_input);
	void Configurate(); //TODO: It should be configured by outside grammar
	void Parse(); //TODO: Provide output tree with used rules
};

#endif /* PARSER_H_ */
