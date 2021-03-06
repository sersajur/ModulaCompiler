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

struct TNameId{
	std::string name;
	std::string blockName;
	bool operator<(const TNameId& compId)const{
		return ((blockName == compId.blockName) ? (name < compId.name) : (blockName < compId.blockName));
	}
};

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

	static Type TokenTypeToType(const TToken::TTokenClass& i_v);
protected:
	static const std::map<NameType, std::string> NameTypeString;
	static const std::map<Type, std::string> TypeString;
};

class ModuleAttributes: public NameAttributes{
public:
	ModuleAttributes(){};
	virtual ~ModuleAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Module;}
	std::string getPrintableText() const override;
};

class ProcedureAttributes: public NameAttributes{
public:
	ProcedureAttributes(): m_returningtype{NameAttributes::Type::Void}, m_inputParameters{} {}
	virtual ~ProcedureAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Procedure;}
public:
	ProcedureAttributes(const std::vector<TNameId>& i_inputParams, const NameAttributes::Type& i_returningType = NameAttributes::Type::Void):
		m_returningtype{i_returningType}, m_inputParameters{i_inputParams} {}
	std::string getPrintableText() const override;
	std::vector<TNameId> getDesiredInput()const { return m_inputParameters; }
	Type getReturningType()const { return m_returningtype; }
private:
	NameAttributes::Type m_returningtype;
	std::vector<TNameId> m_inputParameters;

};

class ArrayAttributes: public NameAttributes{
public:
	ArrayAttributes(); // TODO: depricated
	virtual ~ArrayAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Array;}
public:
	typedef std::pair<int, int> TDimBoundary;
	ArrayAttributes(const NameAttributes::Type& i_type, const std::vector<TDimBoundary>& i_dimBoundaties):
		m_type{i_type}, m_dimBoundaries{i_dimBoundaties} {}
	std::string getPrintableText() const override;
	std::vector<TDimBoundary> getDimBoundaries()const {return m_dimBoundaries;}
private:
	NameAttributes::Type m_type;
	std::vector<TDimBoundary> m_dimBoundaries;
};

class VariableAttributes: public NameAttributes{
public:
	VariableAttributes();
	virtual ~VariableAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Variable;}
public:
	VariableAttributes(const NameAttributes::Type& i_type):
		m_type{i_type} {}
	std::string getPrintableText() const override;
private:
	NameAttributes::Type m_type;
};

class ConstantAttributes: public NameAttributes{
public:
	ConstantAttributes();
	virtual ~ConstantAttributes(){};
	NameAttributes::NameType getNameType() const override {return NameAttributes::NameType::Constant;}
public:
	ConstantAttributes(const NameAttributes::Type& i_type, const TToken::TTokenValue& i_value);
	ConstantAttributes(const ConstantAttributes& i_attr);
	std::string getPrintableText() const override;
private:
	NameAttributes::Type m_type;
	TToken::TTokenValue m_value;

	friend class TableOfNames;
};

#endif /* NAMEATTRIBUTES_H_ */
