/*
 * NameAttributes.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: sersajur
 */
#include "NameAttributes.h"

const std::map<NameAttributes::NameType, std::string> NameAttributes::NameTypeString{
	{NameAttributes::NameType::Module, "Module"},
	{NameAttributes::NameType::Procedure, "Procedure"},
	{NameAttributes::NameType::Array, "Array"},
	{NameAttributes::NameType::Variable, "Variable"},
	{NameAttributes::NameType::Constant, "Constant"}
};
const std::map<NameAttributes::Type, std::string> NameAttributes::TypeString{
	{NameAttributes::Type::Boolean, "Boolean"},
	{NameAttributes::Type::Integer, "Integer"},
	{NameAttributes::Type::Real, "Real"},
	{NameAttributes::Type::Char, "Char"},
	{NameAttributes::Type::String, "String"},
	{NameAttributes::Type::Void, "Void"}
};
NameAttributes::Type NameAttributes::TokenTypeToType(const TToken::TTokenClass& i_v){
	NameAttributes::Type type{};
	switch(i_v){
	case TToken::TTokenClass::_Boolean:
	case TToken::TTokenClass::_boolval:
		type = NameAttributes::Type::Boolean;
		break;
	case TToken::TTokenClass::_strval:
		type = NameAttributes::Type::String;
		break;
	case TToken::TTokenClass::_intval:
	case TToken::TTokenClass::_integer:
		type = NameAttributes::Type::Integer;
		break;
	case TToken::TTokenClass::_realval:
	case TToken::TTokenClass::_real:
		type = NameAttributes::Type::Real;
		break;
	case TToken::TTokenClass::_char:
		type = NameAttributes::Type::Char;
		break;
	default:
		type = NameAttributes::Type::Void;
		break;
	}
	return type;
}

std::string ModuleAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
std::string ProcedureAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
std::string ArrayAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
std::string VariableAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
std::string ConstantAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
