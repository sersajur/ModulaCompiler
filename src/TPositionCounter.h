/*
 * TPositionCounter.h
 *
 *  Created on: Apr 15, 2015
 *      Author: sersajur
 */

#ifndef TPOSITIONCOUNTER_H_
#define TPOSITIONCOUNTER_H_

#include <set>
#include <vector>
#include <string>

#include "TStringConveyor.h"
#include "TFiniteStateMachine.h"
#include "TLexicalException.h"

using std::set;
using std::pair;
using std::vector;
using std::string;

struct TPosition{
	unsigned line;
	unsigned column;
};

template <class N>
class TPositionCounter: public TStringConveyor {
	TFiniteStateMachine<char, N> m_fsm;
	set<N> m_associatedWithColumnChangeFinalStates;
	set<N> m_associatedWithLineChangeFinalStates;
	TPosition m_position;
	vector<unsigned> m_lastLineColumnValue;
public:
	TPositionCounter(){};
	virtual ~TPositionCounter(){};
	TPositionCounter(const TFiniteStateMachine<char, N>& i_fsm,
			const set<N>& i_columnChangingStates, const set<N>& i_lineChangingStates);
	void Reset();
	const TPosition getPosition()const { return m_position; }
private:
	virtual char ProcessSymbol(char i_Symbol) override;
};

/************************************************************************************/
template <class N>
TPositionCounter<N>::TPositionCounter(const TFiniteStateMachine<char, N>& i_fsm,
		const set<N>& i_columnChangingStates, const set<N>& i_lineChangingStates):
m_fsm{i_fsm},
m_associatedWithColumnChangeFinalStates{i_columnChangingStates},
m_associatedWithLineChangeFinalStates{i_lineChangingStates}{
	Reset();
}
/************************************************************************************/
template <class N>
void TPositionCounter<N>::Reset(){
	m_fsm.Reset();
	m_position = {1, 0};
	m_lastLineColumnValue.clear();
}
/************************************************************************************/
template <class N>
char TPositionCounter<N>::ProcessSymbol(char i_symbol){
	if (IsPassAForward()){
		// Finite state machines steps
		vector<char> stringBuffer{i_symbol};
		while (m_fsm.Transit(stringBuffer.back())){
			stringBuffer.push_back(getSymbolFromSource());
		}

		if (!m_fsm.IsMachineAccept()){
			throw TLexicalException("Undefined transition for TPositionCounter");
		}

		// Change positions
		auto finalStates = m_fsm.getLastFinalStates();
		if (TFiniteStateMachine<char, N>::IsThereTargetState(finalStates, m_associatedWithColumnChangeFinalStates)){
			++m_position.column;
		}
		if (TFiniteStateMachine<char, N>::IsThereTargetState(finalStates, m_associatedWithLineChangeFinalStates)){
			++m_position.line;
			m_lastLineColumnValue.push_back(m_position.column);
			m_position.column = 0;
			// Crossplatforming Solution :)
			stringBuffer.erase(stringBuffer.begin(), stringBuffer.end() - m_fsm.getSymbolNumberAfterLastFinalState());
			stringBuffer.insert(stringBuffer.begin(), '\n');
		}

		// StringBuffer management
		ungetToSource(stringBuffer.begin() + 1, stringBuffer.end());
		i_symbol = stringBuffer.front();
	}
	else{
		// Finite state machines step
		m_fsm.Transit(i_symbol);

		if (!m_fsm.IsMachineAccept()){
			throw TLexicalException("Undefined transition for TPositionCounter");
		}

		auto finalStates = m_fsm.getLastFinalStates();
		if (TFiniteStateMachine<char, N>::IsThereTargetState(finalStates, m_associatedWithColumnChangeFinalStates)){
			--m_position.column;
		}
		if (TFiniteStateMachine<char, N>::IsThereTargetState(finalStates, m_associatedWithLineChangeFinalStates)){
			--m_position.line;
			m_position.column = m_lastLineColumnValue.back();
			m_lastLineColumnValue.pop_back();
		}
	}
	m_fsm.Reset();
	return TStringConveyor::ProcessSymbol(i_symbol);
}
#endif /* TPOSITIONCOUNTER_H_ */
