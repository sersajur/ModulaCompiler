/*
 * ParseTree.cpp
 *
 *  Created on: 1 черв. 2015
 *      Author: sersajur
 */

#include "ParseTree.h"

using std::ostream;
using std::endl;

ParseTree::ParseTree() {
	// TODO Auto-generated constructor stub

}

ParseTree::~ParseTree() {
	// TODO Auto-generated destructor stub
}

void ParseTree::setNode(const Rule& i_rule){
	m_rule = i_rule;
}

void ParseTree::setChildren(const std::vector<ParseTree>& i_children){
	m_childRules = i_children;
}

void ParseTree::AssociateWithInput(std::vector<TToken>::const_iterator& io_it){
	auto subtree = m_childRules.begin();
	for (auto& it : m_rule.m_rightPart)
		if (it.IsTerminal())
			it.setAssociatedToken(*io_it++);
		else{
			subtree->AssociateWithInput(io_it);
			subtree++;
		}
}

void ParseTree::AssociateWithInput(const std::vector<TToken>& i_input){
	std::vector<TToken>::const_iterator startInput = i_input.begin();
	this->AssociateWithInput(startInput);
}

ostream& ParseTree::FormatedPrint(ostream& io_os, const unsigned i_tabCounter) const{
	for (auto counter = i_tabCounter; counter > 0; counter--)
		io_os << '\t';
	io_os << m_rule << endl;
	for (auto& it : m_childRules)
		it.FormatedPrint(io_os, i_tabCounter + 1);
	return io_os;
}

ostream& operator<<(ostream& io_os, const ParseTree& i_parseTree){
	return i_parseTree.FormatedPrint(io_os, 0);
}
void ParseTree::TestPrint(std::ostream& o_os)const{
	auto subtree = m_childRules.begin();
	for (auto& it : m_rule.m_rightPart)
		if (it.IsTerminal())
			o_os << it << ": " << it.getAssociatedToken() << std::endl;
		else{
			subtree->TestPrint(o_os);
			subtree++;
		}

}
