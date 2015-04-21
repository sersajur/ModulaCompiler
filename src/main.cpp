//============================================================================
// Name        : main.cpp
// Author      : sersajur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "TStringConveyor.h"
#include "TFiniteStateMachine.h"
#include "TPositionCounter.h"
#include "TCommentFilter.h"

using namespace std;

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

	string srcString{"t(*dsfdf*y*)"};
	string destString;


	srcString >> posCounter >> commentFilter;
	while(!srcString.empty()){
		commentFilter >> destString;

		cout << posCounter.getPosition().line << ":"
			 << posCounter.getPosition().column << ": "
			 << destString.back() << ' ' << int(destString.back()) << endl;
	}

	return 0;
}
