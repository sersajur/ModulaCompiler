/*
 * TTokenExtractor.h
 *
 *  Created on: Apr 26, 2015
 *      Author: sersajur
 */

#ifndef SRC_TTOKENEXTRACTOR_H_
#define SRC_TTOKENEXTRACTOR_H_

#include "TStringConveyor.h"
#include "TFiniteStateMachine.h"

template <class N>
class TTokenExtractor: public TStringConveyor, public TFiniteStateMachine<char, N> {
public:
	TTokenExtractor();
	TTokenExtractor(const N& i_startState, const set<N>& i_finalStates);
	virtual ~TTokenExtractor(){};

	operator bool() const override;
	char ProcessSymbol(char i_symbol) override;
};

template <class N>
TTokenExtractor<N>::TTokenExtractor():
	TStringConveyor::TStringConveyor{},
	TFiniteStateMachine<char, N>::TFiniteStateMachine{}{

}

template <class N>
TTokenExtractor<N>::TTokenExtractor(const N& i_startState, const set<N>& i_finalStates):
	TStringConveyor::TStringConveyor(),
	TFiniteStateMachine<char, N>::TFiniteStateMachine(i_startState, i_finalStates){

}

template <class N>
TTokenExtractor<N>::operator bool() const{
	return TFiniteStateMachine<char, N>::IsMachineWork();
}

template <class N>
char TTokenExtractor<N>::ProcessSymbol(char i_symbol){
	if (IsPassAForward())
		this->Transit(i_symbol);

	return TStringConveyor::ProcessSymbol(i_symbol);
}

#endif /* SRC_TTOKENEXTRACTOR_H_ */
