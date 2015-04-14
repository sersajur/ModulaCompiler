/*
 * TStringConveyor.h
 *
 *  Created on: Apr 9, 2015
 *      Author: sersajur
 */

#ifndef TSTRINGCONVEYOR_H_
#define TSTRINGCONVEYOR_H_

#include <string>

using std::string;

class TStringConveyor{
	string* m_SourceString;
	TStringConveyor* m_SourceConveyor;
	bool m_UseStringAsASourceFlag;
	bool m_ForwardPassFlag;
	inline bool IsSourceAString()const { return m_UseStringAsASourceFlag; }
protected:
	inline bool IsPassAForward()const { return m_ForwardPassFlag; }

	virtual char ProcessSymbol(char i_Symbol);
public:
	TStringConveyor();
	virtual ~TStringConveyor(){ };

	char getSymbol();
	void ungetSymbol(char i_ch);

	TStringConveyor& operator>>(string& i_DestinationString);
	friend TStringConveyor& operator>>(string& i_SourceString, TStringConveyor& io_StringConveyor);
	TStringConveyor& operator>>(TStringConveyor& io_StringConveyorUser);

	TStringConveyor& operator<<(string& i_DestinationString);
	friend TStringConveyor& operator<<(string& i_SourceString, TStringConveyor& io_StringConveyor);
	TStringConveyor& operator<<(TStringConveyor& io_StringConveyorUser);
};


#endif /* TSTRINGCONVEYOR_H_ */
