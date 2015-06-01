/*
 * TableOfNames.h
 *
 *  Created on: 1 черв. 2015
 *      Author: sersajur
 */

#ifndef TABLEOFNAMES_H_
#define TABLEOFNAMES_H_

#include <string>
#include <map>
#include "NameAttributes.h"

class TableOfNames {
public:
	struct TNameId{
		std::string name;
		std::string blockName;
		bool operator<(const TNameId& compId)const{
			return ((blockName == compId.blockName) ? (name < compId.name) : (blockName < compId.blockName));
		}
	};
	struct TRecord{
		TNameId ID;
		NameAttributes* attributes;
	};
private:
	std::map<TNameId, NameAttributes*> m_nameRecords;

	TableOfNames& operator=(const TableOfNames&);
	TableOfNames(const TableOfNames&);
public:
	TableOfNames();
	virtual ~TableOfNames(); //don't forget about memory free;

	bool IsDeclared(const TNameId& i_id) const; // weather the name is declared
	const TRecord getRecord(const TNameId& i_nameId) const;
	void Insert(const TRecord& i_record); //there the memory is going to be allocated
};

#endif /* TABLEOFNAMES_H_ */
