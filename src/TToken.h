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
		_dot,		/* '.' */
		_comma,
//		_QUOT,		/* '   */
		_lbr,		/* '(' */
		_rbr, 		/* ')' */
		_lbrind,	/* '[' */
		_rbrind, 	/* ']' */
	/* boolean constants */
//		_false, 	// reserved
//		_true,		// reserved
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
		_procedure, // reserved
	/* EOF */
		_eof 	/* '\0' for scanner and '$' for parser */
	};

private:

	static const  std::map<std::string, TTokenClass> ReservedWords;
	static const  std::map<TTokenClass, std::string> ClassString;

public:

	union TTokenValue{
		bool asBool;
		int asInt;
		float asReal;
		std::string asString;
		TTokenValue():asString{""}{}
		TTokenValue(const TTokenValue& i_tval): asBool{i_tval.asBool}{}
		TTokenValue& operator=(const TTokenValue& i_tval){
			asBool = i_tval.asBool;
			return *this;
		}
		~TTokenValue(){}
	};

	struct TPosition{
		unsigned line;
		unsigned column;
		TPosition():line{0},column{0}{}
		TPosition(const unsigned l, const unsigned c): line{l}, column{c}{}
		TPosition(const TPosition& i_pos): line{i_pos.line}, column{i_pos.column}{}
	};

	TToken();
	TToken(const TTokenClass& i_tclass, const std::string& i_tlexeme,  const TPosition i_position);
	TToken(const TToken& i_token);
	virtual ~TToken();

	const TTokenClass getClass()const { return m_class; }
	const TTokenValue getValue()const { return m_value; }
	const std::string getLexeme()const { return m_lexeme; }
	const TPosition getPosition()const { return m_pos; }

	friend std::ostream& operator<<(std::ostream& i_os, const TToken& i_token);
	//Debug
	static std::string ClassToString(const TTokenClass& i_class){
		return ClassString.find(i_class)->second;
	}
private:

	TTokenClass m_class;
	TTokenValue m_value;
	std::string m_lexeme;
	TPosition m_pos;
};

#endif /* SRC_TTOKEN_H_ */
