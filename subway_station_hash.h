/*************************************************************************************
 Title          : subway_station_hash.h
 Author         : Xiaoning Wang
 Created on     : May 6, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The interface file for subway_station_hash class
 Purpose        : Create a hash table for subway station.
 ************************************************************************************/
#ifndef SUBWAY_STATION_HASH_H
#define SUBWAY_STATION_HASH_H
#pragma once
#include <iostream>
#include "subway_station.h"
#include "subway_entrance.h"
using namespace std;

typedef int SKeyType;
#define SNULLKEY -1

//purpose: a struct for a subwayStation entry
struct SEntry{
    SKeyType _key;
    SubwayStation  _value;
    SEntry(SKeyType key=SNULLKEY, SubwayStation& value=*new SubwayStation()):_key(key),_value(value){}
};

class SubwayStationHash{

public:
    SubwayStationHash();
    //SubwayStationHash(int tableSize);
    ~SubwayStationHash();

    bool find(const SEntry&  e);
    bool insert(const SEntry& e);
    bool remove(const SEntry& e);
    void clear();
    
    /**
     * purpose: overload operator[]. insert SEntry(key,0) if not found.
     * return pointer to the current position.
     */
    SEntry& operator[](SKeyType key);
    int size();
    void display();

protected:
    /**
     * purpose: the hashfunction for the hash table.
     * return: key % _capacity.
     */
    int hashFunction(SKeyType key);//将键值映射到对应地址
    
    void rehash();
    
    /**
     * purpose: find the pointer of SEntry(*_pTable) by key.
     * return true if find. return false if not find.
     */
    bool find(const SKeyType& k);
    
    /**
     * purpose:find the next prime number.
     * return: p(n) = n^2 - n + 41, n<41, p<1681
     */
    int nextPrime();

private:
    SEntry *_pTable;// a pointer of type SEntry pointing to a hash table with "_capacity" entries.
    int _pos;//position of the currently visiting SEntry//当前访问元素的位置
    int _size;// the occupied entries number in the hashtable.
    int _capacity;// the maximum number of entries in the hash table.

    int primeIndex;

};


#endif //SUBWAY_STATION_HASH_H
