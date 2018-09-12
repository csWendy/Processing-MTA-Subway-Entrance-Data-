/*************************************************************************************
 Title          : subway_entrance.cpp
 Author         : Xiaoning Wang
 Created on     : May 2, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The .cpp file for SubwayEntrance class
 Purpose        : Create a subway entrance for each line reading from the csv file.
 ************************************************************************************/#include<iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include<string>
#include<stdlib.h>
#include <iterator>
#include <cctype>
#include<algorithm>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "subway_entrance.h"


using namespace std;
using std::string;

SubwayEntrance::SubwayEntrance(const string &entranceData)
{
    if (!entranceData.empty()) {

        string entranceName, serverUrl;
        int parentId = -1;
        int entranceType = 0;// set default entranceType to 0(not "exit only")
        double latitude, longitude;
        vector<string> lines;
        stringstream ss(entranceData);
        string str;
        vector<string> lineArray;

        while (getline(ss, str, ',')) {
            lineArray.push_back(str);
        }


        if (lineArray.size() >= 4) {
            // if the entrance is "exit only", set the entranceType to 1.
            string::size_type pos = lineArray[2].find("exit only");
            if (pos != string::npos)
                entranceType = 1;
            
            // get the float point number of longitude and latitude.
            int start = lineArray[3].find_first_of('(') + 1;
            int end = lineArray[3].find_last_of(")");
            string location = lineArray[3].substr(start, end - start);
            int mid = location.find_first_of(' ');

            longitude = atof(location.substr(0, mid).c_str());
            latitude = atof(location.substr(mid + 1, end - mid).c_str());
            //get the line identifiers.
            lines = SplitString(lineArray[4], "-");

        }

        SubwayEntrance::parentId = parentId;
        SubwayEntrance::entranceType = entranceType;
        SubwayEntrance::entranceId = atoi(lineArray[0].c_str());
        SubwayEntrance::latitude = latitude;
        SubwayEntrance::longitude = longitude;
        SubwayEntrance::entranceName = lineArray[2];
        SubwayEntrance::lines = lines;
    }
}
/**
 *
 */
SubwayEntrance::SubwayEntrance() {


}

void SubwayEntrance::setParentId(int parentId) {

    SubwayEntrance::parentId = parentId;
}
const int SubwayEntrance::getId() const {

    return SubwayEntrance::entranceId;
}

const string SubwayEntrance::getName() const {
    return SubwayEntrance::entranceName;
}

const string SubwayEntrance::getUrl() const {
    return SubwayEntrance::serverUrl;
}

const double SubwayEntrance::getLatitude() const {
    return SubwayEntrance::latitude;
}

const double SubwayEntrance::getLongitude() const {
    return SubwayEntrance::longitude;
}

vector<string> SubwayEntrance::getLines() const {
    return SubwayEntrance::lines;
}

const int SubwayEntrance::getEntranceMask() const {
    return SubwayEntrance::mask;
}

const int SubwayEntrance::getType() const {
    return SubwayEntrance::entranceType;
}
bool operator == (const SubwayEntrance& e1, const SubwayEntrance& e2){
    if(e1.getId() == e2.getId()){
        return true;
    }
    return false;
}

//split the string of line identifier seperated by "-".
vector<string>SubwayEntrance::SplitString(const string& s,const string& c)
{
    vector<string>v;
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        string lineName=s.substr(pos1, pos2-pos1);
        v.push_back(lineName);
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));

    return v;
}

//set mask for subway entrance. 
void SubwayEntrance::setMask(const int &num) {
    SubwayEntrance::mask = num;
}




