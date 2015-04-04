/*
 * term.h
 *
 *  Created on: 22 бер. 2015
 *      Author: sersajur
 */

#ifndef TERM_H_
#define TERM_H_

#include <map>
#include <istream>
#include "lexeme.h"

using std::map;
using std::istream;

namespace LEX{

	enum class SymbolClassMask: int{
		UNKNOWN=0,
		DIGIT=1, ODIGIT=2,
		LETTER=4, WHITESPACE=8,
		DELIMITER=16, OPERATOR=32,
		SIGN=64, _EOF=128, ENDLINE=256
	};

	inline const SymbolClassMask& operator|(const SymbolClassMask& a, const SymbolClassMask& b){
		return static_cast<SymbolClassMask>(static_cast<int>(a)|static_cast<int>(b));
	}
	inline const SymbolClassMask& operator&(const SymbolClassMask& a, const SymbolClassMask& b){
		return static_cast<SymbolClassMask>(static_cast<int>(a)&static_cast<int>(b));
	}

	const map<char, SymbolClassMask> SymbolClass{
		{'0', SymbolClassMask::ODIGIT|SymbolClassMask::DIGIT},
		{'1', SymbolClassMask::ODIGIT|SymbolClassMask::DIGIT},
		{'2', SymbolClassMask::ODIGIT|SymbolClassMask::DIGIT},
		{'3', SymbolClassMask::ODIGIT|SymbolClassMask::DIGIT},
		{'4', SymbolClassMask::ODIGIT|SymbolClassMask::DIGIT},
		{'5', SymbolClassMask::ODIGIT|SymbolClassMask::DIGIT},
		{'6', SymbolClassMask::ODIGIT|SymbolClassMask::DIGIT},
		{'7', SymbolClassMask::ODIGIT|SymbolClassMask::DIGIT},
		{'8', SymbolClassMask::DIGIT},
		{'9', SymbolClassMask::DIGIT},

		{'a', SymbolClassMask::LETTER},
		{'b', SymbolClassMask::LETTER},
		{'c', SymbolClassMask::LETTER},
		{'d', SymbolClassMask::LETTER},
		{'e', SymbolClassMask::LETTER},
		{'f', SymbolClassMask::LETTER},
		{'g', SymbolClassMask::LETTER},
		{'h', SymbolClassMask::LETTER},
		{'i', SymbolClassMask::LETTER},
		{'j', SymbolClassMask::LETTER},
		{'k', SymbolClassMask::LETTER},
		{'l', SymbolClassMask::LETTER},
		{'m', SymbolClassMask::LETTER},
		{'n', SymbolClassMask::LETTER},
		{'o', SymbolClassMask::LETTER},
		{'p', SymbolClassMask::LETTER},
		{'q', SymbolClassMask::LETTER},
		{'r', SymbolClassMask::LETTER},
		{'s', SymbolClassMask::LETTER},
		{'t', SymbolClassMask::LETTER},
		{'u', SymbolClassMask::LETTER},
		{'v', SymbolClassMask::LETTER},
		{'w', SymbolClassMask::LETTER},
		{'x', SymbolClassMask::LETTER},
		{'y', SymbolClassMask::LETTER},
		{'z', SymbolClassMask::LETTER},
		{'_', SymbolClassMask::LETTER},
		{'A', SymbolClassMask::LETTER},
		{'B', SymbolClassMask::LETTER},
		{'C', SymbolClassMask::LETTER},
		{'D', SymbolClassMask::LETTER},
		{'E', SymbolClassMask::LETTER},
		{'F', SymbolClassMask::LETTER},
		{'G', SymbolClassMask::LETTER},
		{'H', SymbolClassMask::LETTER},
		{'I', SymbolClassMask::LETTER},
		{'J', SymbolClassMask::LETTER},
		{'K', SymbolClassMask::LETTER},
		{'L', SymbolClassMask::LETTER},
		{'M', SymbolClassMask::LETTER},
		{'N', SymbolClassMask::LETTER},
		{'O', SymbolClassMask::LETTER},
		{'P', SymbolClassMask::LETTER},
		{'Q', SymbolClassMask::LETTER},
		{'R', SymbolClassMask::LETTER},
		{'S', SymbolClassMask::LETTER},
		{'T', SymbolClassMask::LETTER},
		{'U', SymbolClassMask::LETTER},
		{'V', SymbolClassMask::LETTER},
		{'W', SymbolClassMask::LETTER},
		{'X', SymbolClassMask::LETTER},
		{'Y', SymbolClassMask::LETTER},
		{'Z', SymbolClassMask::LETTER},

		{' ', SymbolClassMask::WHITESPACE},
		{'\t', SymbolClassMask::WHITESPACE},
		{'\n', SymbolClassMask::WHITESPACE},

		{'(', SymbolClassMask::DELIMITER},
		{')', SymbolClassMask::DELIMITER},
		{'[', SymbolClassMask::DELIMITER},
		{']', SymbolClassMask::DELIMITER},
		{';', SymbolClassMask::DELIMITER},
		{':', SymbolClassMask::DELIMITER},
		{'.', SymbolClassMask::DELIMITER},
		{'\'',SymbolClassMask::DELIMITER},

		{'=', SymbolClassMask::OPERATOR},
		{'-', SymbolClassMask::OPERATOR|SymbolClassMask::SIGN},
		{'+', SymbolClassMask::OPERATOR|SymbolClassMask::SIGN},
		{'/', SymbolClassMask::OPERATOR},
		{'*', SymbolClassMask::OPERATOR},
		{'>', SymbolClassMask::OPERATOR},
		{'<', SymbolClassMask::OPERATOR}
	};

	const map<char, LexValue> OperatorSymbolClassValue{
		{'=', LexValue::ASS},
		{'-', LexValue::SUB},
		{'+', LexValue::ADD},
		{'/', LexValue::DIV},
		{'*', LexValue::MUL},
		{'>', LexValue::GE},
		{'<', LexValue::LE}
	};

	const map<char, LexValue> DelimiterSymbolClassValue{
		{'(', LexValue::LBR},
		{')', LexValue::RBR},
		{'[', LexValue::LBRIND},
		{']', LexValue::RBRIND},
		{';', LexValue::SEMICOLOM},
		{':', LexValue::COLOM},
		{'.', LexValue::DOT},
		{'\'',LexValue::QUOT}
	};

	struct Term{
		char symbol;
		SymbolClassMask classMask;
		Term(const char& ch);
		inline bool isEndl() const{
			return symbol == '\n';
		}
		inline bool isEOF() const{
			return classMask == SymbolClassMask::_EOF;
		}
		//operator char() const {return symbol;}
		//operator SymbolClassMask() const {return classMask;}
	};

};

#endif /* TERM_H_ */
