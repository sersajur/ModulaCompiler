/*
 * Scaner.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: sersajur
 */

#include <vector>
#include <set>

#include "Scaner.h"
#include "TFiniteStateMachine.h"
#include "TLexicalException.h"

using std::vector;

Scaner::Scaner():
m_lastTokenExtracted(false){

}

Scaner::~Scaner() {

}

void Scaner::Configurate(const string& i_inputStr){
	m_srcString = i_inputStr;
	m_lastTokenExtracted = false;

	//For Position Counting
	TFiniteStateMachine<char, TCntStates> fsmForPosCounter{
		TCntStates::START,
		{TCntStates::f_COLUMN, TCntStates::f_LINE_IOS_OR_WINBEGIN, TCntStates::f_LINE_LINUX, TCntStates::f_LINE_WINDOWS}
	};
	fsmForPosCounter
		(TCntStates::START, '\n', TCntStates::f_LINE_LINUX)
		(TCntStates::START, '\r', TCntStates::f_LINE_IOS_OR_WINBEGIN)
		(TCntStates::START, TCntStates::f_COLUMN)
		(TCntStates::f_LINE_IOS_OR_WINBEGIN, '\n', TCntStates::f_LINE_WINDOWS);

	TPositionCounter<TCntStates> posCounter{
		fsmForPosCounter,
		{TCntStates::f_COLUMN},
		{TCntStates::f_LINE_LINUX, TCntStates::f_LINE_IOS_OR_WINBEGIN, TCntStates::f_LINE_WINDOWS}
	};
	m_posCounter = posCounter;

	//For Comment Suppressing
	TFiniteStateMachine<char, TCommentStates> fsmForComment{
		TCommentStates::START,
		{TCommentStates::f_NOCOMMENT, TCommentStates::f_COMMENT_END}
	};
	fsmForComment
		(TCommentStates::START, '(', TCommentStates::MAYBE_COMMENT_BEGIN)
		(TCommentStates::START, '(', TCommentStates::f_NOCOMMENT)
		(TCommentStates::START, TCommentStates::f_NOCOMMENT)
		(TCommentStates::MAYBE_COMMENT_BEGIN, '*', TCommentStates::COMMENT)
		(TCommentStates::COMMENT, '*', TCommentStates::MAYBE_COMMENT_END)
		(TCommentStates::COMMENT, TCommentStates::COMMENT).except(TCommentStates::COMMENT, '\0')
		(TCommentStates::MAYBE_COMMENT_END, '*', TCommentStates::MAYBE_COMMENT_END)
		(TCommentStates::MAYBE_COMMENT_END, ')', TCommentStates::f_COMMENT_END)
		(TCommentStates::MAYBE_COMMENT_END, TCommentStates::COMMENT).except(TCommentStates::MAYBE_COMMENT_END, '\0');
	TCommentFilter<TCommentStates> commentFilter{
		fsmForComment,
		{TCommentStates::f_COMMENT_END}
	};
	m_commentFilter = commentFilter;

	//For white space suppressing
	m_whiteSpaceFilter.setStartState(TWhiteSpaceStates::start);
	m_whiteSpaceFilter.setFinalStates(set<TWhiteSpaceStates>{TWhiteSpaceStates::f_not_white_space});
	const set<char> WhiteSpaceSymbols{' ', '\n', '\t'};
	m_whiteSpaceFilter
	(TWhiteSpaceStates::start, WhiteSpaceSymbols, TWhiteSpaceStates::whitespace)
	(TWhiteSpaceStates::start, TWhiteSpaceStates::f_not_white_space)
	(TWhiteSpaceStates::whitespace, WhiteSpaceSymbols, TWhiteSpaceStates::whitespace)
	(TWhiteSpaceStates::whitespace, TWhiteSpaceStates::f_not_white_space)
	(TWhiteSpaceStates::f_not_white_space, TWhiteSpaceStates::f_not_white_space);
	m_whiteSpaceFilter.Reset();

	//For Token Extraction
	m_tokenExtractor.setStartState(TTokenExtractState::start);
	m_tokenExtractor.setFinalStates(
		set<TTokenExtractState>
		{TTokenExtractState::f_intval,
		TTokenExtractState::f_realval,
		TTokenExtractState::f_strval,
		TTokenExtractState::f_id,
		TTokenExtractState::f_le,
		TTokenExtractState::f_ge,
		TTokenExtractState::f_eq,
		TTokenExtractState::f_add,
		TTokenExtractState::f_sub,
		TTokenExtractState::f_mul,
		TTokenExtractState::f_div,
		TTokenExtractState::f_ass,
		TTokenExtractState::f_semicolom,
		TTokenExtractState::f_colom,
		TTokenExtractState::f_lbr,
		TTokenExtractState::f_rbr,
		TTokenExtractState::f_lbrind,
		TTokenExtractState::f_rbrind,
		TTokenExtractState::f_eof}
	);
	const set<char> Letters{
		'a', 'A',
		'b', 'B',
		'c', 'C',
		'd', 'D',
		'e', 'E',
		'f', 'F',
		'g', 'G',
		'h', 'H',
		'i', 'I',
		'j', 'J',
		'k', 'K',
		'l', 'L',
		'm', 'M',
		'n', 'N',
		'o', 'O',
		'p', 'P',
		'q', 'Q',
		'r', 'R',
		's', 'S',
		't', 'T',
		'u', 'U',
		'v', 'V',
		'w', 'W',
		'x', 'X',
		'y', 'Y',
		'z', 'Z',
		'_'
	};
	const set<char> Digits{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};
	const set<char> OctalDigits{
		'0', '1', '2', '3', '4', '5', '6', '7'
	};
	m_tokenExtractor
	(TTokenExtractState::start, '\0', TTokenExtractState::f_eof)
	(TTokenExtractState::start, '[' , TTokenExtractState::f_lbrind)
	(TTokenExtractState::start, ']' , TTokenExtractState::f_rbrind)
	(TTokenExtractState::start, '(' , TTokenExtractState::f_lbr)
	(TTokenExtractState::start, ')' , TTokenExtractState::f_rbr)
	(TTokenExtractState::start, ':' , TTokenExtractState::f_colom)
	(TTokenExtractState::start, ';' , TTokenExtractState::f_semicolom)
	(TTokenExtractState::start, ':' , TTokenExtractState::pre_ass1)
		(TTokenExtractState::pre_ass1, '=' , TTokenExtractState::f_ass)
	(TTokenExtractState::start, '/' , TTokenExtractState::f_div)
	(TTokenExtractState::start, '*' , TTokenExtractState::f_mul)
	(TTokenExtractState::start, '-' , TTokenExtractState::f_sub)
	(TTokenExtractState::start, '+' , TTokenExtractState::f_add)
	(TTokenExtractState::start, '=' , TTokenExtractState::f_eq)
	(TTokenExtractState::start, '>' , TTokenExtractState::f_ge)
	(TTokenExtractState::start, '<' , TTokenExtractState::f_le)
	(TTokenExtractState::start, Letters , TTokenExtractState::f_id)
		(TTokenExtractState::f_id, Letters , TTokenExtractState::f_id)
		(TTokenExtractState::f_id, Digits ,  TTokenExtractState::f_id)
		//string value " '(something-\0| ''')^+' ":
	(TTokenExtractState::start, '\'',  TTokenExtractState::pre_str1)
		(TTokenExtractState::pre_str1, TTokenExtractState::pre_str1).except(TTokenExtractState::pre_str1, '\0')
		(TTokenExtractState::pre_str1, '\'', TTokenExtractState::f_strval)
		(TTokenExtractState::pre_str1, '\'', TTokenExtractState::pre_str_quote1)
			(TTokenExtractState::pre_str_quote1, '\'', TTokenExtractState::pre_str_quote2)
				(TTokenExtractState::pre_str_quote2, '\'', TTokenExtractState::pre_str1)
		//string value " ([0-7])^(+3)C ":
	(TTokenExtractState::start, OctalDigits, TTokenExtractState::pre_str11)
		(TTokenExtractState::pre_str11, 'C', TTokenExtractState::f_strval)
		(TTokenExtractState::pre_str11, OctalDigits, TTokenExtractState::pre_str22)
			(TTokenExtractState::pre_str22, 'C', TTokenExtractState::f_strval)
			(TTokenExtractState::pre_str22, OctalDigits, TTokenExtractState::pre_str33)
				(TTokenExtractState::pre_str33, 'C', TTokenExtractState::f_strval)
		//real value " (digit)^+.(digit)^+ "
	(TTokenExtractState::start, Digits, TTokenExtractState::pre_real1)
		(TTokenExtractState::pre_real1, Digits, TTokenExtractState::pre_real1)
		(TTokenExtractState::pre_real1, '.', TTokenExtractState::pre_real_dot1)
			(TTokenExtractState::pre_real_dot1, Digits, TTokenExtractState::f_realval)
			(TTokenExtractState::pre_real_dot1, Digits, TTokenExtractState::pre_real2)
			(TTokenExtractState::pre_real2, Digits, TTokenExtractState::f_realval)
		//real value " (digit)^+E[+|-](digit)^+ "
	(TTokenExtractState::start, Digits, TTokenExtractState::pre_real11)
		(TTokenExtractState::pre_real11, Digits, TTokenExtractState::pre_real11)
		(TTokenExtractState::pre_real11, 'E', TTokenExtractState::pre_real_mantissa11)
			(TTokenExtractState::pre_real_mantissa11, {'+', '-'}, TTokenExtractState::pre_real_mantissa22)
				(TTokenExtractState::pre_real_mantissa22, Digits, TTokenExtractState::pre_real22)
				(TTokenExtractState::pre_real_mantissa22, Digits, TTokenExtractState::f_realval)
			(TTokenExtractState::pre_real_mantissa11, Digits, TTokenExtractState::pre_real22)
			(TTokenExtractState::pre_real_mantissa11, Digits, TTokenExtractState::f_realval)
				(TTokenExtractState::pre_real22, Digits, TTokenExtractState::f_realval)
		//real value " (digit)^+.(digit)^+E[+|-](digit)^+ "
	(TTokenExtractState::start, Digits, TTokenExtractState::pre_real111)
		(TTokenExtractState::pre_real111, Digits, TTokenExtractState::pre_real111)
		(TTokenExtractState::pre_real111, '.', TTokenExtractState::pre_real_dot111)
		(TTokenExtractState::pre_real_dot111, Digits, TTokenExtractState::pre_real222)
			(TTokenExtractState::pre_real222, Digits, TTokenExtractState::pre_real222)
			(TTokenExtractState::pre_real222, 'E', TTokenExtractState::pre_real_mantissa111)
				(TTokenExtractState::pre_real_mantissa111, {'+', '-'}, TTokenExtractState::pre_real_mantissa222)
					(TTokenExtractState::pre_real_mantissa222, Digits, TTokenExtractState::pre_real333)
					(TTokenExtractState::pre_real_mantissa222, Digits, TTokenExtractState::f_realval)
						(TTokenExtractState::pre_real333, Digits, TTokenExtractState::f_realval)
				(TTokenExtractState::pre_real_mantissa111, Digits, TTokenExtractState::pre_real333)
				(TTokenExtractState::pre_real_mantissa111, Digits, TTokenExtractState::f_realval)
		//integer value " (digit)^+ "
	(TTokenExtractState::start, Digits, TTokenExtractState::f_intval)
	(TTokenExtractState::start, Digits, TTokenExtractState::pre_int1)
		(TTokenExtractState::pre_int1, Digits, TTokenExtractState::pre_int1)
		(TTokenExtractState::pre_int1, Digits, TTokenExtractState::f_intval)
		//integer value " (octaldigit)^+B "
	(TTokenExtractState::start, OctalDigits, TTokenExtractState::pre_int11)
	(TTokenExtractState::pre_int11, OctalDigits, TTokenExtractState::pre_int11)
	(TTokenExtractState::pre_int11, 'B', TTokenExtractState::f_intval);
	m_tokenExtractor.Reset();

	m_srcString >> m_posCounter >> m_commentFilter >> m_whiteSpaceFilter >> m_tokenExtractor;
}

void Scaner::Reset(const string& i_inputStr){
	m_srcString = i_inputStr;
	m_posCounter.Reset();
	m_tokenExtractor.Reset();
}

TToken Scaner::getNextToken(){
	vector<char> destString;
	auto pos = m_posCounter.getPosition();
	try{

		do{
			m_whiteSpaceFilter.Reset();
		}while(m_tokenExtractor >> destString);

		if (!m_tokenExtractor.IsMachineAccept())
			throw TLexicalException("Can't find token matching target string");

		auto states = m_tokenExtractor.getLastFinalStates();
		if (states.size() > 1)
			throw TLexicalException("It's been found multiple tokens matching target string");

		int rollBackNum = m_tokenExtractor.getSymbolNumberAfterLastFinalState();
		for (; rollBackNum; rollBackNum--)
			m_tokenExtractor << destString;


		TToken o_token{
			StateClass.find(*states.begin())->second,
			string(destString.begin(), destString.end()),
			{pos.line, pos.column}
		};

		m_tokenExtractor.Reset();
		return o_token;
	}
	catch(TLexicalException& e){
		throw TLexicalException(pos.line, pos.column, string(destString.begin(), destString.end()), e.what());
	}
}
