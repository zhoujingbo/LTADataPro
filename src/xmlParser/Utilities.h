#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <vector>
#include <map>

#include <time.h>       /* time_t, struct tm, time, mktime */
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define NUMBER_NOT_SPECIFIED -1


int strToInt(std::string data);

float strToFloat(std::string data);

// c++ has no trim function. So we need to implement it by ourselves
std::string &ltrim(std::string &s);
std::string &rtrim(std::string &s);
std::string trim(std::string inputChar);

// c++ has no split function. So we need to implement it by ourselves
std::vector<std::string> split(const std::string &s, char delim);
std::vector<int> splitAndParseInt(const std::string &s, char delim = ' ');
std::vector<float> splitAndParseFloat(const std::string &s, char delim = ' ');



class LotsSetMap{

public:
	LotsSetMap(){

	}
	virtual ~LotsSetMap(){

	}


public:
	map<std::string, std::vector<int> >::iterator find(string key){


		map<string,vector<int> >::iterator itr = lotsSet.find(key);
		if(itr!=lotsSet.end()) return itr;

		struct tm key_time;

		strptime(key.c_str(), "%Y-%m-%dT%H:%M", &key_time);
		int min = key_time.tm_min;
		for(int i=-1;i<2;i++){

			key_time.tm_min= min+i;
			mktime(&key_time);

			char key_var_char[256];
			strftime(key_var_char,sizeof(key_var_char),"%Y-%m-%dT%H:%M", &key_time);
			string key_var(key_var_char);
			itr = lotsSet.find(key_var);
			if(itr!=lotsSet.end()){
				return itr;
			}
		}


		return lotsSet.end();

	}

	map<std::string, std::vector<int> >::iterator end(){
		return lotsSet.end();
	}




public:
	std::map<std::string, std::vector<int> > lotsSet;

};

#endif
