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
