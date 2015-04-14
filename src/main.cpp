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

using namespace std;

int main() {
	string srcStr = "qwer((***)";
	string destStr;
	//TStringConveyor conveyor1, conveyor2, conveyor3;

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

	cout << bool(fsm) << endl;
	while (!srcStr.empty()){
		unsigned i;
		for (i = 0; i < srcStr.length() && fsm; i++){
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
/*
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
*/
//	cout << srcStr << endl;
//	cout << destStr << endl;
	return 0;
}
