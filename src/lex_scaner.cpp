/*
 * lex_scaner.cpp
 *
 *  Created on: 1 бер. 2015
 *      Author: sersajur
 */

#include "lex_scaner.h"

namespace LEX{

	Lex_scaner::~Lex_scaner()
	{

	}
	Lex_scaner::Lex_scaner(const string&  i_str):
			m_stream(i_str),
			m_startPos{0}, m_curPos{0},
			m_curLine{1}, m_curColum{1}
	{

	}
	void Lex_scaner::readNextTerm()
	{
		if (currentTerm().isEOF())
			throw LexException("Lex_scaner::readNextTerm is trying to step out of the m_stream.");

		if (currentTerm().isEndl())
		{
			m_lastColum.push_back(m_curColum);
			m_curColum = 1;
			++m_curLine;
		}
		else
			++m_curColum;

		++m_curPos;
	}
	void Lex_scaner::machineBackStep(pos i_stepsNumber)
	{
		/* Exceptions */
		if (m_curPos < i_stepsNumber)
			throw LexException("Lex_scaner::machineBackStep is trying to step back out of the m_stream.");

		for (; i_stepsNumber; i_stepsNumber--)
		{
			--m_curPos;

			if (currentTerm().isEndl())
			{
				--m_curLine;
				m_curColum = m_lastColum.back();
				m_lastColum.pop_back();
			}
			else
				--m_curColum;
		}
	}
	LexType Lex_scaner::getLexeme(Lexeme& io_lexeme)
	{
		AutomatInternalState state = AutomatInternalState::q_START;


		return LexType::LXDELIMITER;
	}

}

