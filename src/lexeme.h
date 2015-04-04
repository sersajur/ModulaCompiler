/*
 * lexeme.h
 *
 *  Created on: 21 бер. 2015
 *      Author: sersajur
 */

#ifndef LEXEME_H_
#define LEXEME_H_

#include <map>
#include <string>
#include <ostream>

using std::map;
using std::string;
using std::ostream;

namespace LEX{

	enum LexType{ /* Lexeme Types */
		LXEOF=0, LXIDENTIFIER,
		LXSTRCONST, LXINTCONST, LXREALCONST, LXBOOLCONST,
		LXOPERATOR,
		LXDELIMITER, LXSTWORD,
		LXERROR
	};

	const map<LexType, string> LexTypeNames{ /* used for debugging/testing */
		{LXEOF, "eof"},
		{LXIDENTIFIER, "id"},
		{LXSTRCONST, "const_str"},
		{LXINTCONST, "const_int"},
		{LXREALCONST, "const_real"},
		{LXBOOLCONST, "const_bool"},
		{LXOPERATOR, "operator"},
		{LXDELIMITER, "delimiter"},
		{LXSTWORD, "statement_word"},
		{LXERROR, "error"}
	};

	enum class LexValue: int{ /* Lexeme Values */
		/* operators */
		LE, /* '<' */
		GE, /* '>' */
		EQ, /* '=' */
		ADD, /* '+' */
		SUB, /* '-' */
		MUL, /* '*' */
		DIV, /* '/' */
		OR, /* 'or' */
		AND, /* 'and' */
		ASS, /* ':=' */

		/* delimiters */
		SEMICOLOM, 	/* ';' */
		COLOM, 		/* ':' */
		DOT,		/* '.' */ 	/* unused */
		QUOT,		/* ' */		/* unused */
		LBR,		/* '(' */
		RBR, 		/* ')' */
		LBRIND,		/* '[' */
		RBRIND, 	/* ']' */

		/* boolean constants */
		FALSE,
		TRUE,

		/* statement words */
		BEGIN, END,
		IF, THEN, ELSIF, ELSE,
		CONST, VAR,
		REAL, INTEGER, BOOLEAN, CHAR,
		ARRAY, OF,
		MODULE, DEFINE, USE,
		FOR
	};

	const map<LexValue, string> LexValueNames{ /* used for debugging/testing */
		{LexValue::LE, "le"},
		{LexValue::GE, "ge"},
		{LexValue::EQ, "eq"},
		{LexValue::ADD, "add"},
		{LexValue::SUB, "sub"},
		{LexValue::MUL, "mul"},
		{LexValue::DIV, "div"},
		{LexValue::OR, "or"},
		{LexValue::AND, "and"},
		{LexValue::ASS, "ass"},
		{LexValue::SEMICOLOM, "semicolom"},
		{LexValue::COLOM, "colom"},
		{LexValue::DOT, "dot"},
		{LexValue::QUOT, "quat"},
		{LexValue::LBR, "lbr"},
		{LexValue::RBR, "rbr"},
		{LexValue::LBRIND, "lbrind"},	/* possible upgrade: */
		{LexValue::RBRIND, "rbrind"}, 	/* the statement words might be stored in boost::bimap */
		{LexValue::FALSE, "false"},		/* for reject redundant due using two structures (LexValueNames, ReservedWords) */
		{LexValue::TRUE, "false"},
		{LexValue::BEGIN, "begin"},
		{LexValue::END, "end"},
		{LexValue::IF, "if"},
		{LexValue::THEN, "then"},
		{LexValue::ELSIF, "elsif"},
		{LexValue::ELSE, "else"},
		{LexValue::CONST, "const"},
		{LexValue::VAR, "var"},
		{LexValue::REAL, "real"},
		{LexValue::INTEGER, "integer"},
		{LexValue::BOOLEAN, "boolean"},
		{LexValue::CHAR, "char"},
		{LexValue::ARRAY, "array"},
		{LexValue::OF, "of"},
		{LexValue::MODULE, "module"},
		{LexValue::DEFINE, "define"},
		{LexValue::USE, "use"},
		{LexValue::FOR, "for"},
	};

	struct Lexeme{
		LexType type;
		int value;
		string text;
		int line_number;
		int column_number;
		friend ostream& operator<<(ostream& os, const Lexeme& lex);
	};

	const string HeaderLine = "Line\t|Column\t|Type\t|Value\t|Text";
}

#endif /* LEXEME_H_ */
