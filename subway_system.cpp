/*************************************************************************************
 Title          : subway_system.cpp
 Author         : Xiaoning Wang
 Created on     : May 1, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The cpp file for SubwaySystem class
 Purpose        : Provide methods to perform all operations required by the program.
 Interact with main() function.
 ************************************************************************************/#include<iostream>
#include <vector>
#include <iterator>
#include<algorithm>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "subway_system.h"
#define R 6372.8
#define TO_RAD (3.1415926536 / 180)
#define DISTANCE 0.28
#define SET_SIZE 10000
#define LINE_HASH_SIZE 1024 //the size of line_hash is set manualy. If the size of database changed, this size has to be changed manualy.

SubwaySystem::SubwaySystem() {
    SubwaySystem::maskNum = 1;
    SubwaySystem::stationHash = new SubwayStationHash();
    SubwaySystem::lineHash = new SubwayLineHash(LINE_HASH_SIZE);
    SubwaySystem::stationIdSet = new DisjSets(SET_SIZE);
}

void SubwaySystem::createSystem(const string &data) {
 //create a new entrance
    SubwayEntrance *newEntrance = new SubwayEntrance(data);
    //create mask
    createMask(*newEntrance);
    //join the set
    SubwaySystem::stationIdSet->addNode(newEntrance->getId());//parentID = -1; entranceID = ID in csv
    SubwaySystem::nameId[convertName(newEntrance->getName())] = newEntrance->getId();
    // add the entrance to its station.
    joinStation(*newEntrance);

}

void SubwaySystem::updateSystem() {

    vector<SubwayStation>::iterator iter = stationSet.begin();
    for (;iter != stationSet.end();iter++ ) {
        SubwaySystem::stationHash->insert(*new SEntry((*iter).getStationId(),*iter));
    }

}

void SubwaySystem::createMask(SubwayEntrance &entrance) {
    vector<string> lines = entrance.getLines();
    vector<string>::iterator iter = lines.begin();
    int tmpMask = 0;
    for (; iter != lines.end(); iter++) {

        if(lineHash->find(*new Entry(*iter))){ // use the key like the line name of "F" to find.
            tmpMask = (*lineHash)[*iter]._value | tmpMask;//tmp Mask = _value or tmpMask.
        } else{

            lineHash->insert(*new Entry(*iter,SubwaySystem::maskNum)) ;
            tmpMask =  SubwaySystem::maskNum | tmpMask;
            SubwaySystem::maskNum *= 2;
        }
    }
    if(tmpMask != 0){
        entrance.setMask(tmpMask);
    }
}

//add entrance to its station
void SubwaySystem::joinStation(const SubwayEntrance &entrance) {
    if(stationSet.size()!=0){
         //trversal the station and use a temp iter.
        vector<SubwayStation>::iterator tmpIter;
        vector<SubwayStation>::iterator iter = stationSet.begin();
        int Flag = 0;
        for (;iter != stationSet.end();iter++) {
            bool isCommonStation = compareEntrance(*iter,entrance); //入口是否属于该站点
            if(isCommonStation){
                if(Flag == 0){
                    (*iter).updateStation(entrance);//站点－入口合并
                    tmpIter = iter;
                    SubwaySystem::stationIdSet->updateNode(entrance.getId(),(*iter).getStationId());//更新并查集
                    Flag = 1;

                }else if(tmpIter!=iter){

                    (*tmpIter).mergeStation(*iter);//站点－站点合并

                    SubwaySystem::stationIdSet->unionSet(tmpIter->getStationId(),(*iter).getStationId());//更新并查集
                    iter = stationSet.erase(iter);//error
                    --iter;

                }
            }

        }

        if(Flag == 0)//站点集合不为空，但没有合适的集合
            stationSet.push_back(*(new SubwayStation(entrance)));

    } else{

        stationSet.push_back(*(new SubwayStation(entrance)));//站点集合为空
    }
}

/**
 * 该入口是否与入口集合中某个入口相似
 * @param entrances
 * @param entrance
 * @return
 */
bool SubwaySystem::compareEntrance(const SubwayStation &station, const SubwayEntrance &entrance) {
    if (station.getStationMask() == entrance.getEntranceMask()) { //the set of line_identifiers for each is identical.
        vector<SubwayEntrance> entrances = station.getEntrances();
        vector<SubwayEntrance>::iterator iter = entrances.begin();
        for (; iter != entrances.end(); iter++) {//the distance between them is at most DISTANCE
            double distance = SubwaySystem::haversine((*iter).getLatitude(), (*iter).getLongitude(),
                                                entrance.getLatitude(), entrance.getLongitude());
            if (distance <= DISTANCE)
                return true;
        }
    }

    return false;
}


int SubwaySystem::getParentId (int childId)  {
    if(childId>0)
        return SubwaySystem::stationIdSet->find(childId);
    return 0;
}

void SubwaySystem::printStationNameByLine(string &lineName) {
    if(!lineName.empty()){
        int mask = (*SubwaySystem::lineHash)[lineName]._value;// get the mask number.
        if(mask>0){
            vector<SubwayStation>::iterator iter = SubwaySystem::stationSet.begin();
            for (; iter != stationSet.end(); iter++) {
                if(((*iter).getStationMask()|mask) == (*iter).getStationMask())
                    cout<<(*iter).getName()<<endl;
            }
        }else{
            cout<<"Line dose not exist"<<endl;
        }

    }
}

 // output all the stations.
void SubwaySystem::printAllStationName() {

    vector<SubwayStation>::iterator iter = SubwaySystem::stationSet.begin();
    cout<<"All "<<stationSet.size()<<"  Stations :"<<endl;
    for (; iter != stationSet.end(); iter++) {
        cout<<(*iter).getName()<<endl;

    }
}

// output all the entrances in a specified station.
void SubwaySystem::printEntranceName(string &stationName) {

    if(!stationName.empty()){
        int childId =SubwaySystem::nameId[convertName(stationName)];//名称处理
        int parentId = getParentId(childId);//错误判断
        SubwayStation parentStation = (*SubwaySystem::stationHash)[parentId]._value;//获得站点对象

        vector<SubwayEntrance> entrances = parentStation.getEntrances();//获得站点入口集合
        vector<SubwayEntrance>::iterator iter = entrances.begin();
        for (;iter != entrances.end();iter++ ) {
            if((*iter).getType()==0)
            cout<<((*iter).getName())<<endl;
        }
    }
}

//Given a point by longitude and latitude, output the nearest entrances, stations or lines.
//flag 0: station; flag 1: line; flag 2 : entrance.

void SubwaySystem::printNearestInfo(double &longitude, double &latitude,int& flag) {

    vector<SubwayStation> tmpStations = SubwaySystem::stationSet;
    vector<SubwayStation>::iterator iter = tmpStations.begin();
    vector<SubwayStation>::iterator  startIndex = iter;
    double minDistance = SubwaySystem::haversine(latitude,longitude,
                                                 (*startIndex).getLatitude(),(*startIndex).getLongitude());
    for (; iter != tmpStations.end(); iter++) {
        double tmpDistance = SubwaySystem::haversine(latitude,longitude,
                                                     (*iter).getLatitude(),(*iter).getLongitude());
        if(tmpDistance < minDistance){
            minDistance = tmpDistance;

            tmpStations.erase(startIndex,iter);//erase elements between startIndex and iter but not startIndex and iter themselves.
            startIndex = --iter;// goes back to the start point after erase.
        }else if(tmpDistance > minDistance){

            tmpStations.erase(iter);
            --iter;
        }
    }

    if(!tmpStations.empty()){
        vector<SubwayStation>::iterator iter2 = tmpStations.begin();
        switch (flag){
            case 0:
            {
                for (; iter2 != tmpStations.end(); iter2++)
                    cout << (*iter2).getName() << endl;
                break;
            }
            case 1:
            {
                vector<string> finalLines=(*iter2).getLines();
                if(tmpStations.size()>1){
                    for (; iter2 != tmpStations.end(); iter2++){
                        finalLines = SubwaySystem::vectorSetUnion(finalLines,(*iter2).getLines());
                    }
                }

                vector<string>::iterator iter21 = finalLines.begin();
                for (; iter21 != finalLines.end(); iter21++){
                    cout<<(*iter21)<<endl;
                }
                break;
            }
            case 2:
            {
                double bestMinDistance = minDistance;
                SubwayEntrance *closedEntrance = new SubwayEntrance();
                for (; iter2 != tmpStations.end(); iter2++){
                    vector<SubwayEntrance> tmpEntrance = (*iter2).getEntrances();
                    vector<SubwayEntrance>::iterator iter22 = tmpEntrance.begin();
                    for (; iter22 != tmpEntrance.end(); iter22++){
                        double tmpDistance = SubwaySystem::haversine(latitude,longitude,
                                                                     (*iter22).getLatitude(),(*iter22).getLongitude());
                        if(tmpDistance < bestMinDistance){
                            bestMinDistance = tmpDistance;
                            *closedEntrance = (*iter22);
                        }
                    }
                }

                if(!closedEntrance->getName().empty()){
                    cout<< closedEntrance->getName()<<endl;
                }


                break;

            }

            default:
            {
                cout<<"error"<<endl;
                break;
            }

        }

    }

}

vector<string> SubwaySystem::vectorSetUnion(vector<string> v1, vector<string> v2) {
    vector<string> v;
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));//get the union of v1 and v2. Then put them into v.
    return v;
}

// convert station names, delete the space, change to lower case.
string SubwaySystem::convertName(const string &stationName) {
    string s1_name = stationName;
    string::size_type index1 = 0;
    if(!s1_name.empty()) {
        while ((index1 = s1_name.find(' ', index1)) != string::npos) {
            s1_name.erase(index1, 1);
        }

        transform(s1_name.begin(), s1_name.end(), s1_name.begin(), ::tolower);
    }
        return s1_name;

}

//compute sphere distance between the given points.
double SubwaySystem::haversine(double lat1, double lon1, double lat2, double lon2)const {
    lat1        = TO_RAD * lat1;
    lat2        = TO_RAD * lat2;
    lon1        = TO_RAD * lon1;
    lon2        = TO_RAD * lon2;
    double dLat = (lat2 - lat1)/2;
    double dLon = (lon2 - lon1)/2;
    double a    = sin(dLat);
    double b    = sin(dLon);
    return 2*R * asin(sqrt(a*a + cos(lat1) * cos(lat2) * b*b));
}

