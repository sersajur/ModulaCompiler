/*
 * TableOfNames.cpp
 *
 *  Created on: 1 черв. 2015
 *      Author: sersajur
 */

#include "TableOfNames.h"

TableOfNames::TableOfNames() {
	// TODO Auto-generated constructor stub

}

TableOfNames::~TableOfNames() {
	for (auto& it : m_nameRecords)
		delete it.second;
}
TableOfNames::TableOfNames(const TableOfNames& i_srcTable){
	for (auto it : i_srcTable.m_nameRecords){
		this->Insert({it.first, it.second});
	}
}
TableOfNames& TableOfNames::operator=(const TableOfNames& i_srcTable){
	for (auto it : i_srcTable.m_nameRecords){
		this->Insert({it.first, it.second});
	}
	return *this;
}

bool TableOfNames::IsDeclared(const TNameId& i_id) const{
	return m_nameRecords.find(i_id) != m_nameRecords.end();
}
const TableOfNames::TRecord TableOfNames::getRecord(const TNameId& i_nameId) const{
	const auto& it = m_nameRecords.find(i_nameId);
	return {i_nameId, it->second};
}
void TableOfNames::Insert(const TRecord& i_record){
	NameAttributes* p_newAttribute{};
	switch (i_record.attributes->getNameType()){
	case NameAttributes::NameType::Module:
		p_newAttribute = new ModuleAttributes{*dynamic_cast<ModuleAttributes*>(i_record.attributes)};
		break;
	case NameAttributes::NameType::Procedure:
		p_newAttribute = new ProcedureAttributes{*(dynamic_cast<ProcedureAttributes*>(i_record.attributes))};
		break;
	case NameAttributes::NameType::Array:
		p_newAttribute = new ArrayAttributes{*(dynamic_cast<ArrayAttributes*>(i_record.attributes))};
		break;
	case NameAttributes::NameType::Variable:
		p_newAttribute = new VariableAttributes{*(dynamic_cast<VariableAttributes*>(i_record.attributes))};
		break;
	case NameAttributes::NameType::Constant:
		p_newAttribute = new ConstantAttributes{*(dynamic_cast<ConstantAttributes*>((i_record.attributes)))};
		break;
	default:
		//May be throwing error needed
		break;
	};
	m_nameRecords.insert({i_record.ID, p_newAttribute});
}
const std::vector<std::string> TableOfNames::HeaderLine{"Block", "IdName", "Attributes"};
inline std::string stringNSpace(long unsigned int i_n){
	std::string o_str{};
	for (;i_n != 0; i_n--)
		o_str += ' ';
	return o_str;

}
std::ostream& operator<<(std::ostream& io_os, const TableOfNames& i_table){
	std::vector<long unsigned> maxLength{TableOfNames::HeaderLine[0].length(), TableOfNames::HeaderLine[1].length()};

	for (auto& it : i_table.m_nameRecords){
		maxLength[0] = ((it.first.blockName.length() > maxLength[0]) ? it.first.blockName.length() : maxLength[0]);
		maxLength[1] = ((it.first.name.length() > maxLength[0]) ? it.first.name.length() : maxLength[1]);
	}

	io_os << stringNSpace(maxLength[0] - TableOfNames::HeaderLine[0].length()) << TableOfNames::HeaderLine[0] << '\t';
	io_os << stringNSpace(maxLength[1] - TableOfNames::HeaderLine[1].length()) << TableOfNames::HeaderLine[1] << '\t';
	io_os << TableOfNames::HeaderLine[2] << std::endl;

	for (auto& it : i_table.m_nameRecords){
		io_os << stringNSpace(maxLength[0] - it.first.blockName.length()) << it.first.blockName << '\t';
		io_os << stringNSpace(maxLength[1] - it.first.name.length()) << it.first.name << '\t';
		io_os << it.second->getPrintableText() << std::endl;
	}
	return io_os;
}
