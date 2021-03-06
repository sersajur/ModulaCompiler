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
#include "SyntaxRuleAtom.h"
#include "Rule.h"
#include "SyntaxGrammar.h"
#include "ParseTree.h"

class Parser {
private:
	SyntaxGrammar m_grammar;
	std::vector<TToken> m_input;

	std::vector<TToken>::iterator m_currentInputTerminal, m_firstUnrecognized;

	bool CheckNextTerminal(const TToken::TTokenClass& i_tokenClassToBeCompared);
	bool Parse(const SyntaxRuleAtom i_ruleAtom, ParseTree& io_pareTree);
//	static void PrintTree(ostream& i_os, const ParseTree& i_parseTree, unsigned i_marginNum);
public:
	Parser();
	Parser(const SyntaxGrammar& i_grammar);
	virtual ~Parser();

	void setInput(const std::vector<TToken>& i_input);
	void Configurate(); //TODO: It should be configured by outside grammar
	ParseTree Parse();
	ParseTree Parse(const std::vector<TToken>& i_input);

//	static void PrintTree(ostream& i_os, const ParseTree& i_parseTree);
};

#endif /* PARSER_H_ */
