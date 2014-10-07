#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <vector>

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

#endif
