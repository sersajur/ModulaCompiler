/*
 * TCommentFilter.h
 *
 *  Created on: Apr 19, 2015
 *      Author: sersajur
 */

#ifndef TCOMMENTFILTER_H_
#define TCOMMENTFILTER_H_

#include <set>

#include "TStringConveyor.h"
#include "TLexicalException.h"

using std::set;

template <class N>
class TCommentFilter: public TStringConveyor {
	TFiniteStateMachine<char, N> m_fsm;
	set<N> m_commentSuppressionStates;
	//TODO: return comment to the source while backward pass
public:
	TCommentFilter(){};
	virtual ~TCommentFilter(){};
	TCommentFilter(const TFiniteStateMachine<char, N>& i_fsm, const set<N>& i_commentSuppressionStates);
private:
	virtual char ProcessSymbol(char i_symbol) override;
};

/************************************************************************************/
template <class N>
TCommentFilter<N>::TCommentFilter(const TFiniteStateMachine<char, N>& i_fsm, const set<N>& i_commentSuppressionStates):
m_fsm{i_fsm},
m_commentSuppressionStates{i_commentSuppressionStates}{

}
/************************************************************************************/
template <class N>
char TCommentFilter<N>::ProcessSymbol(char i_symbol){
	vector<char> stringBuffer{i_symbol};
	bool nothingToPassYet = true;
	while (nothingToPassYet && IsPassAForward()){

		while (m_fsm.Transit(stringBuffer.back())){
			stringBuffer.push_back(getSymbolFromSource());
		}

		if (!m_fsm.IsMachineAccept()){
			throw TLexicalException("Undefined transition for TCommentFilter");
		}

		auto finalStates = m_fsm.getLastFinalStates();
		if (TFiniteStateMachine<char, N>::IsThereTargetState(finalStates, m_commentSuppressionStates)){
			stringBuffer.erase(stringBuffer.begin(), stringBuffer.end() - m_fsm.getSymbolNumberAfterLastFinalState());
			ungetToSource(stringBuffer.begin(), stringBuffer.end());
			stringBuffer = {getSymbolFromSource()};
		}
		else{
			i_symbol = stringBuffer.front();
			ungetToSource(stringBuffer.begin()+1, stringBuffer.end());
			nothingToPassYet = false;
		}
		m_fsm.Reset();
	}
	return TStringConveyor::ProcessSymbol(i_symbol);
}
#endif /* TCOMMENTFILTER_H_ */
