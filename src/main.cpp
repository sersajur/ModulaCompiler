//============================================================================
// Name        : main.cpp
// Author      : sersajur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>

#include "Scaner.h"
#include "TToken.h"
#include "TLexicalException.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

const char* DefaultOutFileName = "./out.txt";

int main(int argn, const char* argv[]){
	if (argn != 2){
		cout << "Usage: mlc <filename>" << endl;
		return 1;
	}

	ifstream fstr(argv[1]);
	if (!fstr.is_open()){
		cout << "Can't open file: \"" << argv[1] << '\"' << endl;
		return 1;
	}

	string fileStringContent;
	fstr.seekg(0, std::ios::end);
	fileStringContent.reserve(fstr.tellg());
	fstr.seekg(0, std::ios::beg);
	fileStringContent.assign(std::istreambuf_iterator<char>(fstr),
							 std::istreambuf_iterator<char>());
	Scaner scaner;
	scaner.Configurate(fileStringContent);

	ofstream outFile(DefaultOutFileName);
	try{
		TToken token = scaner.getNextToken();
		while (token.getClass() != TToken::TTokenClass::_eof){
			outFile << token << endl;
			token = scaner.getNextToken();
		}
		outFile << token << endl;
	}
	catch(TLexicalException& e){
		cout << "Lexical error:" << endl;
		cout << e.what() << endl;
	}
	catch(...){
		cout << "Unknown error occurred while compile" << endl;
	}

	return 0;
}
