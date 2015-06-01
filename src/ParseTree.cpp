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
