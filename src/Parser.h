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
#include <iostream>

#include "TToken.h"
#include "TSyntaxRuleAtom.h"
#include "Rule.h"


using std::vector;
using std::multimap;
using std::pair;
using std::ostream;

class Parser {
public:
	struct ParseTree{
		Rule rule;
		vector<ParseTree>  childRules;
	};
private:

	typedef multimap<TSyntaxRuleAtom, Rule> TRules;
	typedef pair<TSyntaxRuleAtom, Rule> TRulePair;

	TSyntaxRuleAtom m_ruleBase;
	TRules m_rules;
	vector<TToken> m_input;

	vector<TToken>::iterator m_currentInputTerminal;

	bool CheckNextTerminal(const TToken::TTokenClass& i_tokenClassToBeCompared);
	bool Parse(const TSyntaxRuleAtom i_ruleAtom, ParseTree& io_pareTree);
	static void PrintTree(ostream& i_os, const ParseTree& i_parseTree, unsigned i_marginNum);
public:
	Parser();
	virtual ~Parser();

	void setInput(const vector<TToken>& i_input);
	Parser& setRule(const Rule::TRuleNumber, const TSyntaxRuleAtom&, const vector<TSyntaxRuleAtom>&);
	Parser& operator()(const Rule::TRuleNumber, const TSyntaxRuleAtom&, const vector<TSyntaxRuleAtom>&);
	void Configurate(); //TODO: It should be configured by outside grammar
	ParseTree Parse();
	static void PrintTree(ostream& i_os, const ParseTree& i_parseTree);
};

#endif /* PARSER_H_ */
