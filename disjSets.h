/*************************************************************************************
 Title          : disjSets.h
 Author         : Xiaoning Wang
 Created on     : May 4, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The interface file for DisjSets class
 Purpose        : Determining the disjoint sets of subway stations. Make the parent tree.
 ************************************************************************************/

#ifndef DISJSETS_H
#define DISJSETS_H
#include <vector>
#include <string>
#include <list>
using namespace std;
class DisjSets {

public:
    DisjSets (int );
    void addNode(int);
    void updateNode(int,int);
    void unionSet (int,int);
    int find (int);

private:
    vector<int>s;
};
#endif //DISJSETS_H
