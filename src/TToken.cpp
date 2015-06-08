/*
 * TLexeme.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: sersajur
 */

#include <string>

#include "TToken.h"

#define RESERVED_WORD(x) {#x, TTokenClass::_ ## x}
const  std::map<std::string, TToken::TTokenClass> TToken::ReservedWords{
		RESERVED_WORD(begin),
		RESERVED_WORD(end),
		RESERVED_WORD(if),
		RESERVED_WORD(then),
		RESERVED_WORD(elsif),
		RESERVED_WORD(else),
		RESERVED_WORD(const),
		RESERVED_WORD(var),
		RESERVED_WORD(real),
		RESERVED_WORD(integer),
		RESERVED_WORD(Boolean),
		RESERVED_WORD(char),
		RESERVED_WORD(array),
		RESERVED_WORD(of),
		{"false", TToken::TTokenClass::_boolval},
		{"true",  TToken::TTokenClass::_boolval},
		RESERVED_WORD(module),
		RESERVED_WORD(define),
		RESERVED_WORD(use),
		RESERVED_WORD(for),
		RESERVED_WORD(or),
		RESERVED_WORD(and),
		RESERVED_WORD(procedure)
};

#define CLASS_STRING(x) {TTokenClass::_ ## x, #x}
const  std::map<TToken::TTokenClass, std::string> TToken::ClassString{
		CLASS_STRING(boolval),
		CLASS_STRING(intval),
		CLASS_STRING(realval),
		CLASS_STRING(strval),
		CLASS_STRING(id),
		CLASS_STRING(le),
		CLASS_STRING(ge),
		CLASS_STRING(eq),
		CLASS_STRING(add),
		CLASS_STRING(sub),
		CLASS_STRING(mul),
		CLASS_STRING(div),
		CLASS_STRING(or),
		CLASS_STRING(and),
		CLASS_STRING(ass),
		CLASS_STRING(semicolom),
		CLASS_STRING(dot),
		CLASS_STRING(comma),
		CLASS_STRING(colom),
		CLASS_STRING(lbr),
		CLASS_STRING(rbr),
		CLASS_STRING(lbrind),
		CLASS_STRING(rbrind),
		CLASS_STRING(begin),
		CLASS_STRING(end),
		CLASS_STRING(if),
		CLASS_STRING(then),
		CLASS_STRING(elsif),
		CLASS_STRING(else),
		CLASS_STRING(const),
		CLASS_STRING(var),
		CLASS_STRING(real),
		CLASS_STRING(integer),
		CLASS_STRING(Boolean),
		CLASS_STRING(char),
		CLASS_STRING(array),
		CLASS_STRING(of),
		CLASS_STRING(module),
		CLASS_STRING(define),
		CLASS_STRING(use),
		CLASS_STRING(for),
		CLASS_STRING(procedure),
		CLASS_STRING(eof)
};
TToken::TToken():
	m_class{TTokenClass::_eof}{

}

TToken::TToken(const TTokenClass& i_class, const std::string& i_lexeme, const TToken::TPosition i_pos):
		m_class{i_class}, m_lexeme{i_lexeme}, m_pos{i_pos}{

	if (TTokenClass::_id == i_class){
		auto it = ReservedWords.find(i_lexeme);
		m_class = ( (it == ReservedWords.end()) ? m_class : it->second );
	}

	switch (m_class){
	case TTokenClass::_boolval:
		m_value.asBool = (m_lexeme == "true" ? true : false);
		break;
	case TTokenClass::_intval:{
		if (m_lexeme.back() == 'B') { //octal int
			m_value.asInt = std::stoi(std::string{m_lexeme.begin(), m_lexeme.end()-1}, 0, 8);
		} else { //dec int
			m_value.asInt = std::stoi(m_lexeme, 0, 10);
		}
		break;
	}
	case TTokenClass::_realval:
			m_value.asReal = std::stod(m_lexeme, 0);
		break;
	case TTokenClass::_strval:
		m_value.asString = i_lexeme;
		break;
	default:
		break;
	}
}
TToken::TToken(const TToken& i_token):
	m_class{i_token.m_class}, m_lexeme{i_token.m_lexeme}, m_pos{i_token.m_pos}{
	switch (m_class){
	case TTokenClass::_boolval:
		m_value.asBool = i_token.m_value.asBool;
		break;
	case TTokenClass::_intval:
		m_value.asInt = i_token.m_value.asInt;
		break;
	case TTokenClass::_realval:
		m_value.asReal = i_token.m_value.asReal;
		break;
	case TTokenClass::_strval:
		m_value.asString = i_token.m_value.asString;
		break;
	default:
		break;
	}
}
TToken TToken::operator=(const TToken& i_token){
	this->m_class = i_token.m_class;
	this->m_lexeme = i_token.m_lexeme;
	this->m_pos = i_token.m_pos;
	switch (m_class){
	case TTokenClass::_boolval:
		m_value.asBool = i_token.m_value.asBool;
		break;
	case TTokenClass::_intval:
		m_value.asInt = i_token.m_value.asInt;
		break;
	case TTokenClass::_realval:
		m_value.asReal = i_token.m_value.asReal;
		break;
	case TTokenClass::_strval:
		m_value.asString = i_token.m_value.asString;
		break;
	default:
		break;
	}
	return *this;
}
TToken::~TToken() {

}

std::ostream& operator<<(std::ostream& i_os, const TToken& i_token){

	std::string lexeme = ((i_token.m_class == TToken::TTokenClass::_eof) ? "" : std::string{"\"" + i_token.m_lexeme + "\""});
	i_os << i_token.m_pos.line << ':' << i_token.m_pos.column << '\t';
	i_os << TToken::ClassString.find(i_token.m_class)->second << '\t';
	i_os << lexeme << '\t';
	switch (i_token.m_class){
	case TToken::TTokenClass::_boolval:
		i_os << i_token.m_value.asBool;
		break;
	case TToken::TTokenClass::_intval:
		i_os << i_token.m_value.asInt;
		break;
	case TToken::TTokenClass::_realval:
		i_os << i_token.m_value.asReal;
		break;
	case TToken::TTokenClass::_strval:
		i_os << i_token.m_value.asString;
		break;
	default:
		break;
	}
	return i_os;
}
