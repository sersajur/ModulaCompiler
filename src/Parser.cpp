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
Parser::Parser(const SyntaxGrammar& i_grammar):
	m_grammar{i_grammar}{

}
Parser::~Parser() {

}

void Parser::Configurate(){
	SyntaxRuleAtom
		nProgram{"program"},
		nModule{"module"},
		nModuleHeading{"moduleheading"},
		nBlock{"block"},
		nDeclarationParts1{"fctdeclarationparts"},
		nDeclarationParts{"declarationparts"},
		nDeclarationPart{"declarationpart"},
		nDeclarationPart1{"fctdeclarationpart"},
		nConstantDeclarations1{"fctconstantdeclarations"},
		nConstantDeclarations{"constantdeclarations"},
		nConstantDeclaration1{"fctconstantdeclaration"},
		nConstantDeclaration{"constantdeclaration"},
		nVariableDecalrations1{"fctvariabledeclarations"},
		nVariableDecalrations{"variabledeclarations"},
		nVariableDecalration1{"fctvariabledeclaration"},
		nVariableDecalration{"variabledeclaration"},
		nStatementPart{"statementpart"},
		nConstant{"constant"},
		nUnsignedConstant{"unsignedconstant"},
		nSign{"sign"},
		nNumber{"number"},
		nType{"type"},
		nBaseType{"basetype"},
		nIdentList{"identlist"},
		nIdentList1{"fctidentlist"},
		nArrayStructure{"arraystructure"},
		nIndexRangeList{"indexrangelist"},
		nIndexRange1{"fctindexrange"},
		nIndexRange{"indexrange"},
		nProcedureDeclaration{"proceduredeclaration"},
		nProcedureDeclaration1{"fctproceduredeclaration1"},
		nMbProcedureBody{"fctmbprocedurebody"},
		nMbFormalparameters{"mbformalparameters"},
		nMbResultType{"mbresulttype"},
		nSection1{"fctsection"},
		nSection{"section"},
		nMbSpec{"mbspec"},
		nFormalType{"formaltype"},
		nMbArray{"mbArray"},
		nIndexTypes{"indextypes"},
		nStatementSequence{"statementsequence"},
		nStatement1{"fctstatement"},
		nStatement{"statement"},
		nAssignment{"assignment"},
		nVariable{"variable"},
		nVariable1{"fctvar"},
		nIndices{"indices"},
		nExpression1{"fctexpr"},
		nExpression{"expression"},
		nSimpleExpression1{"fctsimpleexpression"},
		nSimpleExpression{"SimpleExpression"},
		nMbRelation{"mbrelation"},
		nTermAdd{"fcttermadd"},
		nMbSign{"mbsign"},
		nMbAddition{"mbaddition"},
		nTerm{"term"},
		nTermMul1{"fcttermmul"},
		nMbMultiplication{"mbmultiplication"},
		nFactor{"factor"},
		nFunctionCall{"functioncall"},
		nParameterlist{"parameterlist"},
		nParameters1{"fctparameters"},
		nParameters{"parameters"},
		nParameter1{"fctparameter"},
		nParameter{"parameter"},
		nMulOperator{"muloperator"},
		nAddOperator{"addoperator"},
		nRelation{"relation"},
		nProcedureCall{"procedurecall"},
		nMbParameterList{"mbparameterlist"},
		nIfStatement{"ifstatement"},
		nIfStatement1{"fctifstatement"},
		nMbElsifs1{"fctmbelsifs"},
		nMbElsifs{"mbelsifs"},
		nMbElsifs2{"fctmbelsifs1"},
		nMbElse{"mbelse"},
		nForStatement{"forstatement"},
		nMbSectionList{"mbsectionlist"},
		nFormalParameters{"formalparameters"};

	SyntaxRuleAtom
		tDot{TToken::TTokenClass::_dot},
		tComma{TToken::TTokenClass::_comma},
		tColom{TToken::TTokenClass::_colom},
		tSemicolom{TToken::TTokenClass::_semicolom},
		tOr{TToken::TTokenClass::_or},
		tAnd{TToken::TTokenClass::_and},
		tPlus{TToken::TTokenClass::_add},
		tMinus{TToken::TTokenClass::_sub},
		tMult{TToken::TTokenClass::_mul},
		tDiv{TToken::TTokenClass::_div},
		tEq{TToken::TTokenClass::_eq},
		tLe{TToken::TTokenClass::_le},
		tGe{TToken::TTokenClass::_ge},
		tAss{TToken::TTokenClass::_ass},
		tLPar{TToken::TTokenClass::_lbr},
		tRPar{TToken::TTokenClass::_rbr},
		tLIPar{TToken::TTokenClass::_lbrind},
		tRIPar{TToken::TTokenClass::_rbrind},
		tOf{TToken::TTokenClass::_of},
		tArray{TToken::TTokenClass::_array},
		tInteger{TToken::TTokenClass::_integer},
		tChar{TToken::TTokenClass::_char},
		tReal{TToken::TTokenClass::_real},
		tBoolean{TToken::TTokenClass::_Boolean},
		tConst{TToken::TTokenClass::_const},
		tVar{TToken::TTokenClass::_var},
		tProcedure{TToken::TTokenClass::_procedure},
		tBegin{TToken::TTokenClass::_begin},
		tEnd{TToken::TTokenClass::_end},
		tModule{TToken::TTokenClass::_module},
		tIf{TToken::TTokenClass::_if},
		tThen{TToken::TTokenClass::_then},
		tElsif{TToken::TTokenClass::_elsif},
		tElse{TToken::TTokenClass::_else},
		tFor{TToken::TTokenClass::_for},
		tValInt{TToken::TTokenClass::_intval},
		tValReal{TToken::TTokenClass::_realval},
		tValStr{TToken::TTokenClass::_strval},
		tValBool{TToken::TTokenClass::_boolval},
		tId{TToken::TTokenClass::_id};

	m_grammar = SyntaxGrammar{nProgram};
	m_grammar
	(nProgram, 			{nModule, tDot})
	(nModule, 		  	{nModuleHeading, nBlock,tId})
	(nModuleHeading, 	{tModule, tId, tSemicolom})
	(nBlock, 			{tEnd})
	(nBlock, 			{nDeclarationParts, nDeclarationParts1})
	(nBlock, 			{nStatementPart, tEnd})
	(nDeclarationParts1,{tEnd})
	(nDeclarationParts1,{nStatementPart, tEnd})
	(nDeclarationParts, {nDeclarationPart, nDeclarationPart1})
	(nDeclarationPart1, {nDeclarationParts})
	(nDeclarationPart1, {})
	(nDeclarationPart, 	{tConst,nConstantDeclarations1})
	(nDeclarationPart, 	{tVar,  nVariableDecalrations1})
	(nDeclarationPart, 	{nProcedureDeclaration, tSemicolom})
	(nConstantDeclarations1, {nConstantDeclarations})
	(nConstantDeclarations1, {})
	(nVariableDecalrations1, {nVariableDecalrations})
	(nVariableDecalrations1, {})
	(nConstantDeclarations,  {nConstantDeclaration, tSemicolom, nConstantDeclaration1})
	(nConstantDeclaration1,  {nConstantDeclarations})
	(nConstantDeclaration1,  {})
	
	(nVariableDecalrations,  {nVariableDecalration, tSemicolom, nVariableDecalration1})
	(nVariableDecalration1,  {nVariableDecalrations})
	(nVariableDecalration1,  {})
	
	(nStatementPart,	{tBegin, nStatementSequence})
	(nConstantDeclaration, 	{tId, tEq, nConstant})
	(nConstant, {nUnsignedConstant})
	(nConstant, {nSign, nNumber})
	(nUnsignedConstant, {tValBool})
	(nUnsignedConstant, {nNumber})
	(nUnsignedConstant, {tValStr})
	(nSign, 	{tPlus})
	(nSign, 	{tMinus})
	(nNumber, 	{tValInt})
	(nNumber, 	{tValReal})
	(nType, 	{nBaseType})
	(nType, 	{nArrayStructure})
	(nBaseType, {tBoolean})
	(nBaseType, {tInteger})
	(nBaseType, {tReal})
	(nBaseType, {tChar})
	(nIdentList, {tId, nIdentList1})
	(nIdentList1, {})
	(nIdentList1,{tComma,nIdentList})
	(nArrayStructure, {tArray, nIndexRangeList, tOf, nBaseType})
	(nIndexRangeList, {nIndexRange, nIndexRange1})
	(nIndexRange1, {tComma, nIndexRangeList})
	(nIndexRange1, {})
	(nIndexRange, {nConstant, tColom, nConstant})
	(nVariableDecalration, {nIdentList, tColom, nType})
	(nProcedureDeclaration,{tProcedure, tId, nProcedureDeclaration1})
	(nProcedureDeclaration1, {nMbProcedureBody})
	(nProcedureDeclaration1, {nMbFormalparameters, nMbProcedureBody})
	(nMbProcedureBody,   {nBlock, tId})
	(nMbProcedureBody,   {nMbResultType, nBlock, tId})
	(nMbFormalparameters,{tLPar, nMbSectionList, tRPar})
	(nMbSectionList, {nFormalParameters})
	(nMbSectionList, {})
	(nMbResultType, {tColom, nBaseType})
	(nFormalParameters,{nSection, nSection1})
	(nSection1, {tSemicolom, nFormalParameters})
	(nSection1, {})
	(nSection,  {nIdentList, tColom, nFormalType})
	(nSection,  {nMbSpec, nIdentList, tColom, nFormalType})
	(nMbSpec,   {tConst})
	(nMbSpec,   {tVar})
	(nFormalType, {nBaseType})
	(nFormalType, {nMbArray, nBaseType})
	(nMbArray, {tArray,nIndexTypes,tOf})
	(nIndexTypes, {nIdentList})
	(nStatementSequence, {nStatement,nStatement1})
	(nStatement1,{tSemicolom,nStatementSequence})
	(nStatement1,{})
	(nStatement, {nAssignment})
	(nStatement, {nProcedureCall})
	(nStatement, {nIfStatement})
	(nStatement, {nForStatement})
	(nAssignment,{nVariable, tAss, nExpression})
	(nVariable,  {tId, nVariable1})
	(nVariable1, {tLIPar, nIndices, tRIPar, nVariable1})
	(nVariable1, {})
	(nIndices, {nExpression, nExpression1})
	(nExpression1, {tComma, nIndices})
	(nExpression1, {})
	(nExpression,  {nSimpleExpression, nSimpleExpression1})
	(nSimpleExpression1, {nMbRelation})
	(nSimpleExpression1, {})
	(nMbRelation, {nRelation, nSimpleExpression})
	(nSimpleExpression, {nTerm, nTermAdd})
    (nSimpleExpression, {nMbSign, nTerm, nTermAdd})
	(nTermAdd, {nMbAddition})
	(nTermAdd, {})
	(nMbSign,  {tPlus})
	(nMbSign,  {tMinus})
    (nMbAddition, {nAddOperator, nSimpleExpression})
	(nTerm, {nFactor, nTermMul1})
	(nTermMul1, {nMbMultiplication})
	(nTermMul1, {})
    (nMbMultiplication, {nMulOperator, nTerm})
	(nFactor, {nUnsignedConstant})
	(nFactor, {nFunctionCall})
	(nFactor, {nVariable})
	(nFactor, {tLPar, nExpression, tRPar})
	(nFunctionCall, {tId, nParameterlist})
	(nParameterlist,{tLPar, nParameters1, tRPar})
	(nParameters1,  {nParameters})
	(nParameters1,  {})
	(nParameters,   {nParameter, nParameter1})
	(nParameter1,   {tComma, nParameters})
	(nParameter1,   {})
	(nParameter,    {nExpression})
	(nParameter,    {nVariable})
	(nMulOperator,  {tMult})
	(nMulOperator,  {tDiv})
	(nMulOperator,  {tAnd})
	(nAddOperator,  {tPlus})
	(nAddOperator,  {tMinus})
	(nAddOperator,  {tOr})
	(nRelation,     {tEq})
	(nRelation,     {tLe})
	(nRelation,     {tGe})
	(nProcedureCall,{tId, nMbParameterList})
	(nMbParameterList,{nParameterlist})
	(nMbParameterList,{})
	(nIfStatement,    {tIf, nExpression, tThen, nStatementSequence, nIfStatement1})
	(nIfStatement1,   {tEnd})
	(nIfStatement1,   {nMbElsifs, nMbElsifs1})
	(nIfStatement1,   {nMbElse, tEnd})
	(nMbElsifs1, {tEnd})
	(nMbElsifs1, {nMbElse, tEnd})
	(nMbElsifs,  {tElsif, nExpression, tThen, nStatementSequence, nMbElsifs2})
	(nMbElsifs2, {nMbElsifs})
	(nMbElsifs2, {})
	(nMbElse,    {tElse, nStatementSequence})
	(nForStatement, {tFor, nVariable, tEq, nExpression, tColom, nExpression, nStatementSequence, tEnd});
}
void Parser::setInput(const std::vector<TToken>& i_input){
	m_input = i_input;
}
ParseTree  Parser::Parse(){
	m_firstUnrecognized = m_currentInputTerminal = m_input.begin();
	ParseTree o_parseTree{};
	bool o_parseResult{Parse(m_grammar.getRuleBase(), o_parseTree)};

	if (m_firstUnrecognized != m_input.end())
		throw SyntaxException(*m_firstUnrecognized, "Unexpected token class");

	if ((m_currentInputTerminal != m_input.end()))
		throw SyntaxException(*m_currentInputTerminal, "Non-empty rest of tokens started from this one");

	if (!o_parseResult)
		throw SyntaxException(*m_currentInputTerminal, "There is no matched rules for tokens after this one");
	return o_parseTree;
}
ParseTree Parser::Parse(const std::vector<TToken>& i_input){
	m_input = i_input;
	return Parser::Parse();
}
bool Parser::Parse(const SyntaxRuleAtom i_syntaxAtom, ParseTree& o_parseTree){
	if (i_syntaxAtom.IsTerminal()){
		return CheckNextTerminal(i_syntaxAtom.getTerminal());
	}

	Rule matchedRule{};
	std::vector<ParseTree> childNodes{};
	auto savedCurrentPosition = m_currentInputTerminal;
	auto ruleCandidates = m_grammar.getMatchedRules(i_syntaxAtom);
	for (auto& currentRule : ruleCandidates){ // Loop possible rules
		if (currentRule.IsLambda() && !matchedRule.IsInit()){
			matchedRule = currentRule;
			continue;
		}

		bool isRuleParsed{false};
		m_currentInputTerminal = savedCurrentPosition;
		for (auto& syntaxAtom : currentRule.getRightPart()){ //Loop right rule part
			ParseTree childTree{};
			if (!(isRuleParsed = Parse(syntaxAtom, childTree))){
				childNodes.clear();
				break;
			}
			if (!syntaxAtom.IsTerminal())
				childNodes.push_back(childTree);
		}
		if (isRuleParsed){
			matchedRule = currentRule;
			break;
		}
	}

	if (matchedRule.IsLambda()){
		m_currentInputTerminal = savedCurrentPosition;
	}

	if (matchedRule.IsInit()){
		o_parseTree.setNode(matchedRule);
		o_parseTree.setChildren(childNodes);
	}

//Debug:
	cout << "##########################################################" << endl;
	cout << "Current terminal: " ;
	if (savedCurrentPosition!=m_input.end())
		cout << *savedCurrentPosition << endl;
	else
		cout << "_eof" << endl;
	cout << "Current syn atom: " << i_syntaxAtom << endl;
	cout << "Rule candidates : " << endl;
	for (auto& rule : ruleCandidates)
		cout << "\t" << rule << endl;
	cout << "Chasen one      : ";
	if (matchedRule.IsInit())
		cout << matchedRule << endl;
	else
		cout << "none" <<endl;

	return matchedRule.IsInit();
}
bool Parser::CheckNextTerminal(const TToken::TTokenClass& i_tokenClassToBeCompared){
	if (m_currentInputTerminal == m_input.end())
		return false;

	bool isEqual{m_currentInputTerminal->getClass() == i_tokenClassToBeCompared};
	if (isEqual){
		m_currentInputTerminal++;
		if (m_firstUnrecognized < m_currentInputTerminal)//
			m_firstUnrecognized = m_currentInputTerminal;
	}

	return isEqual;
}
//void Parser::PrintTree(ostream& i_os, const ParseTree& i_parseTree){
//	Parser::PrintTree(i_os, i_parseTree, 0);
//}
//void Parser::PrintTree(ostream& i_os, const ParseTree& i_parseTree, const unsigned i_marginNum){
//	for (auto counter = i_marginNum; counter > 0; counter--)
//		i_os << '\t';
//	i_os << i_parseTree.rule << endl;
//	for (auto& it : i_parseTree.childRules)
//		Parser::PrintTree(i_os, it, i_marginNum+1);
//}
