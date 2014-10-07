#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <vector>
#include "Utilities.h"


int strToInt(std::string data){
	if (data.empty()){
		return NUMBER_NOT_SPECIFIED;
	}

	return std::atoi(data.c_str());
}

float strToFloat(std::string data){
	if (data.empty()){
		return NUMBER_NOT_SPECIFIED;
	}

	return std::atof(data.c_str());
}

// trim from start
std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
std::string trim(const char* inputChar) {
	if (inputChar == 0)
	{
		return inputChar;
	}
	std::string* inputStr = new std::string(inputChar);
	return ltrim(rtrim(*inputStr));
}

std::string trim(std::string inputStr) {
	if (inputStr.empty())
	{
		return inputStr;
	}	
	return ltrim(rtrim(inputStr));
}

// split function implementation
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
    }
    return elems;    
}

std::vector<int> splitAndParseInt(const std::string &s, char delim){
	std::vector<int> elems;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(strToInt(item));
		}
    }
    return elems;
}


std::vector<float> splitAndParseFloat(const std::string &s, char delim){
	std::vector<float> elems;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(strToFloat(item));
		}
    }
    return elems;
}
