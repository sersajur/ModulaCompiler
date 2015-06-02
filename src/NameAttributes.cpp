/*
 * NameAttributes.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: sersajur
 */
#include "NameAttributes.h"


const std::map<NameAttributes::NameType, string> NameAttributes::NameTypeString{
	{NameAttributes::NameType::Module, "Module"},
	{NameAttributes::NameType::Procedure, "Procedure"},
	{NameAttributes::NameType::Array, "Array"},
	{NameAttributes::NameType::Variable, "Variable"},
	{NameAttributes::NameType::Constant, "Constant"}
};
const std::map<NameAttributes::Type, string> NameAttributes::TypeString{
	{NameAttributes::Type::Boolean, "Boolean"},
	{NameAttributes::Type::Integer, "Integer"},
	{NameAttributes::Type::Real, "Real"},
	{NameAttributes::Type::Char, "Char"},
	{NameAttributes::Type::String, "String"},
	{NameAttributes::Type::Void, "Void"}
};


string ModuleAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
string ProcedureAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
string ArrayAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
string VariableAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
string ConstantAttributes::getPrintableText() const{
	return NameAttributes::NameTypeString.find(getNameType())->second;
}
