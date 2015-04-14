//============================================================================
// Name        : main.cpp
// Author      : sersajur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "TStringConveyor.h"

using namespace std;

int main() {
	string srcStr = "";
	string destStr;
	TStringConveyor conveyor1, conveyor2, conveyor3;

	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;
	srcStr >> conveyor1 >> conveyor2 >> conveyor3 >> destStr;



	cout << srcStr << endl;
	cout << destStr << endl;
	return 0;
}
