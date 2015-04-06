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
		const pos OctalStringLength = 3;

		int state = q_START;
		for ( ; ;readNextTerm())
		{
			if ((state == q_START) && currentTerm().is(SymbolClassMask::WHITESPACE)){
				continue;
			}else if ((state == q_START) && currentTerm().is(SymbolClassMask::ODIGIT)){
				state = q_WAIT_OCTAL;
				continue;

			}else if ((state == q_WAIT_OCTAL) && currentTerm().is(SymbolClassMask::ODIGIT)){
				state = q_WAIT_OCTAL;
				continue;
			}else if ((state == q_WAIT_OCTAL) && currentTerm().is('C') &&
							((m_curPos - m_startPos) <= OctalStringLength)){
				state = f_EXTRACT_STR;
			}else if ((state == q_WAIT_OCTAL) && currentTerm().is('B')){
				state = f_EXTRACT_INT;
			}else if ((state == q_WAIT_OCTAL) && currentTerm().is('.')){
				state = q_FRAC_PART1;
				continue;
			}else if ((state == q_WAIT_OCTAL) && currentTerm().is('E')){
				state = q_MANTISSA1;
				continue;
			}else if ((state == q_WAIT_OCTAL) && (currentTerm().is('8') || currentTerm().is('9'))){
				state = q_INT_PART;
				continue;
			}else if (state == q_WAIT_OCTAL){
				machineBackStep();
				state = f_EXTRACT_INT;

			}else if ((state == q_START) && (currentTerm().is('8') || currentTerm().is('9'))){
				state = q_INT_PART;
				continue;

			}else if ((state == q_INT_PART) && currentTerm().is(SymbolClassMask::DIGIT)){
				state = q_INT_PART;
				continue;
			}else if ((state == q_INT_PART) && currentTerm().is('.')){
				state = q_FRAC_PART1;
				continue;
			}else if ((state == q_INT_PART) && currentTerm().is('E')){
				state = q_MANTISSA1;
				continue;
			}else if (state == q_INT_PART){
				machineBackStep();
				state = f_EXTRACT_INT;

			}else if ((state == q_FRAC_PART1) && currentTerm().is(SymbolClassMask::DIGIT)){
				state = q_FRAC_PART2;
				continue;
			}else if (state == q_FRAC_PART1){
				machineBackStep(2);
				state = f_EXTRACT_INT;

			}else if ((state == q_FRAC_PART2) && currentTerm().is(SymbolClassMask::DIGIT)){
				state = q_FRAC_PART2;
				continue;
			}else if ((state == q_FRAC_PART2) && currentTerm().is('E')){
				state = q_MANTISSA0;
				continue;
			}else if (state == q_FRAC_PART2){
				machineBackStep();
				state = f_EXTRACT_REAL;

			}else if ((state == q_MANTISSA0) && (currentTerm().is('+') || currentTerm().is('-'))){
				state = q_MANTISSA01;
				continue;
			}else if ((state == q_MANTISSA0) && (currentTerm().is(SymbolClassMask::DIGIT))){
				state = q_MANTISSA3;
				continue;
			}else if (state == q_MANTISSA0){
				machineBackStep(2);
				state = f_EXTRACT_REAL;

			}else if ((state == q_MANTISSA01) && currentTerm().is(SymbolClassMask::DIGIT)){
				state = q_MANTISSA3;
				continue;
			}else if (state == q_MANTISSA01){
				machineBackStep(3);
				state= f_EXTRACT_REAL;

			}else if ((state == q_MANTISSA1) && (currentTerm().is('+') || currentTerm().is('-'))){
				state = q_MANTISSA2;
				continue;
			}else if ((state == q_MANTISSA1) && currentTerm().is(SymbolClassMask::DIGIT)){
				state = q_MANTISSA3;
				continue;
			}else if (state == q_MANTISSA1){
				machineBackStep(2);
				state = f_EXTRACT_INT;

			}else if ((state == q_MANTISSA2) && currentTerm().is(SymbolClassMask::DIGIT)){
				state = q_MANTISSA3;
				continue;
			}else if ((state == q_MANTISSA2)){
				machineBackStep(3);
				state = f_EXTRACT_INT;

			}else if ((state == q_MANTISSA3) && currentTerm().is(SymbolClassMask::DIGIT)){
				state = q_MANTISSA3;
				continue;
			}else if (state == q_MANTISSA3){
				machineBackStep(1);
				state = f_EXTRACT_REAL;

			}else if ((state == q_START) && currentTerm().is(SymbolClassMask::LETTER)){
				state = q_IDENT;
				continue;
			}else if ((state == q_IDENT) && currentTerm().is(SymbolClassMask::LETTER | SymbolClassMask::DIGIT)){
				state = q_IDENT;
				continue;
			}else if (state == q_IDENT){
				machineBackStep(1);
				state = f_EXTRACT_IDENT;

			}else if ((state == q_START) && currentTerm().is(':')){
				state = q_OP_ASSIGN;
				continue;

			}else if ((state == q_OP_ASSIGN) && currentTerm().is('=')){
				state = f_EXTRACT_OP;
			}else if (state == q_OP_ASSIGN){
				machineBackStep();
				state = f_EXTRACT_DELIMITER;

			}else if ((state == q_START) && currentTerm().is(SymbolClassMask::OPERATOR)){
				state = f_EXTRACT_OP;

			}else if ((state == q_START) && currentTerm().is('\'')){
				state = q_STR0;
				continue;

			}else if ((state == q_STR0) && (currentTerm().isEndl() || currentTerm().isEOF())){
				machineBackStep();
				state = f_EXTRACT_ERROR;
			}else if ((state == q_STR0) && currentTerm().is('\'')){
				state = q_STR1;
				continue;
			}else if (state == q_STR0){
				state = q_STR0;
				continue;

			}else if ((state == q_STR1) && currentTerm().is('\'')){
				state = q_STR2;
				continue;
			}else if (state == q_STR1){
				machineBackStep();
				state = f_EXTRACT_STR;

			}else if (state == q_STR2 && currentTerm().is('\'')){
				state = q_STR0;
				continue;
			}else if (state == q_STR2){
				machineBackStep(2);
				state = f_EXTRACT_STR;
			}

			else if ((state == q_START) && currentTerm().is('(')){
				state = q_COM0;
				continue;

			}else if ((state == q_COM0) && currentTerm().is('*')){
				state = q_COM1;
				continue;
			}else if (state == q_COM0){
				machineBackStep();
				state = f_EXTRACT_DELIMITER;

			}else if ((state == q_COM1) && currentTerm().is('*')){
				state = q_COM2;
				continue;
			}else if ((state == q_COM1) && currentTerm().isEOF()){
				machineBackStep();
				state = f_EXTRACT_ERROR;
			}else if (state == q_COM1){
				state = q_COM1;
				continue;
			}else if ((state == q_COM2) && currentTerm().isEOF()){
				machineBackStep();
				state = f_EXTRACT_ERROR;
			}else if ((state == q_COM2) && currentTerm().is(')')){
				state = f_EXTRACT_COM;
			}else if (state == q_COM2){
				state = q_COM1;
				continue;

			}else if ((state == q_START) && currentTerm().is(SymbolClassMask::DELIMITER)){
				state = f_EXTRACT_DELIMITER;
			}else if ((state == q_START) && currentTerm().isEOF()){
				state = f_EXTRACT_EOF;
			}else{
				state = f_EXTRACT_ERROR;
			}

			switch (state){
			case f_EXTRACT_COM:
				m_startPos = m_curPos + 1;
				state = q_START;
				break;
			case f_EXTRACT_DELIMITER:
				string s = string(m_stream.begin()+m_startPos, m_stream.begin()+m_curPos);
				const auto& el = DelimiterSymbolClassValue.find(s.c_str());
				if (el != s.end()){
					io_lexeme = Lexem{}
				}
			case f_EXTRACT_EOF:
			case f_EXTRACT_ERROR:
			case f_EXTRACT_IDENT:
			case f_EXTRACT_INT:
			case f_EXTRACT_OP:
			case f_EXTRACT_REAL:
			case f_EXTRACT_STR:
			}

		}
		return LexType::LXDELIMITER;
	}

}

