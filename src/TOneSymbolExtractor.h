/*
 * TOneSymbolExtractor.h
 *
 *  Created on: May 2, 2015
 *      Author: sersajur
 */

#ifndef SRC_TONESYMBOLEXTRACTOR_H_
#define SRC_TONESYMBOLEXTRACTOR_H_

#include <vector>
#include "TLexicalException.h"

template <class N>
class TOneSymbolExtractor: public TStringConveyor, public TFiniteStateMachine<char, N> {
public:
	enum class TExtractCondition{
		FirstFinalState, LastFinalState
	};
	TOneSymbolExtractor(TExtractCondition i_cond = TExtractCondition::FirstFinalState);
	TOneSymbolExtractor(const N& i_startState, const std::set<N> i_finalStates, TExtractCondition i_cond = TExtractCondition::FirstFinalState);
	virtual ~TOneSymbolExtractor(){};

	void setExtractCondition(const TExtractCondition& i_cond){m_extractCondition = i_cond;}
	char ProcessSymbol(char i_symbol) override;
private:
	TExtractCondition m_extractCondition;
};

template <class N>
TOneSymbolExtractor<N>::TOneSymbolExtractor(TExtractCondition i_cond):
m_extractCondition{i_cond}{

}

template <class N>
TOneSymbolExtractor<N>::TOneSymbolExtractor(const N& i_startState, const std::set<N> i_finalStates, TExtractCondition i_cond):
TStringConveyor{},
TFiniteStateMachine<char, N>{i_startState, i_finalStates},
m_extractCondition{i_cond}{

}

template <class N>
char TOneSymbolExtractor<N>::ProcessSymbol(char i_symbol){
	if (!IsPassAForward())
		return TStringConveyor::ProcessSymbol(i_symbol);

	std::vector<char> symbolBuffer = {i_symbol};
	switch (m_extractCondition){
	case TExtractCondition::FirstFinalState:
		while (!this->Transit(symbolBuffer.back()).IsMachineAccept() && this->IsMachineWork()){
			symbolBuffer.push_back(getSymbolFromSource());
		}
		if (!this->IsMachineAccept()){
			throw TLexicalException
			("Can't extract symbol by first final states since the latter was not reached");
		}
		break;
	case TExtractCondition::LastFinalState:
		while (this->Transit(symbolBuffer.back()).IsMachineWork()){
			symbolBuffer.push_back(getSymbolFromSource());
		}
		if (!this->IsMachineAccept()){
			throw TLexicalException
			("Can't extract symbol by last final states since the latter was not reached");
		}
		ungetToSource(symbolBuffer, this->getSymbolNumberAfterLastFinalState());
		this->Reset();
		break;
	default:
		throw TLexicalException("Undefined condition for symbol extract");
	}

	return TStringConveyor::ProcessSymbol(symbolBuffer.back());
}


#endif /* SRC_TONESYMBOLEXTRACTOR_H_ */
