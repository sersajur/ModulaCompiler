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

using namespace std;

int main() {

	enum States{
		START, 	f_COLUMN,
				f_LINE_LINUX,
				f_LINE_IOS_OR_WINBEGIN,
				f_LINE_WINDOWS
	};
	TFiniteStateMachine<char, States> fsm{START, {f_COLUMN, f_LINE_IOS_OR_WINBEGIN, f_LINE_LINUX, f_LINE_WINDOWS}};
	fsm
	(START, '\n', f_LINE_LINUX)
	(START, '\r', f_LINE_IOS_OR_WINBEGIN)
	(START, f_COLUMN)
	(f_LINE_IOS_OR_WINBEGIN, '\n', f_LINE_WINDOWS);
	TPositionCounter<States> posCounter;
	posCounter = {fsm, {f_COLUMN}, {f_LINE_LINUX, f_LINE_IOS_OR_WINBEGIN, f_LINE_WINDOWS}};

	string srcStr = "firstLine\nnewLinuxLine\rnewIOSLine\r\nnewWindowsLine";
	srcStr >> posCounter;
	string destStr;
	while (!srcStr.empty()){
		posCounter >> destStr;
		cout 	<< posCounter.getPosition().line << ':'
				<< posCounter.getPosition().column << '\t'
				<< destStr.back() << '\t' << int(destStr.back()) << endl;
	}
	cout << "unget Test:\n";
	while (!destStr.empty()){
		cout 	<< posCounter.getPosition().line << ':'
				<< posCounter.getPosition().column << '\t'
				<< destStr.back() << endl;
		posCounter << destStr;
	}
	cout << int('\r');

	//TStringConveyor conveyor1, conveyor2, conveyor3;
/*//For comments
	enum States{
		START,
		f_NOCOMMENT,
		MAYBE_COMMENT_BEGIN,
		COMMENT,
		MAYBE_COMMENT_END,
		f_COMMENT_END};

	TFiniteStateMachine<char, States> fsm{START, {f_NOCOMMENT, f_COMMENT_END}};
	fsm
	(START, '(', MAYBE_COMMENT_BEGIN)
	(START, '(', f_NOCOMMENT)
	(START, f_NOCOMMENT)
	(MAYBE_COMMENT_BEGIN, '*', COMMENT)
	(COMMENT, '*', MAYBE_COMMENT_END)
	(COMMENT, '*', COMMENT)
	(MAYBE_COMMENT_END, ')', f_COMMENT_END);
	bool one_more_step = true;
	cout << bool(fsm) << endl;
	while (!srcStr.empty() || one_more_step){
		if (srcStr.empty())
			one_more_step = false;
		unsigned i;
		for (i = 0; i < srcStr.length()+1 && fsm; i++){
			cout << srcStr[i] << '\t' << ':' << fsm.Transit(srcStr[i]) << endl;
		}
		cout << "Last final states:\n";
		auto f_states = fsm.getLastFinalStates();
		for (auto& it : f_states)
			cout << it << endl;
		cout << "Extracted substring:" << endl;
		if (!f_states.empty()){
			cout << srcStr.substr(0, (i-fsm.getSymbolNumberAfterLastFinalState()))<< endl;
			srcStr.erase(0, (i-fsm.getSymbolNumberAfterLastFinalState()));
		}
		fsm.Reset();
	}
	cout << "Steps after final state:" << endl;
	cout << fsm.getSymbolNumberAfterLastFinalState() << endl;
*/
//	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
//	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
//	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;

//	cout << srcStr << endl;
//	cout << destStr << endl;
	return 0;
}
