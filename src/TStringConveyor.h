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
	bool IsSourceAString()const { return m_UseStringAsASourceFlag; }
protected:
	bool IsPassAForward()const { return m_ForwardPassFlag; }
	char getSymbolFromSource();
	void ungetToSource(char i_symbol);
	void ungetToSource(string i_symbol);
	void ungetToSource(const std::string::iterator i_begin, const std::string::iterator i_end);
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
