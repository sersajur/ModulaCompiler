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
	std::string o_str{NameAttributes::NameTypeString.find(getNameType())->second};
	o_str += "\t(";
	if (m_inputParameters.size() != 0){
		for (auto& it : m_inputParameters){
			o_str += ' ' + it.name + ',';
		}
		o_str.pop_back();
	}
	o_str += " ): " + NameAttributes::TypeString.find(m_returningtype)->second;
	return o_str;
}
std::string ArrayAttributes::getPrintableText() const{
	std::string o_str{NameAttributes::NameTypeString.find(getNameType())->second};
	o_str += "\t(";
	for (auto& it : m_dimBoundaries){
		o_str += ' ' + std::to_string(it.first) + ':' + std::to_string(it.second) + ',';
	}
	o_str.pop_back();
	o_str += " ): " + NameAttributes::TypeString.find(m_type)->second;
	return o_str;
}
std::string VariableAttributes::getPrintableText() const{
	std::string o_str{NameAttributes::NameTypeString.find(getNameType())->second};
	o_str += "\t: " + NameAttributes::TypeString.find(m_type)->second;
	return o_str;
}
ConstantAttributes::ConstantAttributes(const NameAttributes::Type& i_type, const TToken::TTokenValue& i_value):
	m_type{i_type}{
	switch(m_type){
	case Type::Boolean:
		m_value.asBool = i_value.asBool;
		break;
	case Type::Integer:
		m_value.asInt = i_value.asInt;
		break;
	case Type::Real:
		m_value.asReal = i_value.asReal;
		break;
	case Type::String:
		m_value.asString = i_value.asString;
		break;
	default:
		break;
	}
}
ConstantAttributes::ConstantAttributes(const ConstantAttributes& i_attr):
	m_type{i_attr.m_type}{
	switch(m_type){
	case Type::Boolean:
		m_value.asBool = i_attr.m_value.asBool;
		break;
	case Type::Integer:
		m_value.asInt = i_attr.m_value.asInt;
		break;
	case Type::Real:
		m_value.asReal = i_attr.m_value.asReal;
		break;
	case Type::String:
		m_value.asString = i_attr.m_value.asString;
		break;
	default:
		break;
	}
}
std::string ConstantAttributes::getPrintableText() const{
	std::string o_str{NameAttributes::NameTypeString.find(getNameType())->second};
	o_str += '\t';
	switch(m_type){
	case Type::Boolean:
		o_str += std::to_string(m_value.asBool);
		break;
	case Type::Integer:
		o_str += std::to_string(m_value.asInt);
		break;
	case Type::Real:
		o_str += std::to_string(m_value.asReal);
		break;
	case Type::String:
		o_str += m_value.asString;
		break;
	default:
		break;
	}
	o_str += ": " + NameAttributes::TypeString.find(m_type)->second;
	return o_str;
}
