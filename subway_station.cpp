/*************************************************************************************
 Title          : subway_station.h
 Author         : Xiaoning Wang
 Created on     : May 3, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The cpp file for SubwayStation class
 Purpose        : Create a subway station according to the connected subway entrances.
 ************************************************************************************/


#include<iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include<string>
#include<stdlib.h>
#include <algorithm>
#include <cctype>

#include "subway_station.h"

SubwayStation::SubwayStation() {

}

SubwayStation::SubwayStation(const SubwayEntrance &entrance ) {
    entrances.push_back(entrance);
    stationId = entrance.getId();
    setLocation(entrance.getLatitude(),entrance.getLongitude());
    stationLines = entrance.getLines();
    stationName = entrance.getName();
    stationMask = entrance.getEntranceMask();
}

//Add subwayEntrance to subwayStation
void SubwayStation::updateStation(const SubwayEntrance &entrance) {

    vector<SubwayEntrance>::iterator ret;
    ret = find(entrances.begin(), entrances.end(), entrance);
    if(ret == entrances.end()){ //no entrance match, return entrances.end().
        entrances.push_back(entrance);
    }

    double newLatitude = (getLatitude()+entrance.getLatitude())/2;
    double newLongitude = (getLongitude()+entrance.getLongitude())/2;
    setLocation(newLatitude,newLongitude);//update the coordinators by the central coordinates caculated above.
}

//merge the two stations.
void SubwayStation::mergeStation(SubwayStation &s2) {
    vector<SubwayEntrance> s2E = s2.getEntrances();
    SubwayStation::entrances.insert( SubwayStation::entrances.end(),s2E.begin(),s2E.end());//insert s2E to the end of s1E
    double newLatitude = (getLatitude()+s2.getLatitude())/2;
    double newLongitude = (getLongitude()+s2.getLongitude())/2;
    setLocation(newLatitude,newLongitude);//update the coordinators.

}

void SubwayStation::setLocation(const double &latitude, const double &longitude) {
    SubwayStation::stationLatitude = latitude;
    SubwayStation::stationLongitude = longitude;
}

const int SubwayStation::getStationId() const {
    return SubwayStation::stationId;
}
const double SubwayStation::getLongitude() const {
    return SubwayStation::stationLongitude;
}
const double SubwayStation::getLatitude() const {
    return SubwayStation::stationLatitude;
}
const string SubwayStation::getName() const {
    return SubwayStation::stationName;
}
vector<string> SubwayStation::getLines() const {
    return SubwayStation::stationLines;
}
const int SubwayStation::getStationMask() const {
    return SubwayStation::stationMask;
}

bool operator !=( const SubwayStation& s1, const SubwayStation& s2){

    string s1_name = s1.getName();
    string s2_name = s2.getName();
    string::size_type index1 = 0;
    string::size_type index2 = 0;

    if(!s1_name.empty() && !s2_name.empty()){
        while((index1 = s1_name.find(' ',index1)) != string::npos) {
            s1_name.erase(index1,1);
        }
        while((index2 = s2_name.find(' ',index2)) != string::npos) {
            s2_name.erase(index2,1);
        }

        transform(s1_name.begin(),s1_name.end(),s1_name.begin(),::tolower);
        transform(s2_name.begin(),s2_name.end(),s2_name.begin(),::tolower);

        if(s1_name != s2_name && s1.getStationId() != s2.getStationId()){
            return true;
        }

    }

    return false;
}

vector<SubwayEntrance> SubwayStation::getEntrances() const {

    return SubwayStation::entrances;
}



