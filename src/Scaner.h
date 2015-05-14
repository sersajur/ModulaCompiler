/*
 * Scaner.h
 *
 *  Created on: Apr 27, 2015
 *      Author: sersajur
 */

#ifndef SRC_SCANER_H_
#define SRC_SCANER_H_

#include <string>

#include "TToken.h"
#include "TPositionCounter.h"
#include "TTokenExtractor.h"
#include "TOneSymbolExtractor.h"

using std::string;


class Scaner {
private:
	enum class TCntStates{
		START, 	f_COLUMN,
		f_LINE_LINUX,
		f_LINE_IOS_OR_WINBEGIN,
		f_LINE_WINDOWS
	};
	enum class TCommentStates{
		start,
		f_nocomment,
		f_commentBegin1, comment, commentEnd1, commentEnd2
	};
	enum class TWhiteSpaceStates{
		start,
		f_not_white_space,
		whitespace
	};
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
		f_dot,
		f_comma,
		f_lbr,
		f_rbr,
		f_lbrind,
		f_rbrind,
		f_eof,
	};
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
		MAKE_STATE_CLASS(dot),
		MAKE_STATE_CLASS(comma),
		MAKE_STATE_CLASS(eof)
	};

public:
	Scaner();
	virtual ~Scaner();

	void Configurate(const string& i_inputStr);
	void Reset(const string& i_inputStr);
	TToken getNextToken();
	bool IsThatAll() const;
private:
	bool m_lastTokenExtracted;
	string m_srcString;
	TPositionCounter<TCntStates> m_posCounter;
	TOneSymbolExtractor<TCommentStates> m_commentFilter;
	TOneSymbolExtractor<TWhiteSpaceStates> m_whiteSpaceFilter;
	TTokenExtractor<TTokenExtractState> m_tokenExtractor;
};

#endif /* SRC_SCANER_H_ */
