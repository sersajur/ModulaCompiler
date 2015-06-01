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
#include "Rule.h"
#include "TToken.h"

class ParseTree {
private:
	Rule m_rule;
	std::vector<ParseTree>  m_childRules;
private:
	std::ostream& FormatedPrint(std::ostream& io_os, const unsigned i_tabCounter) const;
	void AssociateWithInput(std::vector<TToken>::const_iterator& io_it);
public:
	ParseTree();
	virtual ~ParseTree();

	void setNode(const Rule& i_rule);
	void setChildren(const std::vector<ParseTree>& i_children);

	void AssociateWithInput(const std::vector<TToken>& i_input);
	friend std::ostream& operator<<(std::ostream& io_os, const ParseTree& i_parseTree);

	void TestPrint(std::ostream& o_os)const; //TODO: remove debug
};

#endif /* PARSETREE_H_ */
