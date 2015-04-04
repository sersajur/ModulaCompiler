/*
 * term.cpp
 *
 *  Created on: 22 бер. 2015
 *      Author: sersajur
 */

#include "term.h"

namespace LEX{

	Term::Term(const char& ch)
	{
		this->symbol = ch;
		if (int(ch))
		{
			const auto& it = SymbolClass.find(this->symbol);
			this->classMask = ( (it != SymbolClass.end()) ? it->second :
												SymbolClassMask::UNKNOWN );
		}
		else
			this->classMask = SymbolClassMask::_EOF;
	}

}
