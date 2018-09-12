/*************************************************************************************
 Title          : subway_line_hash.h
 Author         : Xiaoning Wang
 Created on     : May 5, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The interface file for subway_line_hash class
 Purpose        : Create a hash table for subway line.
 ************************************************************************************/

#ifndef SUBWAY_LINE_HASH_H
#define SUBWAY_LINE_HASH_H
#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef string KeyType;
#define NULLKEY "NullKey"

//a struct for a subwayStation entry
struct Entry{
    KeyType _key;
    int     _value;
    Entry(KeyType key=NULLKEY, int value=0):_key(key),_value(value){}
};

class SubwayLineHash{

public:
    SubwayLineHash();
    SubwayLineHash(int tableSize);
    ~SubwayLineHash();

    bool find(const Entry&  e);
    bool insert(const Entry& e);
    bool remove(const Entry& e);
    void clear();
    Entry& operator[](KeyType key);
    int size();
    void display();

protected:
    int hashFunction(KeyType key);
    void rehash();
    bool find(const KeyType& k);
    int nextPrime();//p(n) = n^2 - n + 41, n<41, p<1681

private:
    Entry *_pTable;// a pointer of type Entry pointing to a hash table with "_capacity" entries.
    int _pos;//position of the currently visiting element./当前访问元素的位置
    int _size;// the occupied entries number in the hashtable.
    int _capacity;// the maximum number of entries in the hash table.
    int primeIndex;
};

#endif //SUBWAY_LINE_HASH_H
