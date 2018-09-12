/*************************************************************************************
 Title          : subway_entrance.h
 Author         : Xiaoning Wang
 Created on     : May 2, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The interface file for SubwayEntrance class
 Purpose        : Create a subway entrance for each line reading from the csv file.
 ************************************************************************************/

#ifndef SUBWAY_ENTRANCE_H
#define SUBWAY_ENTRANCE_H

#include<iostream>
#include<string>
#include <limits.h>
using namespace std;
using std::string;

class SubwayEntrance{
public:
    SubwayEntrance(const string& entranceData);//A constructor for the class that takes a string from a csv file.
    SubwayEntrance (int id, string name, string url,string lines);
    SubwayEntrance();
    void setParentId(int parentId);
    void setMask(const int& num);
    const int getParentId()const;
    const int getId()const;
    const string getName()const;
    const string getUrl()const;
    vector<string>  getLines()const;
    const int getType()const;
    const double getLatitude()const;
    const double getLongitude()const;
    const int getEntranceMask()const;
    
    /**
     * purpose: check if two entrances are same entrances.
     * @return true or false.
     */
    friend bool operator ==(const SubwayEntrance& e1, const SubwayEntrance& e2);
    
    /**
     * purpose: use to get the line idetifiers seperated by "-".
     * @param: a long string of s is to be splited according to a short string of c("-" in this project.)
     * return: a vector of strings contained every splited array from s.
     */
    vector<string> SplitString(const string& s,const string& c);

private:
    string entranceName;
    int entranceId;
    string  serverUrl ;
    vector<string>  lines;
    int parentId;
    double latitude;
    double longitude;
    int entranceType;//1: exit only; 0: normal entrance.
    int mask;
};
#endif //SUBWAY_ENTRANCE_h
