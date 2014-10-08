/*
 * LTADataParser.h
 *
 *  Created on: Jun 11, 2014
 *      Author: zhoujingbo
 */

#ifndef LTADATAPARSER_H_
#define LTADATAPARSER_H_


#include "pugixml/pugixml.hpp"


#include <string>
using namespace std;

class LTADataParser {

private:
	pugi::xml_document doc;

public:
	LTADataParser();
	virtual ~LTADataParser();

public:
	void loadTravelTimeSetDataFile();
	void loadCarparksLotsDataFile();
	void covertCarparksLots2CSV();
	bool covertCarparksLots2CSV_perDay(string outfileName, string dataFile, int carParkNum, int timeInterval);
};



#endif /* LTADATAPARSER_H_ */
