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


bool TableOfNames::IsDeclared(const TNameId& i_id) const{
	return m_nameRecords.find(i_id) != m_nameRecords.end();
}
const TableOfNames::TRecord TableOfNames::getRecord(const TNameId& i_nameId) const{
	const auto& it = m_nameRecords.find(i_nameId);
	return {i_nameId, it->second};
}
void TableOfNames::Insert(const TRecord& i_record){
	NameAttributes* p_newAttribute;
	switch (i_record.attributes->getNameType()){
	case NameAttributes::NameType::Module:
		p_newAttribute = new ModuleAttributes(*dynamic_cast<ModuleAttributes*>(i_record.attributes));
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
		p_newAttribute = new ConstantAttributes{*(dynamic_cast<ConstantAttributes*>(i_record.attributes))};
		break;
	default:
		//May be throwing error needed
		break;
	};
	m_nameRecords.insert({i_record.ID, p_newAttribute});
}
