//============================================================================
// Name        : ModulaCompiler.cpp
// Author      : sersajur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream> /* cout, endl */
#include <fstream> /* ifstream */
#include <string> /* string */
#include <streambuf>
#include "lex_scaner.h" /* Lexeme, Lex_scaner */

using std::filebuf;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
using LEX::Lexeme;
using LEX::Lex_scaner;

const char* OutFileName = "/home/sersajur/workspace/ModulaCompiler/tests/out.txt";

int main(int argn, const char* argv[]){
	/* simple error check  */
	if (argn < 2){
		cout << "Nothing to compile." << endl;
		return 1;
	}

	ifstream streamFile(argv[1]);  //initialize fstream with input files
	if (!streamFile.is_open()) {
		cout << "File does not exist:" << endl;
		cout << argv[1] << endl;
		return 1;
	}
	string strFile;
	streamFile.seekg(0, std::ios::end);
	strFile.reserve(streamFile.tellg());
	streamFile.seekg(0, std::ios::beg);
	strFile.assign( std::istreambuf_iterator<char>(streamFile),
					std::istreambuf_iterator<char>());

	Lex_scaner scaner(&strFile);
	Lexeme lexeme;
	ofstream outstream(OutFileName);
	outstream << LEX::HeaderLine << endl;
	while (scaner.getLexeme(lexeme)){
		outstream << lexeme << endl;
	}

	return 0;
}
