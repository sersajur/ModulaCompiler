/*
 * TToken.h
 *
 *  Created on: Apr 21, 2015
 *      Author: sersajur
 */

#ifndef SRC_TTOKEN_H_
#define SRC_TTOKEN_H_

#include <string>
#include <map>
#include <iostream>

using std::string;
using std::map;
using std::ostream;

#define TOKEN_CLASS(x) _ ## x

class TToken{
public:

	enum class TTokenClass{
		_boolval,
		_intval,
		_realval,
		_strval,
		_id,
	/* operators */
		_le, 		/* '<' */
		_ge, 		/* '>' */
		_eq, 		/* '=' */
		_add, 		/* '+' */
		_sub, 		/* '-' */
		_mul, 		/* '*' */
		_div, 		/* '/' */
		_or, 		/* 'or' */	//reserved
		_and, 		/* 'and' */	//reserved
		_ass, 		/* ':=' */
	/* delims */
		_semicolom, /* ';' */
		_colom, 	/* ':' */
//		_DOT,		/* '.' */
//		_QUOT,		/* '   */
		_lbr,		/* '(' */
		_rbr, 		/* ')' */
		_lbrind,	/* '[' */
		_rbrind, 	/* ']' */
	/* boolean constants */
		_false, 	// reserved
		_true,		// reserved
	/* statement words */
		_begin,		// reserved
		_end,		// reserved
		_if,		// reserved
		_then,		// reserved
		_elsif,		// reserved
		_else,		// reserved
		_const,		// reserved
		_var,		// reserved
		_real,		// reserved
		_integer,	// reserved
		_Boolean,	// reserved
		_char,		// reserved
		_array,		// reserved
		_of,		// reserved
		_module,	// reserved
		_define,	// reserved
		_use,		// reserved
		_for,		// reserved
	/* EOF */
		_eof 	/* '\0' for scanner and '$' for parser */
	};

private:

	static const  map<string, TTokenClass> ReservedWords;
	static const  map<TTokenClass, string> ClassString;

public:
	union TTokenValue{
		bool asBool;
		int asInt;
		float asReal;
		//TODO: repair the union, extend it dor string
//		string asString;
//		TTokenValue(): asString(){}
//		TTokenValue(const TTokenValue& i_value){ this->asString = i_value.asString; }
//		~TTokenValue(){}
	};

	struct TPosition{
		unsigned line;
		unsigned column;
	};

	TToken();
	TToken(const TTokenClass&, const string&,  const TPosition&);
	virtual ~TToken();

	const TTokenClass getClass()const { return m_class; }
	const TTokenValue getValue()const { return m_value; }
	const string getLexeme()const { return m_lexeme; }
	const TPosition getPosition()const { return m_pos; }

	friend ostream& operator<<(ostream& i_os, const TToken& i_token);
private:

	TTokenClass m_class;
	TTokenValue m_value;
	string m_lexeme;
	TPosition m_pos;
};

#endif /* SRC_TTOKEN_H_ */