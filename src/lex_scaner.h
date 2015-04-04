/*
 * lex_scaner.h
 *
 *  Created on: 1 бер. 2015
 *      Author: sersajur
 */

#ifndef LEX_SCANER_H_
#define LEX_SCANER_H_

#include <map>
#include <string>
#include <istream>
#include <vector>

#include "lexeme.h"
#include "term.h"

using std::map;
using std::string;
using std::istream;
using std::streambuf;
using std::vector;

namespace LEX{

	struct ReservedWordTypeValue{
		LexType type;
		LexValue value;
	};

	const map<string, ReservedWordTypeValue> ReservedWords{
			{"begin", 	{LXSTWORD, 		LexValue::BEGIN}},
			{"end",   	{LXSTWORD, 		LexValue::END}},
			{"if", 	  	{LXSTWORD, 		LexValue::IF}},
			{"then",  	{LXSTWORD, 		LexValue::THEN}},
			{"elsif", 	{LXSTWORD, 		LexValue::ELSIF}},
			{"else",  	{LXSTWORD, 		LexValue::ELSE}},
			{"const", 	{LXSTWORD, 		LexValue::CONST}},
			{"var",   	{LXSTWORD, 		LexValue::VAR}},
			{"real",  	{LXSTWORD, 		LexValue::REAL}},
			{"integer",	{LXSTWORD,		LexValue::INTEGER}},
			{"Boolean",	{LXSTWORD,		LexValue::BOOLEAN}},
			{"char",  	{LXSTWORD, 		LexValue::CHAR}},
			{"array", 	{LXSTWORD, 		LexValue::ARRAY}},
			{"of",    	{LXSTWORD, 		LexValue::OF}},
			{"false", 	{LXBOOLCONST,	LexValue::FALSE}},
			{"true",  	{LXBOOLCONST,	LexValue::TRUE}},
			{"module",	{LXSTWORD, 		LexValue::MODULE}},
			{"define",	{LXSTWORD, 		LexValue::DEFINE}},
			{"use",   	{LXSTWORD, 		LexValue::USE}},
			{"for",   	{LXSTWORD, 		LexValue::FOR}},
			{"or",    	{LXOPERATOR,	LexValue::OR}},
			{"and",   	{LXOPERATOR, 	LexValue::AND}}
	};

	class Lex_scaner{
	public:
		typedef string LexException;
		Lex_scaner();
		Lex_scaner(const string& i_str);
		LexType getLexeme(Lexeme& i_lexeme);
		virtual ~Lex_scaner();
	private:
		typedef unsigned int pos;

		string m_stream;
		pos m_startPos, m_curPos;

		vector<pos> m_lastColum;
		pos m_curLine, m_curColum;


		inline const Term& currentTerm() const{
			return Term(m_stream.c_str[m_curPos]);
		}

		void readNextTerm(); // TODO: check if 'throw' needed
		void machineBackStep(pos i_stepsNumber=1);

		enum class AutomatInternalState: int{
			q_START, q_WAIT_OCTAL, f_EXTRACT_INT, f_EXTRACT_STR,
			q_INT_PART, q_FRAC_PART1, q_FRAC_PART2, q_MANTISSA1,
			q_MANTISSA2, q_MANTISSA3, f_EXTRACT_REAL,
			q_IDENT, f_EXTRACT_IDENT,
			q_OP_ASSIGN, f_EXTRACT_OP_ASSIGN, f_EXTRACT_DELIMITER,
			f_EXTRACT_OP,
			q_STR0, q_STR1, q_STR2, f_EXTRACT_ERROR,
			q_COM0, q_COM1, q_COM2, q_COM3, f_EXTRACT_COM,
			f_EXTRACT_EOF
		};

	};
};
#endif /* LEX_SCANER_H_ */
