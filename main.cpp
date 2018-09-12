/*******************************************************************************
 Title          : main.cpp
 Author         : Xiaoning Wang
 Created on     : May 8, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The main function for implement the commands
 Purpose        : call the SubwaySystem class to implements the commands.
 *******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <cstring>
#include <string>
#include "subway_system.h"
#include "command.h"


using namespace std;

/*********************************************************************
 * purpose: output all the stationsaccording to the input line.
 * @param: lineIdentifier and subwaySystem
 *********************************************************************/
void listLineStations (string& lineIdentifier,SubwaySystem& subwaySystem){
    subwaySystem.printStationNameByLine(lineIdentifier);

}

/***********************************************************************
 * purpose: output all the stations in the subway system
 * @param: subwaySystem
 ************************************************************************/
void listAllStations(SubwaySystem& subwaySystem){
    subwaySystem.printAllStationName();
}

/*************************************************************************
 * purpose:output all the subway entrances that belongs to the input station.
 * @param: stationName and subwaySystem
 ************************************************************************/
void listEntrances(string &stationName,SubwaySystem& subwaySystem){
    subwaySystem.printEntranceName(stationName);
}

/***********************************************************************************************
 * purpose: given longitude and latitude, output the nearest stations, lines or entrances.
 * @param: longitude,latitude,flag, subwaySystem
 * Note: flag 0 : nearest stations; flag 1: nearest lines; flag 2: nearest entrances
 **********************************************************************************************/
void nearestInfo(double& longitude,double& latitude,int flag,SubwaySystem& subwaySystem){

    subwaySystem.printNearestInfo(longitude,latitude,flag);
}

/***********************************************************************************************
 * purpose: read lines from the csv file and create or update system information.
 * @param: SubwaySystem , ifstream
 **********************************************************************************************/
void readCsv(SubwaySystem& subwaySystem,ifstream& inFile){
    string lineStr;

    while (!getline(inFile, lineStr).eof())
    {
        subwaySystem.createSystem(lineStr);
    }
    subwaySystem.updateSystem();

}


/***********************************************************************************************
 
 Below is the main() function
 
 **********************************************************************************************/
int main( int argc,  char* argv[] ) {

    ifstream  fin_csv;
    ifstream  fin_command;
    SubwaySystem subwaySystem;
    Command   command;
    string    stationName,lineName;
    double    longitude,latitude;
    bool      result;

    if (argc < 3 ) {
        cerr << "Usage: " << argv[0] << " commandfile  outputfile\n";
        exit(1);
    }

    fin_csv.open( argv[1]);
    if ( !fin_csv ) {
        cerr << "Could not open" << argv[1] << " for reading.\n";
        exit(1);
    }
    
    //read csv file.
    readCsv(subwaySystem,fin_csv);

    fin_command.open(argv[2]);
    if ( fin_command.fail() ) {
        cerr << "Could not open " << argv[2] << " for reading.\n";
        exit(1);
    }

    // read command file.
    while ( ! fin_command.eof() ) {
        if (!command.get_next(fin_command)) {
            if (!fin_command.eof())
                cerr << "Could not get next command.\n";
            return 1;
        }

        command.get_args(lineName, stationName, longitude, latitude,result);

        switch (command.type_of())
        {
            case list_line_stations_cmmd:

                cout << "command:lineName " << lineName << endl;
                listLineStations(lineName,subwaySystem);
                cout<<"---------------------------------------------------"<<endl;
                break;
            case list_all_stations_cmmd:
                cout << "command:list_all_stations  " << endl;
                listAllStations(subwaySystem);
                cout<<"---------------------------------------------------"<<endl;
                break;
            case list_entrances_cmmd:
                cout << "command:list_entrances  " << stationName<< endl;
                listEntrances(stationName,subwaySystem);
                cout<<"---------------------------------------------------"<<endl;
                break;
            case nearest_station_cmmd:
                cout << "command:nearest_station " << longitude << " " <<latitude<< endl;
                nearestInfo(longitude,latitude,0,subwaySystem);
                cout<<"---------------------------------------------------"<<endl;
                break;
            case nearest_lines_cmmd:
                cout << "command:nearest_line " << longitude << " " <<latitude << endl;
                nearestInfo(longitude,latitude,1,subwaySystem);
                cout<<"---------------------------------------------------"<<endl;
                break;
            case nearest_entrance_cmmd:
                cout << "command:nearest_entrance  " <<longitude  << " " << latitude<< endl;
                nearestInfo(longitude,latitude,2,subwaySystem);
                cout<<"---------------------------------------------------"<<endl;
                break;
            case bad_cmmd:
                cout << "command:bad command " << endl;
                cout<<"---------------------------------------------------"<<endl;
                break;
            default:
                break;
        }
    }
}


