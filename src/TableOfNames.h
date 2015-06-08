/*
 * TableOfNames.h
 *
 *  Created on: 1 черв. 2015
 *      Author: sersajur
 */

#ifndef TABLEOFNAMES_H_
#define TABLEOFNAMES_H_

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "NameAttributes.h"

class TableOfNames {
public:
	struct TRecord{
		TNameId ID;
		NameAttributes* attributes;
	};
private:
	std::map<TNameId, NameAttributes*> m_nameRecords;
public:
	TableOfNames();
	TableOfNames(const TableOfNames& i_srcTable);
	TableOfNames& operator=(const TableOfNames& i_srcTable);
	virtual ~TableOfNames(); //don't forget about memory free;

	bool IsDeclared(const TNameId& i_id) const; // weather the name is declared
	const TRecord getRecord(const TNameId& i_nameId) const;
	void Insert(const TRecord& i_record); //there the memory is going to be allocated

	static const std::vector<std::string> HeaderLine;
	friend std::ostream& operator<<(std::ostream& io_os, const TableOfNames& i_table);
};

#endif /* TABLEOFNAMES_H_ */
