/*
 * ParseTree.h
 *
 *  Created on: 1 черв. 2015
 *      Author: sersajur
 */

#ifndef PARSETREE_H_
#define PARSETREE_H_

#include <vector>
#include <ostream>
#include <string>
#include "Rule.h"
#include "TableOfNames.h"
#include "TToken.h"
#include "ByteCode.h"

class ParseTree {
private:
	Rule m_rule;
	std::vector<ParseTree>  m_childRules;
private:

	std::ostream& FormatedPrint(std::ostream& io_os, const unsigned i_tabCounter) const;
	void AssociateWithInput(std::vector<TToken>::const_iterator& io_it);
	bool operator==(const char* i_nterminalValue)const{return (m_rule.m_leftPart.getNterminal()==i_nterminalValue);}
	void InsertToTableIfUndefinedOrThrowException(TableOfNames& io_tableOfNames, TableOfNames::TRecord i_record, const TToken& i_token)const;
	void DefinitionProcess(TableOfNames& io_tableOfNames, const std::string i_currentBlock = "");
	void UsageCheckProcess(TableOfNames& io_tableOfNames, const std::string i_currentBlock = "");
public:
	ParseTree();
	virtual ~ParseTree();
	void setNode(const Rule& i_rule);
	void setChildren(const std::vector<ParseTree>& i_children);
	void AssociateWithInput(const std::vector<TToken>& i_input);
	TableOfNames SemanticAnalyze();
	std::string GenerateCode(const TableOfNames& i_tableOfNames, ByteCode& code);

	friend std::ostream& operator<<(std::ostream& io_os, const ParseTree& i_parseTree);

	const ParseTree& operator=(const ParseTree i_parseTree);
	void TestPrint(std::ostream& o_os)const; //TODO: remove debug
	operator std::string()const {return m_rule.m_leftPart.getNterminal();}
};

#endif /* PARSETREE_H_ */
