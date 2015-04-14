///*
// * TFiniteStateMachine.cpp
// *
// *  Created on: 13 квіт. 2015
// *      Author: sersajur
// */
//
////#include "TFiniteStateMachine.h"
///*
//template <class T, class N>
//TFiniteStateMachine<T, N>::TFiniteStateMachine():
//m_goodFlag{false}, m_symbolNumberAfterLastFinalState{NoStepAfterFinalState}{
//
//}
///************************************************************************************/
//template <class T, class N>
//TFiniteStateMachine<T, N>::TFiniteStateMachine(const N& i_startState, const set<N>& i_finalStates):
//m_possibleFinalStates{i_finalStates},
//m_startState{i_startState}{
//	Reset();
//}
///************************************************************************************/
//template <class T, class N>
//TFiniteStateMachine<T, N>::~TFiniteStateMachine() {
//
//}
///************************************************************************************/
//template <class T, class N>
//void TFiniteStateMachine<T, N>::setTransition(const N& i_currentState, const T& i_inputTerm, const N& i_nextState){
//	m_transitions.insert(pair<pair<N, T>, N>(pair<N, T>(i_currentState, i_inputTerm), i_nextState));
//}
///************************************************************************************/
//template <class T, class N>
//void TFiniteStateMachine<T, N>::setTransition(const N& i_currentState, const set<T>& i_inputTerms, const N& i_nextState){
//	for (auto& it : i_inputTerms){
//		setTransition(i_currentState, *it, i_nextState);
//	}
//}
///************************************************************************************/
//template <class T, class N>
//void TFiniteStateMachine<T, N>::setTransition(const N& i_currentState, const N& i_nextState){
//	m_otherTransitions.insert(pair<N, N>(i_currentState, i_nextState));
//}
///************************************************************************************/
//template <class T, class N>
//void TFiniteStateMachine<T, N>::setTransition(const N& i_currentState, const set<N>& i_nextStates){
//	for (auto& it : i_nextStates){
//		setTransition(i_currentState, *it);
//	}
//}
///************************************************************************************/
//template <class T, class N>
//void TFiniteStateMachine<T, N>::setFinalStates(const set<N>& i_finalStates){
//	m_possibleFinalStates = i_finalStates;
//}
///************************************************************************************/
//template <class T, class N>
//TFiniteStateMachine<T,N>& TFiniteStateMachine<T, N>::operator()(const N& i_currentState, const T& i_inputTerm, const N& i_nextState){
//	setTransition(i_currentState, i_inputTerm, i_nextState);
//	return *this;
//}
///************************************************************************************/
//template <class T, class N>
//TFiniteStateMachine<T,N>& TFiniteStateMachine<T, N>::operator()(const N& i_currentState, const set<T>& i_inputTerms, const N& i_nextState){
//	setTransition(i_currentState, i_inputTerms, i_nextState);
//	return *this;
//}
///************************************************************************************/
//template <class T, class N>
//TFiniteStateMachine<T, N>& TFiniteStateMachine<T, N>::operator()(const N& i_currentState, const N& i_nextState){
//	setTransition(i_currentState, i_nextState);
//	return *this;
//}
///************************************************************************************/
//template <class T, class N>
//TFiniteStateMachine<T, N>& TFiniteStateMachine<T, N>::operator()(const N& i_currentState, const set<N>& i_nextStates){
//	setTransition(i_currentState, i_nextStates);
//	return *this;
//}
///************************************************************************************/
//template <class T, class N>
//void TFiniteStateMachine<T, N>::Reset(){
//	m_currentStates = {m_startState};
//	m_goodFlag = true;
//	m_lastFinalStates.clear();
//	m_symbolNumberAfterLastFinalState = NoStepAfterFinalState;
//}
///************************************************************************************/
//template <class T, class N>
//set<N> TFiniteStateMachine<T, N>::getLastFinalStates()const{
//	return m_lastFinalStates;
//}
///************************************************************************************/
//template <class T, class N>
//int TFiniteStateMachine<T, N>::getSymbolNumberAfterLastFinalState()const{
//	return m_symbolNumberAfterLastFinalState;
//}
///************************************************************************************/
//template <class T, class N>
//TFiniteStateMachine<T,N>& TFiniteStateMachine<T, N>::Transit(const T& i_inputTerm){
//	if (!m_goodFlag){
//		return *this;
//	}
//
//	/* Find transitions */
//	set<N> nextStates;
//	for (auto& it_currentState : m_currentStates){
//		auto& pair_nextStateRange = m_transitions.equal_range(pair<N, T>(*it_currentState, i_inputTerm));
//		if (pair_nextStateRange.first != pair_nextStateRange.second){ /* for transitions <N, T> -> N */
//			for (auto& it = pair_nextStateRange.first; it != pair_nextStateRange.second; it++){
//				nextStates.insert(it->second);
//			}
//		}
//		else{ /* for transitions N -> N */
//			auto& pair_otherNextStateRange = m_otherTransitions.equal_range(*it_currentState);
//			if (pair_otherNextStateRange.first != pair_otherNextStateRange.second){
//				for (auto& it = pair_otherNextStateRange.first; it != pair_otherNextStateRange.second; it++){
//					nextStates.insert(it->second);
//				}
//			}
//		}
//	}
//*/
//	/* If transitions don't exist */
///*	if (nextStates.empty()){
//		m_goodFlag = false;
//		if (m_symbolNumberAfterLastFinalState != NoStepAfterFinalState){
//			++m_symbolNumberAfterLastFinalState;
//		}
//		return *this;
//	}
//*/
//	/* Transitions exist. Update m_currentState, update m_lastFinalStates, update SymbolNumberAfterLastFinalState */
///*	m_currentStates = nextStates;
//	bool atLeastOneFinalFound = false;
//	for (auto& it_state : m_currentStates){
//		if (m_currentStates.find(*it_state) != m_currentStates.end()){
//			if (!atLeastOneFinalFound){
//				m_lastFinalStates.clear();
//				atLeastOneFinalFound = true;
//				m_symbolNumberAfterLastFinalState = 0;
//			}
//			m_lastFinalStates.insert(*it_state);
//		}
//	}
//	if (!atLeastOneFinalFound){
//		if (m_symbolNumberAfterLastFinalState != NoStepAfterFinalState){
//			++m_symbolNumberAfterLastFinalState;
//		}
//	}
//	return *this;
//}
//*/
