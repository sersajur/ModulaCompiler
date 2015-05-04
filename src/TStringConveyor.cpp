/*
 * TStringConveyor.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: sersajur
 */

#include "TStringConveyor.h"

TStringConveyor::TStringConveyor():
m_SourceString(NULL), m_SourceConveyor(NULL),
m_UseStringAsASourceFlag(false), m_ForwardPassFlag(false){

}

//TStringConveyor::~TStringConveyor(){ ;}
char TStringConveyor::getSymbol(){
	m_ForwardPassFlag = true;
	return ProcessSymbol(getSymbolFromSource());
}
/************************************************************************************/
void TStringConveyor::ungetSymbol(char i_ch){
	m_ForwardPassFlag = false;
	ungetToSource(ProcessSymbol(i_ch));
}
/************************************************************************************/
TStringConveyor& TStringConveyor::operator>>(vector<char>& i_DestinationVector){
	char ch = getSymbol();
	i_DestinationVector.push_back(ch);
	return *this;
}
/************************************************************************************/
TStringConveyor& TStringConveyor::operator>>(TStringConveyor& io_StringConveyorUser){
	io_StringConveyorUser.m_SourceConveyor = this;
	io_StringConveyorUser.m_UseStringAsASourceFlag = false;
	io_StringConveyorUser.m_ForwardPassFlag = true;
	return io_StringConveyorUser;
}
/************************************************************************************/
TStringConveyor& TStringConveyor::operator<<(vector<char>& i_DestinationVector){
	if (!i_DestinationVector.empty()){
		ungetSymbol(i_DestinationVector.back());
		i_DestinationVector.pop_back();
	}
	else
		ungetSymbol(static_cast<char>(0));
	return *this;
}
/************************************************************************************/
TStringConveyor& TStringConveyor::operator<<(TStringConveyor& io_StringConveyorUser){
	io_StringConveyorUser.m_SourceConveyor = this;
	io_StringConveyorUser.m_UseStringAsASourceFlag = false;
	io_StringConveyorUser.m_ForwardPassFlag = false;
	return io_StringConveyorUser;
}
/************************************************************************************/
/* Protected: */
char TStringConveyor::getSymbolFromSource(){
	char o_symbol;
	if (IsSourceAString()){
		o_symbol = m_SourceString->c_str()[0];
		if (m_SourceString->length())
			m_SourceString->erase(m_SourceString->begin());
		}
	else
		o_symbol = m_SourceConveyor->getSymbol();
	return o_symbol;
}
/************************************************************************************/
void TStringConveyor::ungetToSource(char i_symbol){
	if (IsSourceAString()){
		if (static_cast<int>(i_symbol) != 0){
			m_SourceString->insert(m_SourceString->begin(), i_symbol);
		}
	}
	else
		m_SourceConveyor->ungetSymbol(i_symbol);
}
/************************************************************************************/
void TStringConveyor::ungetToSource(string i_symbols){
	while (!i_symbols.empty()){
		ungetToSource(i_symbols.back());
		i_symbols.pop_back();
	}
}
/************************************************************************************/
void TStringConveyor::ungetToSource(vector<char>& io_buf, int i_backStepNumber){
	for (; i_backStepNumber; i_backStepNumber--){
		ungetToSource(io_buf.back());
		io_buf.pop_back();
	}
}
/************************************************************************************/
void TStringConveyor::ungetToSource(const vector<char>::iterator i_begin, const vector<char>::iterator i_end){
	for (auto it = i_end - 1; it >= i_begin; --it){
		ungetToSource(*it);
	}

}
/************************************************************************************/
char TStringConveyor::ProcessSymbol(char i_Symbol){
	return i_Symbol;
}
/************************************************************************************/
/* Friends: */
TStringConveyor& operator>>(string& i_SourceString, TStringConveyor& io_StringConveyor){
	io_StringConveyor.m_SourceString = &i_SourceString;
	io_StringConveyor.m_UseStringAsASourceFlag = true;
	io_StringConveyor.m_ForwardPassFlag = true;
	return io_StringConveyor;
}
/************************************************************************************/
TStringConveyor& operator<<(string& i_SourceString, TStringConveyor& io_StringConveyor){
	io_StringConveyor.m_SourceString = &i_SourceString;
	io_StringConveyor.m_UseStringAsASourceFlag = true;
	io_StringConveyor.m_ForwardPassFlag = false;
	return io_StringConveyor;
}
