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
#include "Parser.h"
#include "SyntaxException.h"
#include "ParseTree.h"

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

	string fileStringContent{};
	fstr.seekg(0, std::ios::end);
	fileStringContent.reserve(fstr.tellg());
	fstr.seekg(0, std::ios::beg);
	fileStringContent.assign(std::istreambuf_iterator<char>(fstr),
							 std::istreambuf_iterator<char>());

	Scaner scaner{};
	scaner.Configurate(fileStringContent);
	Parser parser{};
	parser.Configurate();
	ofstream outFile(DefaultOutFileName);
	try{
		//Lexical analyze
		vector<TToken> tokens{};
		do{
			tokens.push_back(scaner.getNextToken());
		}while (tokens.back().getClass() != TToken::TTokenClass::_eof);

		outFile << "Lexical analyze:" << endl;
		for (auto it = tokens.begin(); it != tokens.end(); it++)
			outFile << *it << endl;
		//Syntax analyze
		tokens.pop_back();
		parser.setInput(tokens);
		ParseTree parseTree = parser.Parse();
		outFile << "Syntax analyze:" << endl;
		outFile << parseTree;
	}
	catch(TLexicalException& e){
		outFile << "Lexical error:" << endl;
		outFile << e.what() << endl;
	}
	catch(SyntaxException& e){
		outFile << "Syntax error:" << endl;
		outFile << e.what() << endl;
	}
	catch(...){
		outFile << "Unknown error occurred while compile" << endl;
	}

	return 0;
}
