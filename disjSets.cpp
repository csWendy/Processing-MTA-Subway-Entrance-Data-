/*************************************************************************************
 Title          : disjSets.cpp
 Author         : Xiaoning Wang
 Created on     : May 4, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The cpp file for DisjSets class
 Purpose        : Determining the disjoint sets of subway stations. Make the parent tree.
 ************************************************************************************/
#include<iostream>
#include <vector>
#include<string>
#include<stdlib.h>
#include "disjSets.h"

DisjSets::DisjSets(int numElements) : s(numElements) {
//   cout<<s.size()<<endl;
//    for (int i = 0; i < s.size(); i++){
//        cout<<s[i]<<endl;
//        s[i] = -1;
//    }

}
void DisjSets::addNode(int id) {
    if(s[id]==0){
        s[id]=-1;
    }
//    cout <<id<<endl;
//    cout<<s[id]<<endl;
}
void DisjSets::updateNode(int childId,int parentId) {
    s[childId]=parentId;
    if(s[parentId]<0)
        s[parentId]-=1;
}


void DisjSets::unionSet(int root1, int root2) {
    if (root1 != root2) {
//        if (s[root2] < s[root1]) {
//        // root2 is deeper
//            s[root2] += s[root1];
//            s[root1] = root2;
//        } else {
        // root1 is deeper
            s[root1] += s[root2];
            s[root2] = root1;

    }
}

int DisjSets::find(int x) {
    if (s[x] < 0)
        return x;
    else
        return s[x] = find(s[x]);
}
