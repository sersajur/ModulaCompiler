//============================================================================
// Name        : main.cpp
// Author      : sersajur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "TStringConveyor.h"
#include "TFiniteStateMachine.h"
#include "TPositionCounter.h"
#include "TCommentFilter.h"
#include "TTokenExtractor.h"
#include "TToken.h"

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

int main() {

	//For Position Counting

	enum class TCntStates{
		START, 	f_COLUMN,
		f_LINE_LINUX,
		f_LINE_IOS_OR_WINBEGIN,
		f_LINE_WINDOWS
	};
	TFiniteStateMachine<char, TCntStates>
	fsmForPosCounter{
		TCntStates::START,
		{TCntStates::f_COLUMN, TCntStates::f_LINE_IOS_OR_WINBEGIN, TCntStates::f_LINE_LINUX, TCntStates::f_LINE_WINDOWS}
	};

	fsmForPosCounter
	(TCntStates::START, 					'\n', 	TCntStates::f_LINE_LINUX)
	(TCntStates::START, 					'\r', 	TCntStates::f_LINE_IOS_OR_WINBEGIN)
	(TCntStates::START, 							TCntStates::f_COLUMN)
	(TCntStates::f_LINE_IOS_OR_WINBEGIN, 	'\n', 	TCntStates::f_LINE_WINDOWS);

	TPositionCounter<TCntStates>
	posCounter{
		fsmForPosCounter,
		{TCntStates::f_COLUMN},
		{TCntStates::f_LINE_LINUX, TCntStates::f_LINE_IOS_OR_WINBEGIN, TCntStates::f_LINE_WINDOWS}
	};

	//For Comment Suppressing

	enum class TCommentStates{
		START,
		f_NOCOMMENT,
		MAYBE_COMMENT_BEGIN,
		COMMENT,
		MAYBE_COMMENT_END,
		f_COMMENT_END
	};

	TFiniteStateMachine<char, TCommentStates>
	fsmForComment{
		TCommentStates::START,
		{TCommentStates::f_NOCOMMENT, TCommentStates::f_COMMENT_END}
	};

	fsmForComment
	(TCommentStates::START, 				'(', 	TCommentStates::MAYBE_COMMENT_BEGIN)
	(TCommentStates::START, 				'(', 	TCommentStates::f_NOCOMMENT)
	(TCommentStates::START,      				 	TCommentStates::f_NOCOMMENT)
	(TCommentStates::MAYBE_COMMENT_BEGIN, 	'*', 	TCommentStates::COMMENT)
	(TCommentStates::COMMENT, 				'*', 	TCommentStates::MAYBE_COMMENT_END)
	(TCommentStates::COMMENT, TCommentStates::COMMENT).except(TCommentStates::COMMENT, '\0')
	(TCommentStates::MAYBE_COMMENT_END, 	'*', 	TCommentStates::MAYBE_COMMENT_END)
	(TCommentStates::MAYBE_COMMENT_END, 	')', 	TCommentStates::f_COMMENT_END)
	(TCommentStates::MAYBE_COMMENT_END, TCommentStates::COMMENT).except(TCommentStates::MAYBE_COMMENT_END, '\0');

	TCommentFilter<TCommentStates>
	commentFilter{
		fsmForComment,
		{TCommentStates::f_COMMENT_END}
	};

	//For Token Extraction

	enum class TTokenExtractState{
		start,

		f_intval, pre_int1,
				  pre_int11,
		f_realval, pre_real1, pre_real_dot1, pre_real2,
				   pre_real11, pre_real_mantissa11, pre_real22, pre_real_mantissa22,
				   pre_real111, pre_real222, pre_real333, pre_real_mantissa111, pre_real_mantissa222, pre_real_dot111,
		f_strval, pre_str1, pre_str_quote1, pre_str_quote2, pre_str11, pre_str22, pre_str33,
		f_id,
		f_le,
		f_ge,
		f_eq,
		f_add,
		f_sub,
		f_mul,
		f_div,
		f_ass, pre_ass1,
		f_semicolom,
		f_colom,
		f_lbr,
		f_rbr,
		f_lbrind,
		f_rbrind,
		f_eof,
	};
	TTokenExtractor<TTokenExtractState>
	tokenExtractor{
		TTokenExtractState::start,
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
		TTokenExtractState::f_eof }
	};
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
	tokenExtractor
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
		(TTokenExtractState::pre_str1, TTokenExtractState::pre_str1).except(TTokenExtractState::pre_str1, {'\'', '\0'})
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

#define MAKE_STATE_CLASS( x ) { TTokenExtractState::f_ ## x, TToken::TTokenClass::_ ## x }

	const map<const TTokenExtractState, const TToken::TTokenClass> StateClass{
		MAKE_STATE_CLASS(intval),
		MAKE_STATE_CLASS(realval),
		MAKE_STATE_CLASS(strval),
		MAKE_STATE_CLASS(id),
		MAKE_STATE_CLASS(le),
		MAKE_STATE_CLASS(ge),
		MAKE_STATE_CLASS(eq),
		MAKE_STATE_CLASS(add),
		MAKE_STATE_CLASS(sub),
		MAKE_STATE_CLASS(mul),
		MAKE_STATE_CLASS(div),
		MAKE_STATE_CLASS(ass),
		MAKE_STATE_CLASS(semicolom),
		MAKE_STATE_CLASS(colom),
		MAKE_STATE_CLASS(lbr),
		MAKE_STATE_CLASS(rbr),
		MAKE_STATE_CLASS(lbrind),
		MAKE_STATE_CLASS(rbrind),
		MAKE_STATE_CLASS(eof)
	};

	string srcString{"asd+4+2.5"};
	vector<char> destString;


	srcString >> posCounter >> commentFilter >> tokenExtractor;

	try{
		vector<TToken> tokenSequence;
		while (tokenSequence.empty() || tokenSequence.back().getClass() != TToken::TTokenClass::_eof){
			auto pos = posCounter.getPosition();
			while(tokenExtractor >> destString);

			if (tokenExtractor.IsMachineAccept()){
				auto states = tokenExtractor.getLastFinalStates();
				if (states.size() > 1)
					throw "Ambiguous string: " + string(destString.begin(), destString.end());

				int rollBackNum = tokenExtractor.getSymbolNumberAfterLastFinalState();
				for (; rollBackNum; rollBackNum--)
					tokenExtractor << destString;

				tokenSequence.push_back(TToken(StateClass.find(*states.begin())->second,
												string(destString.begin(), destString.end()),
												{pos.line, pos.column}));
				destString.clear();
				tokenExtractor.Reset();
			}
			else{
				throw "There is no token for the string: " + string(destString.begin(), destString.end());
			}
			cout << tokenSequence.back() << endl;
		}
	}
	catch(...){
		cout << "fuck!" << endl;
	}

	return 0;
}
