//============================================================================
// Name        : LTADataPro.cpp
// Author      : zhou jingbo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "xmlParser/LTADataParser.h"

int main() {


	LTADataParser ltaParser;
	//ltaParser.loadTravelTimeSetDataFile();
	//ltaParser.loadCarparksLotsDataFile();
	ltaParser.covertCarparksLots2CSV();


	return 0;
}
