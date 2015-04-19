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
bool IsThereTargetState(set<N> i_source, set<N> i_target){
	bool  result = false;
	for (const auto& it : i_target){
		if (i_source.find(it) != i_source.end()){
			result = true;
			break;
		}
	}
	return result;
}
/************************************************************************************/
template <class N>
char TPositionCounter<N>::ProcessSymbol(char i_symbol){
	if (IsPassAForward()){
		// Finite state machines steps
		string stringBuffer{i_symbol};
		while (m_fsm.Transit(stringBuffer.back())){
			stringBuffer += getSymbolFromSource();
		}
		// Change positions
		auto finalStates = m_fsm.getLastFinalStates();
		if (finalStates.empty()){
			throw "TPositionCounter: No final state for fsm.";
		}
		if (IsThereTargetState(finalStates, m_associatedWithColumnChangeFinalStates)){
			++m_position.column;
		}
		if (IsThereTargetState(finalStates, m_associatedWithLineChangeFinalStates)){
			++m_position.line;
			m_lastLineColumnValue.push_back(m_position.column);
			m_position.column = 0;
			stringBuffer.replace(stringBuffer.begin(),
					stringBuffer.end() - m_fsm.getSymbolNumberAfterLastFinalState(), "\n");
		}
		// StringBuffer management
		ungetToSource(stringBuffer.begin() + 1, stringBuffer.end());
		m_fsm.Reset();
		return *stringBuffer.begin();
	}
	else{
		m_fsm.Transit(i_symbol);
		auto finalStates = m_fsm.getLastFinalStates();
		if (finalStates.empty()){
			throw "TPositionCounter: No final state for fsm.";
		}
		if (IsThereTargetState(finalStates, m_associatedWithColumnChangeFinalStates)){
			--m_position.column;
		}
		if (IsThereTargetState(finalStates, m_associatedWithLineChangeFinalStates)){
			--m_position.line;
			m_position.column = m_lastLineColumnValue.back();
			m_lastLineColumnValue.pop_back();
		}
		m_fsm.Reset();
		return i_symbol;
	}
}
#endif /* TPOSITIONCOUNTER_H_ */
