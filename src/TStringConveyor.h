/*
 * TStringConveyor.h
 *
 *  Created on: Apr 9, 2015
 *      Author: sersajur
 */

#ifndef TSTRINGCONVEYOR_H_
#define TSTRINGCONVEYOR_H_

#include <vector>
#include <string>

using std::vector;
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
	void ungetToSource(const vector<char>::iterator i_begin, const vector<char>::iterator i_end);
	virtual char ProcessSymbol(char i_Symbol);
public:
	TStringConveyor();
	virtual ~TStringConveyor(){ };

	virtual operator bool() const {return true;}
	char getSymbol();
	void ungetSymbol(char i_ch);

	TStringConveyor& operator>>(vector<char>& i_DestinationVector);
	friend TStringConveyor& operator>>(string& i_SourceString, TStringConveyor& io_StringConveyor);
	TStringConveyor& operator>>(TStringConveyor& io_StringConveyorUser);

	TStringConveyor& operator<<(vector<char>& i_DestinationVector);
	friend TStringConveyor& operator<<(string& i_SourceString, TStringConveyor& io_StringConveyor);
	TStringConveyor& operator<<(TStringConveyor& io_StringConveyorUser);
};


#endif /* TSTRINGCONVEYOR_H_ */
