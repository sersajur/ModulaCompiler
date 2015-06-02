/*
 * NameAttributes.h
 *
 *  Created on: 1 черв. 2015
 *      Author: sersajur
 */

#ifndef NAMEATTRIBUTES_H_
#define NAMEATTRIBUTES_H_

#include <vector>
#include <string>
#include <map>
#include "TToken.h"

using std::vector;
using std::string;
using std::map;

class NameAttributes{

public:
	enum class NameType{
		Module, Procedure, Array, Variable, Constant
	};
	enum class Type{
		Integer, Real, Char, String, Boolean, Void
	};
	virtual NameType getNameType() const = 0;
	virtual std::string getPrintableText() const = 0;
	virtual ~NameAttributes(){};
protected:
	static const map<NameType, string> NameTypeString;
	static const map<Type, string> TypeString;
};

class ModuleAttributes: public NameAttributes{
public:
	ModuleAttributes(){};
	virtual ~ModuleAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Module;}
	string getPrintableText() const override;
};

class ProcedureAttributes: public NameAttributes{
public:
	ProcedureAttributes(): m_returningtype{NameAttributes::Type::Void}, m_inputParametersType{} {}
	virtual ~ProcedureAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Procedure;}
public:
	ProcedureAttributes(const vector<NameAttributes::Type>& i_inputParamsType, const NameAttributes::Type& i_returningType = NameAttributes::Type::Void):
		m_returningtype{i_returningType}, m_inputParametersType{i_inputParamsType} {}
	string getPrintableText() const override;
private:
	NameAttributes::Type m_returningtype;
	vector<NameAttributes::Type> m_inputParametersType;

};

class ArrayAttributes: public NameAttributes{
public:
	ArrayAttributes(); // TODO: depricated
	virtual ~ArrayAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Array;}
public:
	struct TDimBoundary{
		unsigned low_edge;
		unsigned high_edge;
	};
	ArrayAttributes(const NameAttributes::Type& i_type, const vector<TDimBoundary>& i_dimBoundaties):
		m_type{i_type}, m_dimBoundaries{i_dimBoundaties} {}
	string getPrintableText() const override;
private:
	NameAttributes::Type m_type;
	vector<TDimBoundary> m_dimBoundaries;
};

class VariableAttributes: public NameAttributes{
public:
	VariableAttributes();
	virtual ~VariableAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Variable;}
public:
	VariableAttributes(const NameAttributes::Type& i_type):
		m_type{i_type} {}
	string getPrintableText() const override;
private:
	NameAttributes::Type m_type;
};

class ConstantAttributes: public NameAttributes{
public:
	ConstantAttributes();
	virtual ~ConstantAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Constant;}
public:
	ConstantAttributes(const NameAttributes::Type& i_type, const TToken::TTokenValue& i_value):
		m_type{i_type}, m_value{i_value} {}
	string getPrintableText() const override;
private:
	NameAttributes::Type m_type;
	TToken::TTokenValue m_value;
};

#endif /* NAMEATTRIBUTES_H_ */
