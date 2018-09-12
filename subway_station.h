/*************************************************************************************
 Title          : subway_station.h
 Author         : Xiaoning Wang
 Created on     : May 3, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The interface file for SubwayStation class
 Purpose        : Create a subway station according to the connected subway entrances.
 ************************************************************************************/

#ifndef SUBWAY_STATION_H
#define SUBWAY_STATION_H
#include <vector>
#include <string>
#include <list>
#include "subway_entrance.h"
using namespace std;
class SubwayStation{
public:
    SubwayStation();
    SubwayStation(const SubwayEntrance& entrance);
    
    /**
     * purpose: join the entrance to the station
     * @param entrance
     * return N/A
     */
    void updateStation(const SubwayEntrance& entrance);
    
    /**
     * purpose: merge the two stations
     * @param entrance
     * return N/A
     */
    void mergeStation(SubwayStation& s2);
    void setLocation(const double& latitude,const double& longitude);
    void setEntrances(const vector<SubwayEntrance>& newEntrances);
    vector<SubwayEntrance> getEntrances()const;
    const int getStationId()const;
    const double getLatitude()const;
    const double getLongitude()const;
    const string getName()const;
    const int getStationMask()const;
    vector<string> getLines()const;
    
    /** purpose: overload the operator != to comapare the two stations.
     * two subwaystations.
     * return true or false
     */
    friend bool operator !=( const SubwayStation& s1, const SubwayStation& s2);


private:
    vector<SubwayEntrance> entrances;
    double stationLatitude;
    double stationLongitude;
    string stationName;
    vector<string>  stationLines;
    int  stationMask;
    int  stationId;//stationID = entrance.getID().

};
#endif //SUBWAY_STATION_H
