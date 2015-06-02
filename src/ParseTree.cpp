/*
 * ParseTree.cpp
 *
 *  Created on: 1 черв. 2015
 *      Author: sersajur
 */


#include "SemanticException.h"
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
void ParseTree::InsertToTableIfUndefinedOrThrowException(TableOfNames& io_tableOfNames, TableOfNames::TRecord i_record, const TToken& i_token)const{
	if (io_tableOfNames.IsDeclared(i_record.ID))
		throw SemanticException(i_token, "Already declared name");
	else{
		io_tableOfNames.Insert(i_record);
	}
}
void ParseTree::DefinitionProcess(TableOfNames& io_tableOfNames, const std::string i_currentBlock){


	if (m_rule.m_leftPart.getNterminal() == "program"){
		m_childRules[0].DefinitionProcess(io_tableOfNames, i_currentBlock);
	}
	else if (*this == "module"){
		TToken idToken = m_childRules[0].m_rule.getRightPart()[1].getAssociatedToken();
		TableOfNames::TNameId id{idToken.getLexeme(), i_currentBlock};
		ModuleAttributes attributes{};
		InsertToTableIfUndefinedOrThrowException(io_tableOfNames, {id, &attributes}, idToken);
		//to declarationparts (if it exists):
		m_childRules[1].m_childRules[0].DefinitionProcess(io_tableOfNames, id.name);
	}
	else if (*this == "declarationparts"){
		if (m_childRules[0].m_childRules[0] == "proceduredeclaration")
			m_childRules[0].m_childRules[0].DefinitionProcess(io_tableOfNames, i_currentBlock);
		else if (!m_childRules[0].m_childRules[0].m_rule.IsLambda())
			m_childRules[0].m_childRules[0].m_childRules[0].DefinitionProcess(io_tableOfNames, i_currentBlock);
		//to next declarationparts
		if (!m_childRules[1].m_rule.IsLambda())
			m_childRules[1].m_childRules[0].DefinitionProcess(io_tableOfNames, i_currentBlock);
	}
	else if ((*this == "constantdeclarations") || (*this == "variabledeclarations")){
		m_childRules[0].DefinitionProcess(io_tableOfNames, i_currentBlock);
		//to next constantdeclarations (variabledeclarations)
		if (!m_childRules[1].m_rule.IsLambda())
			m_childRules[1].m_childRules[0].DefinitionProcess(io_tableOfNames, i_currentBlock);
	}
	else if (*this == "constantdeclaration"){
		TToken idToken = m_rule.getRightPart()[0].getAssociatedToken();
		TableOfNames::TNameId id{idToken.getLexeme(), i_currentBlock};
		TToken valueToken{};
		bool isSign{false};
		int sign{1};
		if (m_childRules[0].m_childRules[0] == "unsignedconstant"){
			auto terminal = (m_childRules[0].m_childRules[0].m_childRules.empty() ? m_childRules[0].m_childRules[0].m_rule.getRightPart()[0] : m_childRules[0].m_childRules[0].m_childRules[0].m_rule.getRightPart()[0]);
			valueToken = terminal.getAssociatedToken();
		}
		else{
			isSign = true;
			auto terminal = m_childRules[0].m_childRules[1].m_rule.getRightPart()[0];
			valueToken = terminal.getAssociatedToken();
			terminal = m_childRules[0].m_childRules[0].m_rule.getRightPart()[0];
			if (terminal.getAssociatedToken().getClass() == TToken::TTokenClass::_sub)
				sign = -1;
		}
		TToken::TTokenValue value{valueToken.getValue()};
		NameAttributes::Type type = NameAttributes::TokenTypeToType(valueToken.getClass());
		if (isSign){
			if (type == NameAttributes::Type::Real)
				value.asReal *= float(sign);
			else
				value.asInt *= sign;
		}
		ConstantAttributes attributes{type, value};
		InsertToTableIfUndefinedOrThrowException(io_tableOfNames, {id, &attributes}, idToken);
	}
	else if (*this == "variabledeclaration"){
		if (m_childRules[1].m_childRules[0] == "basetype"){ //variable
			auto tokenClass = m_childRules[1].m_childRules[0].m_rule.getRightPart()[0].getTerminal();
			NameAttributes::Type type{NameAttributes::TokenTypeToType(tokenClass)};
			VariableAttributes attributes{type};
			ParseTree subtree = *this;
			do{
				subtree = subtree.m_childRules[0];
				TToken idToken = subtree.m_rule.getRightPart()[0].getAssociatedToken();
				TableOfNames::TNameId id{idToken.getLexeme(), i_currentBlock};
				InsertToTableIfUndefinedOrThrowException(io_tableOfNames, {id, &attributes}, idToken);
				subtree = subtree.m_childRules[0];
			}while(!subtree.m_rule.IsLambda());

		}
		else{ // array

		}
	}
	else if (*this == "proceduredeclaration"){

	}
}
void ParseTree::UsageCheckProcess(TableOfNames& io_tableOfNames, const std::string i_currentBlock){

}
TableOfNames ParseTree::SemanticAnalyze(){
	TableOfNames tableOfNames{};
	DefinitionProcess(tableOfNames);
	UsageCheckProcess(tableOfNames);
	return tableOfNames;
}
ByteCode ParseTree::GenerateCode(const TableOfNames& i_tableOfNames){
	//code stub
	return ByteCode{};
}
