/*
 * ParseTree.cpp
 *
 *  Created on: 1 черв. 2015
 *      Author: sersajur
 */

#include <string>
#include "SemanticException.h"
#include "ParseTree.h"
#include <iostream> //debug

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
const ParseTree& ParseTree::operator=(const ParseTree i_parseTree){
	m_childRules = i_parseTree.m_childRules;
	m_rule = i_parseTree.m_rule;
	return *this;
}
void ParseTree::DefinitionProcess(TableOfNames& io_tableOfNames, const std::string i_currentBlock){
	if (m_rule.m_leftPart.getNterminal() == "program"){
		m_childRules[0].DefinitionProcess(io_tableOfNames, i_currentBlock);
	}
	else if (*this == "module"){
		TToken idToken = m_childRules[0].m_rule.getRightPart()[1].getAssociatedToken();
		TNameId id{idToken.getLexeme(), i_currentBlock};
		ModuleAttributes attributes{};
		InsertToTableIfUndefinedOrThrowException(io_tableOfNames, {id, &attributes}, idToken);

		TToken endIdToken = this->m_rule.getRightPart()[2].getAssociatedToken();
		if (idToken.getLexeme() != endIdToken.getLexeme()){
			throw SemanticException{endIdToken, std::string{"\"" + idToken.getLexeme() + "\" expected but \"" +  endIdToken.getLexeme() + "\" provided!"}};
		}
		//to declarationparts (if it exists):
		m_childRules[1].DefinitionProcess(io_tableOfNames, id.name);
	}
	else if (*this == "block"){
		if (!this->m_childRules.empty()){
			this->m_childRules[0].DefinitionProcess(io_tableOfNames, i_currentBlock);
		}
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
		TNameId id{idToken.getLexeme(), i_currentBlock};
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
		NameAttributes::Type type = NameAttributes::TokenTypeToType(valueToken.getClass());
		TToken::TTokenValue value{};
		switch (type){
		case NameAttributes::Type::Boolean:
			value.asBool = valueToken.getValue().asBool;
			break;
		case NameAttributes::Type::Integer:
			value.asInt = valueToken.getValue().asInt;
			value.asInt = (isSign ? value.asInt * int(sign) : value.asInt);
			break;
		case NameAttributes::Type::Real:
			value.asReal = valueToken.getValue().asReal;
			value.asReal = (isSign ? value.asReal * float(sign) : value.asReal);
			break;
		case NameAttributes::Type::String:
			value.asString = valueToken.getValue().asString;
			break;
		default:
			break;
		}
		ConstantAttributes attributes{type, value};
		InsertToTableIfUndefinedOrThrowException(io_tableOfNames, {id, &attributes}, idToken);
	}
	else if (*this == "variabledeclaration" || *this == "section"){
		if (m_childRules[1].m_childRules[0] == "basetype"){ //variable
			auto tokenClass = m_childRules[1].m_childRules[0].m_rule.getRightPart()[0].getTerminal();
			NameAttributes::Type type{NameAttributes::TokenTypeToType(tokenClass)};
			VariableAttributes attributes{type};
			ParseTree subtree = *this;
			do{
				subtree = subtree.m_childRules[0];
				TToken idToken = subtree.m_rule.getRightPart()[0].getAssociatedToken();
				TNameId id{idToken.getLexeme(), i_currentBlock};
				InsertToTableIfUndefinedOrThrowException(io_tableOfNames, {id, &attributes}, idToken);
				subtree = subtree.m_childRules[0];
			}while(!subtree.m_rule.IsLambda());
		}
		else{ // array
			auto typeTree = m_childRules[1].m_childRules[0].m_childRules[1]; //"type"
			NameAttributes::Type type{NameAttributes::TokenTypeToType(typeTree.m_rule.getRightPart()[0].getTerminal())};
			ParseTree subtree = m_childRules[1].m_childRules[0]; //"arraystructure"
			std::vector<ArrayAttributes::TDimBoundary> boundaries{};
			do{
				subtree = subtree.m_childRules[0]; //indexRangeListTree
				int left{subtree.m_childRules[0].m_rule.getRightPart()[0].getAssociatedToken().getValue().asInt};
				int right{subtree.m_childRules[0].m_rule.getRightPart()[2].getAssociatedToken().getValue().asInt};
				boundaries.push_back({left, right});
				subtree = subtree.m_childRules[1];
			}while(!subtree.m_rule.IsLambda());
			ArrayAttributes attributes{type, boundaries};
			subtree = *this;
			do{
				subtree = subtree.m_childRules[0];
				TToken idToken = subtree.m_rule.getRightPart()[0].getAssociatedToken();
				TNameId id{idToken.getLexeme(), i_currentBlock};
				InsertToTableIfUndefinedOrThrowException(io_tableOfNames, {id, &attributes}, idToken);
				subtree = subtree.m_childRules[0];
			}while(!subtree.m_rule.IsLambda());
		}
	}
	else if (*this == "proceduredeclaration"){
		TToken idToken = m_rule.getRightPart()[1].getAssociatedToken();
		std::string procName{idToken.getLexeme()};

		ParseTree& procBody = (m_childRules[0].m_childRules[0] == "fctmbprocedurebody" ? m_childRules[0].m_childRules[0] : m_childRules[0].m_childRules[1]);
		TToken endIdToken = procBody.m_rule.getRightPart()[1].getAssociatedToken();
		if (idToken.getLexeme() != endIdToken.getLexeme()){
			throw SemanticException{endIdToken, std::string{"\"" + idToken.getLexeme() + "\" expected but \"" +  endIdToken.getLexeme() + "\" provided!"}};
		}
		TNameId id{procName, i_currentBlock};
	// 1. Returning type
		NameAttributes::Type returningType{};
		auto& bodyTree = (m_childRules[0].m_childRules[0] == "fctmbprocedurebody" ? m_childRules[0].m_childRules[0] : m_childRules[0].m_childRules[1]);
		if (bodyTree.m_childRules[0] == "mbresulttype"){
			returningType = NameAttributes::TokenTypeToType(bodyTree.m_childRules[0].m_childRules[0].m_rule.getRightPart()[0].getTerminal());
		}else{
			returningType = NameAttributes::Type::Void;
		}
	// 2. Parameters to tableOfNames + accepting parameters' type
		std::vector<TNameId> params{};
		if (m_childRules[0].m_childRules[0] == "mbformalparameters" && !m_childRules[0].m_childRules[0].m_childRules[0].m_rule.IsLambda()){
			auto subTree = m_childRules[0].m_childRules[0].m_childRules[0];
			do{
				subTree = subTree.m_childRules[0];
				subTree.m_childRules[1].DefinitionProcess(io_tableOfNames, procName);
				auto identListTree = subTree.m_childRules[1];
				do{
					identListTree = identListTree.m_childRules[0];
					params.push_back({identListTree.m_rule.getRightPart()[0].getAssociatedToken().getLexeme(), procName});
					identListTree = identListTree.m_childRules[0];
				}while(!identListTree.m_rule.IsLambda());
				subTree = subTree.m_childRules[2];
			}while(!subTree.m_rule.IsLambda());
		}
	// 3. procedure to tableOfNames
		ProcedureAttributes attributes{params, returningType};
		InsertToTableIfUndefinedOrThrowException(io_tableOfNames, {id, &attributes}, idToken);
	// 4. Step inside to procedure
		if (m_childRules[0].m_childRules.back().m_childRules[0] == "block"){
			m_childRules[0].m_childRules.back().m_childRules[0].DefinitionProcess(io_tableOfNames, procName);
		}else{
			m_childRules[0].m_childRules.back().m_childRules[1].DefinitionProcess(io_tableOfNames, procName);
		}
	}
}
void ParseTree::UsageCheckProcess(TableOfNames& io_tableOfNames, const std::string i_currentBlock){
	/*TODO:
	 * 1. Check module and procedure ending id --- done in DefinitionProcess
	 * 2. For each id in statement part check if it included to table of name
	 * 3. Check if function call agree function specification
	 * 4*. Type agreement check.
	 */
	if (*this == "program"){ //go to the main module block
		TToken moduleId = this->m_childRules[0].m_childRules[0].m_rule.getRightPart()[1].getAssociatedToken();
		m_childRules[0].m_childRules[1].UsageCheckProcess(io_tableOfNames, moduleId.getLexeme());
	}else if (*this == "block"){ // recursion for block's declaration and go to the statement part
		if (m_childRules[0] == "declarationparts"){
			auto subTree = *this;
			do{
				subTree = subTree.m_childRules[0];
				if (subTree.m_childRules[0].m_childRules[0] == "proceduredeclaration")
					subTree.m_childRules[0].m_childRules[0].UsageCheckProcess(io_tableOfNames, i_currentBlock);
				subTree = subTree.m_childRules[1];
			}while(!subTree.m_rule.IsLambda());
			if (m_childRules[1].m_childRules.size() != 0)
				m_childRules[1].m_childRules[0].UsageCheckProcess(io_tableOfNames, i_currentBlock);
		}

		if (m_childRules[0] == "statementpart"){
			m_childRules[0].UsageCheckProcess(io_tableOfNames, i_currentBlock);
		}
	}else if (*this == "proceduredeclaration"){
		TToken idToken = m_rule.getRightPart()[1].getAssociatedToken();
		ParseTree procBody{};
		if (m_childRules[0].m_childRules[0] == "fctmbprocedurebody"){
			procBody = m_childRules[0].m_childRules[0];
		}else{
			procBody = m_childRules[0].m_childRules[1];
		}

		if (procBody.m_childRules[0] == "block"){
			procBody.m_childRules[0].UsageCheckProcess(io_tableOfNames, idToken.getLexeme());
		}else{
			procBody.m_childRules[1].UsageCheckProcess(io_tableOfNames, idToken.getLexeme());
		}
	}else if (*this == "statementpart"){ //iterate statements
		auto subTree = *this;
		do{
			subTree = subTree.m_childRules[0];
			subTree.m_childRules[0].UsageCheckProcess(io_tableOfNames, i_currentBlock);
			subTree = subTree.m_childRules[1];
		}while(!subTree.m_rule.IsLambda());
	}else{ // recursive descent for statement tree (check each id)
		for (auto ruleElement : m_rule.getRightPart()){
			if (ruleElement.IsTerminal() && ruleElement.getTerminal() == TToken::TTokenClass::_id){
				TToken idToken = ruleElement.getAssociatedToken();
				if (!io_tableOfNames.IsDeclared({idToken.getLexeme(), i_currentBlock})){
					throw SemanticException{idToken, "is not declared!"};
				}
			}
		}
		for (auto& it : m_childRules)
			it.UsageCheckProcess(io_tableOfNames, i_currentBlock);
	}
}
TableOfNames ParseTree::SemanticAnalyze(){
	TableOfNames tableOfNames{};
	DefinitionProcess(tableOfNames);
	UsageCheckProcess(tableOfNames);
	return tableOfNames;
}

// code generation should not be part of a tree
// reasoning: it's not tree doing job on itself,
// but outer entity (some ICodeGenerator) doing tree traversal
// as of right now, it breaches S in SOLID
std::string ParseTree::GenerateCode(const TableOfNames& i_tableOfNames, ByteCode& code){
    switch(m_rule.m_number)
    {
    case 2: // module start
        code.emitCode("LABEL _MODULE_" + m_childRules[0].m_rule.m_rightPart[1].getAssociatedToken().getLexeme());
        if (m_childRules[1].m_rule.m_number == 5) {
            m_childRules[1].m_childRules[0].GenerateCode(i_tableOfNames, code);
            code.emitCode("LABEL _MODULESTART");
            m_childRules[1].m_childRules[1].GenerateCode(i_tableOfNames, code);
        } else {
            code.emitCode("LABEL _MODULESTART");
            m_childRules[1].m_childRules[0].GenerateCode(i_tableOfNames, code);
        }
        break;
    case 51: // procedure declaration
        code.emitCode("LABEL _PROCEDURE_" + m_rule.m_rightPart[1].getAssociatedToken().getLexeme());
        m_childRules[0].GenerateCode(i_tableOfNames, code);
        code.emitCode("RET");
        break;
    case 29: // bool literal
    case 31: // string literal, not working
    case 34: // int literal
    case 35: // real literal
        return m_rule.m_rightPart[0].getAssociatedToken().getLexeme();
    case 28: // signed variable or literal
    {
        auto sign = m_childRules[0].m_rule.m_rightPart[0].getAssociatedToken().getLexeme();
        auto number = m_childRules[1].GenerateCode(i_tableOfNames, code);
        return code.emitCode(sign + " 0 " + number);
    }
    case 79: // variable
    {
        auto id = m_rule.m_rightPart[0].getAssociatedToken().getLexeme();
        if (m_childRules[0].m_rule.IsLambda()) return id;
        // array indeces
        auto indexExpr = m_childRules[0].m_childRules[0];//nIndices
        auto rest = m_childRules[0].m_childRules[1];//nVar1
        while (true) {
            int index = 0;
            std::string last;
            while (true) {
                auto expr = indexExpr.m_childRules[0].GenerateCode(i_tableOfNames, code);
                auto prev = code.emitCode("BOUNDS " + id + " " + std::to_string(index));
                if (index) {
                    prev = code.emitCode("* " + expr + " " + prev);
                    last = code.emitCode("+ " + last + " " + prev);
                } else {
                    last = expr;
                }
                index++;
                if (indexExpr.m_childRules[1].m_rule.IsLambda()) break;
                indexExpr = indexExpr.m_childRules[1].m_childRules[0];
            }
            id = code.emitCode("ADDR " + id + " " + last);
            if (rest.m_rule.IsLambda()) break;
            indexExpr = rest.m_childRules[0];
            rest = rest.m_childRules[1];
        }
        return id;
    }
    case 78: // assignment
    {
        auto varName = m_childRules[0].GenerateCode(i_tableOfNames, code);
        auto varExpr = m_childRules[1].GenerateCode(i_tableOfNames, code);
        return code.emitCode("= " + varName + " " + varExpr);
    }
    case 85: // expression
    {
        auto leftRelationPart = m_childRules[0].GenerateCode(i_tableOfNames, code);
        if (m_childRules[1].m_rule.IsLambda())
            return leftRelationPart;
        auto op = m_childRules[1].m_childRules[0].m_childRules[0].m_rule.m_rightPart[0].getAssociatedToken().getLexeme();
        auto rightRelationPart = m_childRules[1].m_childRules[0].m_childRules[1].GenerateCode(i_tableOfNames, code);
        return code.emitCode(op + " " + leftRelationPart + " " + rightRelationPart);
    }
    case 89: // "simple"/addition expression
    {
        auto leftPart = m_childRules[0]/*.m_childRules[0]*/.GenerateCode(i_tableOfNames, code);
        if (m_childRules[1].m_rule.IsLambda())
            return leftPart;
        auto rightPart = m_childRules[1].m_childRules[0].m_childRules[1].GenerateCode(i_tableOfNames, code);
        auto op = m_childRules[1].m_childRules[0].m_childRules[0].m_rule.m_rightPart[0].getAssociatedToken().getLexeme();
        return code.emitCode(op + " " + leftPart + " " + rightPart);
    }
    case 90: // signed expressions
    {
        auto sign = m_childRules[0].m_rule.m_rightPart[0].getAssociatedToken().getLexeme();
        auto expr = m_childRules[1].GenerateCode(i_tableOfNames, code);
        auto rightPart = m_childRules[2].m_childRules[0].m_childRules[1].GenerateCode(i_tableOfNames, code);
        auto op = m_childRules[2].m_childRules[0].m_childRules[0].m_rule.m_rightPart[0].getAssociatedToken().getLexeme();
        auto leftPart = code.emitCode(sign + " 0 " + expr);
        return code.emitCode(op + " " + leftPart + " " + rightPart);
    }
        break;
    case 96: // multiplication expression
    {
        auto leftPart = m_childRules[0]/*.m_childRules[0].m_childRules[0]*/.GenerateCode(i_tableOfNames, code);
        if (m_childRules[1].m_rule.IsLambda())
            return leftPart;
        auto rightPart = m_childRules[1].m_childRules[0].m_childRules[1].GenerateCode(i_tableOfNames, code);
        auto op = m_childRules[1].m_childRules[0].m_childRules[0].m_rule.m_rightPart[0].getAssociatedToken().getLexeme();
        return code.emitCode(op + " " + leftPart + " " + rightPart);
    }
    case 100: // number in multiplication
    {
        auto node = m_childRules[0];
        while (node.m_childRules.size() != 0)
            node = node.m_childRules[0];
        return node.GenerateCode(i_tableOfNames, code);
    }
        //return m_childRules[0].m_childRules[0].GenerateCode(i_tableOfNames, code);
    case 102: // var in multiplication
        return m_childRules[0].GenerateCode(i_tableOfNames, code);
    case 125: // if
    {
        if (m_childRules[2].m_rule.m_number == 126){ // short if
            auto labelAfter = code.getNextLabel();
            auto expr = m_childRules[0].GenerateCode(i_tableOfNames, code);
            code.emitCode("IFFALSE " + expr + " " + labelAfter);
            m_childRules[1].GenerateCode(i_tableOfNames, code);
            code.emitCode("LABEL " + labelAfter);
        } else if (m_childRules[2].m_rule.m_number == 128) { // long if
            auto labelAfter = code.getNextLabel();
            auto labelElse = code.getNextLabel();
            auto expr = m_childRules[0].GenerateCode(i_tableOfNames, code);
            code.emitCode("IFFALSE " + expr + " " + labelElse);
            m_childRules[1].GenerateCode(i_tableOfNames, code);
            code.emitCode("GOTO " + labelAfter);
            code.emitCode("LABEL " + labelElse);
            m_childRules[2].m_childRules[0].m_childRules[0].GenerateCode(i_tableOfNames, code);
            code.emitCode("LABEL " + labelAfter);
        } else if (m_childRules[2].m_rule.m_number == 127) { // elsif
            auto labelAfter = code.getNextLabel();
            auto expr = m_childRules[0].GenerateCode(i_tableOfNames, code);
            code.emitCode("IFFALSE " + expr + " " + labelAfter);
            m_childRules[1].GenerateCode(i_tableOfNames, code);
            code.emitCode("GOTO " + labelAfter);
            auto elsif = m_childRules[2].m_childRules[0];
            while (!elsif.m_rule.IsLambda()) {
                auto labelElse = code.getNextLabel();
                auto expr = elsif.m_childRules[0].GenerateCode(i_tableOfNames, code);
                code.emitCode("IFFALSE " + expr + " " + labelElse);
                elsif.m_childRules[1].GenerateCode(i_tableOfNames, code);
                code.emitCode("GOTO " + labelAfter);
                code.emitCode("LABEL " + labelElse);
                elsif = elsif.m_childRules[2];
            }
            //m_childRules[2].m_childRules[1].GenerateCode(i_tableOfNames, code);
            if (!m_childRules[2].m_childRules[1].m_rule.IsLambda())
                m_childRules[2].m_childRules[1].m_childRules[0].m_childRules[0].GenerateCode(i_tableOfNames, code);
            code.emitCode("LABEL " + labelAfter);
        }
    }
        break;
    case 135: // for
    {
        auto labelForStart = code.getNextLabel();
        auto labelForEnd = code.getNextLabel();
        auto iterator = m_childRules[0].GenerateCode(i_tableOfNames, code);
        auto start = m_childRules[1].GenerateCode(i_tableOfNames, code);
        auto end = m_childRules[2].GenerateCode(i_tableOfNames, code);
        code.emitCode("= " + iterator + " " + start);
        code.emitCode("LABEL " + labelForStart);
        auto condition = code.emitCode("< " + iterator + " " + end);
        code.emitCode("IFFALSE " + condition + " " + labelForEnd);
        m_childRules[3].GenerateCode(i_tableOfNames, code);
        code.emitCode("GOTO " + labelForStart);
        code.emitCode("LABEL " + labelForEnd);
    }
        break;
    case 104: // function call
    case 122: // procedure call
    {
        auto funcName = m_rule.m_rightPart[0].getAssociatedToken().getLexeme();
        auto parameters = m_childRules[0].m_childRules[0].m_childRules[0];
        if (m_rule.m_number == 122) parameters = parameters.m_childRules[0];
        while (true) {
            auto param = parameters.m_childRules[0].m_childRules[0].GenerateCode(i_tableOfNames, code);
            code.emitCode("PUSH " + param);
            if (parameters.m_childRules[1].m_rule.IsLambda()) break;
            parameters = parameters.m_childRules[1].m_childRules[0];
        }
        code.emitCode("CALL _PROCEDURE_" + funcName);
        if (m_rule.m_number == 104)
            return code.emitCode("POP");
    }
        break;
    default:
        if (m_childRules.size() == 1) return m_childRules[0].GenerateCode(i_tableOfNames, code);
        for (auto& subtree : m_childRules)
            subtree.GenerateCode(i_tableOfNames, code);
        break;
    }
    return "";
}
