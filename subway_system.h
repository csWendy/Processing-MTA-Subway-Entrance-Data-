/*************************************************************************************
 Title          : subway_system.h
 Author         : Xiaoning Wang
 Created on     : May 1, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The interface file for SubwaySystem class
 Purpose        : Provide methods to perform all operations required by the program.
 Interact with main() function.
 ************************************************************************************/

#ifndef SUBWAY_SYSTEM_H
#define SUBWAY_SYSTEM_H

#include <vector>
#include <string>
#include <list>
#include <map>

#include "subway_line_hash.h"
#include "subway_station_hash.h"
#include "subway_station.h"
#include "subway_entrance.h"
#include "disjSets.h"

using namespace std;


/***********************************************************************
                     The interface of SubwaySystem class
**********************************************************************/


class SubwaySystem {
public:
    SubwaySystem();
    /**
     * purpose: create a new system.
     * @param: a string which would be passed to SubwayEntrance class to create new entrance.
     * return N/A
     **/
    void createSystem(const string& data);
    void updateSystem();
    void joinStation(const SubwayEntrance& entrance);
    bool compareEntrance(const SubwayStation& station,const SubwayEntrance& entrance);
    void createMask(SubwayEntrance& entrance);
    int getParentId(int childId );

    void printAllStationName();
    void printEntranceName(string& stationName);
    void printStationNameByLine(string& lineName);
    void printNearestInfo(double& longitude,double& latitude,int& flag);
    string convertName(const string& stationName);
    vector<string> vectorSetUnion(vector<string> v1,vector<string> v2);
    double haversine(double lat1, double lon1, double lat2, double lon2)const;



private:
    map<string, int> nameId;
    SubwayLineHash *lineHash;
    SubwayStationHash *stationHash;
    vector<SubwayStation> stationSet;
    DisjSets* stationIdSet;
    int maskNum;
};


#endif //SUBWAY_SYSTEM_H
