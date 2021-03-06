/*
 * LTADataParser.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: zhoujingbo
 */

#include "LTADataParser.h"
#include "Utilities.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <cmath>
#include <numeric>
using namespace std;

LTADataParser::LTADataParser() {
	// TODO Auto-generated constructor stub

}

LTADataParser::~LTADataParser() {
	// TODO Auto-generated destructor stub
}


void LTADataParser::loadTravelTimeSetDataFile(){

	//dataFile = "data/26 Dec 13/TrafficInformation_TravelTimeSet.xml";
	//dataFile = "data/14 Mar 14/TrafficInformation_TravelTimeSet.xml";
	string dataFile = "data/Mar 14/20 Mar 14/TrafficInformation_TravelTimeSet.xml";

	cout<<dataFile<<endl;
	if (!doc.load_file(dataFile.c_str())){
			cout<< "XML open failed!"<<endl;;
			return;

	}
	cout<< "XML load successfully!"<<endl;;


	pugi::xpath_query query("feed/entry/content/m:properties");

	pugi::xpath_node_set result = query.evaluate_node_set(doc);

	//pugi::xpath_node_set resultEntry = result.select_nodes("d:Name");

	string node_direction = "d:Direction";
	string node_start = "d:StartPoint";
	string node_end = "d:EndPoint";
	string node_travelTime = "d:EstimatedTime";
	string node_data = "d:CreateDate";

	string sel_start = "OUTRAM RD";
	string sel_end = "AYE/CTE INTERCHANGE";
	//unsigned int sel_direction = 2;

	int count = 0;
	map<string,vector<int> > travelTimeSet;
	//cout<<d_direction<<", "<<d_start<<", "<<d_end<<", "<<d_travelTime<< ", "<<d_data<<endl<< ", ";
	for(unsigned int i=0;i<result.size();i++){

		unsigned int d_direction = result[i].node().child(node_direction.c_str()).text().as_int(1);
		string d_start = result[i].node().child(node_start.c_str()).text().as_string("");
		string d_end = result[i].node().child(node_end.c_str()).text().as_string("");
		int d_travelTime = result[i].node().child(node_travelTime.c_str()).text().as_int(1);
		string d_data =  result[i].node().child(node_data.c_str()).text().as_string("");

		vector<int>& tt_vec = travelTimeSet[d_start+" # "+d_end];

		tt_vec.push_back(d_travelTime);

		//if(sel_direction==d_direction && sel_start==d_start && sel_end == d_end){
		//if(d_travelTime>8){
		count++;
		cout<<d_direction<<" "<<d_start<<", "<<d_end<<", "<<d_travelTime<< ", "<<d_data<< ", "<<endl;
		//}
		//cout<<d_travelTime<< " "<<d_data<<endl<< " ";

	//	}

		//cout<<"courrentNode.name:"<<currentNode.name()<<" value:"<<currentNode.text()<<endl;
		//cout<<currentNode.child("d:StartPoint").text()<<endl;
	}
	cout<<"total len :"<<count<<endl;

	for(std::map<string,vector<int> >::iterator it = travelTimeSet.begin();it!=travelTimeSet.end();it++){

		//double sum = :std::accumulate(v.rbegin(), v.rend(), 0);
		double sum = 0,sumSquare = 0;
		for(uint j=0;j<it->second.size();j++){
			sum+=it->second.at(j);
			sumSquare+=it->second.at(j)*it->second.at(j);
		}


		double mean = sum/it->second.size();
		double dev = std::sqrt(sumSquare/it->second.size() - mean*mean);
		if(dev>=1)
		cout<<" meam:"<<mean<<"		dev_var:"<<dev<<"		road:"<<it->first<<endl;
	}



//	pugi::xml_node currentNode = result[0].node();

//	cout<<"name:   "<<currentNode.name()<<"   value:"<<currentNode.text()<<endl;


}


void LTADataParser::loadCarparksLotsDataFile(){

	//dataFile = "data/26 Dec 13/TrafficInformation_TravelTimeSet.xml";
		//dataFile = "data/14 Mar 14/TrafficInformation_TravelTimeSet.xml";
		string dataFile = "data/Mar 14/16 Mar 14/CarparksLotsAvailability_CarParkSet.xml";

		cout<<dataFile<<endl;
		if (!doc.load_file(dataFile.c_str())){
				cout<< "XML open failed!"<<endl;;
				return;

		}
		cout<< "XML load successfully!"<<endl;;


		pugi::xpath_query query("feed/entry/content/m:properties");

		pugi::xpath_node_set result = query.evaluate_node_set(doc);

		//pugi::xpath_node_set resultEntry = result.select_nodes("d:Name");

		string node_carParkId = "d:CarParkID";
		string node_place = "d:Development";
		string node_lots = "d:Lots";
		string node_date = "d:CreateDate";

		//string sel_place = "Mandarin Hotel";

		//unsigned int sel_direction = 2;

		int count = 0;
		map<string,vector<int> > lotsSet;
		//cout<<d_direction<<", "<<d_start<<", "<<d_end<<", "<<d_travelTime<< ", "<<d_data<<endl<< ", ";
		for(unsigned int i=0;i<result.size();i++){

			unsigned int d_carParkId = result[i].node().child(node_carParkId.c_str()).text().as_int(1);
			string d_place = result[i].node().child(node_place.c_str()).text().as_string("");
			int d_lots = result[i].node().child(node_lots.c_str()).text().as_int(1);
			string d_date =  result[i].node().child(node_date.c_str()).text().as_string("");

			stringstream keyStr;
			keyStr<<d_carParkId;
			string key = keyStr.str();
			vector<int>& tt_vec = lotsSet[key];

			tt_vec.push_back(d_lots);

			if(d_carParkId==9){
			//if(d_travelTime>8){
			count++;
			cout<<d_carParkId<<" "<<d_place<<", "<<d_lots<< ", "<<d_date<< ", "<<endl;
			//}
			//cout<<d_travelTime<< " "<<d_data<<endl<< " ";

			}

			//cout<<"courrentNode.name:"<<currentNode.name()<<" value:"<<currentNode.text()<<endl;
			//cout<<currentNode.child("d:StartPoint").text()<<endl;
		}
		cout<<"total len :"<<count<<endl;

		for(std::map<string,vector<int> >::iterator it = lotsSet.begin();it!=lotsSet.end();it++){

			//double sum = :std::accumulate(v.rbegin(), v.rend(), 0);
			double sum = 0,sumSquare = 0;
			int max=-1, min=20000;
			for(uint j=0;j<it->second.size();j++){
				sum+=it->second.at(j);
				sumSquare+=it->second.at(j)*it->second.at(j);
				if(it->second.at(j)>max){
					max = it->second.at(j);
				}
				if(it->second.at(j)<min){
					min = it->second.at(j);
				}
			}


			double mean = sum/it->second.size();
			double dev = std::sqrt(sumSquare/it->second.size() - mean*mean);
			if(dev>=0)
			cout<<" mean:"<<mean<<"		dev_var:"<<dev<<"		min:"<<min<<"		max:"<<max<<"		road:"<<it->first<<endl;
		}

		cout<<"total parks:"<<lotsSet.size()<<endl;



	//	pugi::xml_node currentNode = result[0].node();

	//	cout<<"name:   "<<currentNode.name()<<"   value:"<<currentNode.text()<<endl;

}

string getTimeKey(string str){
	unsigned found = str.find_last_of(":");
	string key = str.substr(0,found);
	return key;
}

string getTimeDay(string time_start, int offset){
	time_t now = time(0);
	struct tm* key_time=localtime(&now);

	strptime(time_start.c_str(), "%d %b %y", key_time);

	key_time->tm_mday+=offset;
	mktime(key_time);

	char time_day_char[256];
	strftime(time_day_char,sizeof(time_day_char),"%d %b %y", key_time);
	string time_day(time_day_char);
	//cout<<"time_day:"<<time_day<<endl;
	return time_day;
}

string getTimeMon(string time_start,int offset){
	time_t now = time(0);
	struct tm* key_time=localtime(&now);

	strptime(time_start.c_str(), "%d %b %y", key_time);

	key_time->tm_mday+=offset;
	mktime(key_time);

	char time_mon_char[256];
	strftime(time_mon_char,sizeof(time_mon_char),"%b %y", key_time);
	string time_mon(time_mon_char);
	//cout<<"time_mon:"<<time_mon<<endl;

	return time_mon;

}

void LTADataParser::covertCarparksLots2CSV(){
	string outfileName ="data/lta_carParksLots.csv";
	int carParkNum = 26;
	int timeInterval = 6;
   ////media/hd1/zhoujingbo/data/LTA data/Francis/
	string time_start = "10 Sep 13";

	vector<string> f_data;
	int s_count=0;
	int total=0;

	//clean data
	std::remove(outfileName.c_str());


	for(int i=0;i<400;i++){
	string time_day = getTimeDay(time_start,i);
	string time_mon = getTimeMon(time_start,i);
	cout<<" to process :"<<time_mon<<"/"<<time_day<<endl;
	string dataFile = "/media/hd1/zhoujingbo/data/LTA data/Francis/"+time_mon+"/"+time_day+"/CarparksLotsAvailability_CarParkSet.xml";

	bool status=covertCarparksLots2CSV_perDay(outfileName,dataFile,carParkNum,timeInterval);
	total++;
	if(status==false){
		f_data.push_back(time_day);
	}else{
		s_count++;
	}
	}
	cout<<" total file:"<<total<<" processed with successful number:"<<s_count<<endl;
	cout<<"XML open failed file number:"<<f_data.size() <<" is:"<<endl;
	for(uint i=0;i<f_data.size();i++){
		cout<<f_data[i]<<endl;
	}
}

bool LTADataParser::covertCarparksLots2CSV_perDay(string outfileName, string dataFile, int carParkNum, int timeInterval){

	bool status = true;

	bool file_exist = true;

	ifstream infile (outfileName.c_str());

	if(!infile){
		file_exist = false;

	}

	ofstream outf;

	if(!file_exist){
		outf.open(outfileName.c_str(),  ios::out);

	}else{
		outf.open(outfileName.c_str(),  ios::app);
	}




	if (!doc.load_file(dataFile.c_str())) {
		cout << dataFile<<" XML open failed!" << endl;

		status = false;
	}


	pugi::xpath_query query("feed/entry/content/m:properties");

	pugi::xpath_node_set result = query.evaluate_node_set(doc);

	string node_carParkId = "d:CarParkID";
	string node_place = "d:Development";
	string node_lots = "d:Lots";
	string node_date = "d:CreateDate";


	LotsSetMap lotsSetMap(carParkNum,timeInterval);
	map<int, string> id_name_map;
	//cout<<d_direction<<", "<<d_start<<", "<<d_end<<", "<<d_travelTime<< ", "<<d_data<<endl<< ", ";
	for (unsigned int i = 0; i < result.size(); i++) {

		unsigned int d_carParkId = result[i].node().child(
				node_carParkId.c_str()).text().as_int(1);
		string d_place =
				result[i].node().child(node_place.c_str()).text().as_string("");
		int d_lots = result[i].node().child(node_lots.c_str()).text().as_int(1);
		string d_date =
				result[i].node().child(node_date.c_str()).text().as_string("");

		string key = getTimeKey(d_date);

		lotsSetMap.insert( d_carParkId-1,  key,  d_lots);



		if(id_name_map.find(d_carParkId-1)==id_name_map.end()){
			id_name_map[d_carParkId-1] = d_place;

		}else if(d_place!=id_name_map[d_carParkId-1]){
				cout<<"place id name is changed"<<endl;
				cout<<"d_carParId:"<<d_carParkId-1<<" old name:"<<id_name_map[d_carParkId-1]<<" new name:"<<d_place<<endl;
				exit(1);
		}

	}

	lotsSetMap.padMissingValue();

	cout<<"start writing data of "<<dataFile<<" into file:"<<outfileName<<endl;

	if(!file_exist){
		outf<<"# id name map, ";
		for(std::map<int,string >::iterator it=id_name_map.begin();it!=id_name_map.end();it++){
			outf<<" "<<it->first<<":"<<it->second<<", ";
		}
		outf<<endl;


		cout<<outfileName<<" is first created, "<<"write command line to:"<<outfileName<<endl;
		outf<<"# time,";
		for(int i=0;i<carParkNum;i++){
				outf<<" "<<i<<",";
		}
		outf<<endl;
	}

	for(std::map<string,vector<int> >::iterator it = lotsSetMap.lotsSet.begin();it!=lotsSetMap.lotsSet.end();it++){
		//cout<<it->first<<endl;
		outf<<it->first<<", ";
		for(uint j=0;j<it->second.size();j++){
			outf<<it->second.at(j)<<", ";
		}
		outf<<endl;
	}

	outf.close();

	cout <<dataFile<< " processed successfully! with total time steps:" << lotsSetMap.lotsSet.size() << endl;
	return status;

}
