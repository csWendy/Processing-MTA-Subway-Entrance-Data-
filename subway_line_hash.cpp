/*************************************************************************************
 Title          : subway_line_hash.cpp
 Author         : Xiaoning Wang
 Created on     : May 5, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The .cpp file for subway_line_hash class
 Purpose        : Create a hash table for subway line.
 ************************************************************************************/

#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "subway_line_hash.h"



SubwayLineHash::SubwayLineHash()
{
    _capacity = 1024;
    _pTable = new Entry[_capacity];
    _size = 0;
    primeIndex = 1;
}
SubwayLineHash::SubwayLineHash(int tableSize) {

    SubwayLineHash::_capacity = tableSize;
    _pTable = new Entry[_capacity];
    _size = 0;
    primeIndex = 1;
}

SubwayLineHash::~SubwayLineHash()
{
    clear();
}

int SubwayLineHash::nextPrime()
{
    int p =(int)pow(static_cast<float>(primeIndex),2) - primeIndex + 41;
    primeIndex = primeIndex << 1;
    if(primeIndex >= 41){
        cout << "Max capacity reached. exit!" << endl;
        exit(-1);
    }
    return p;
}

bool SubwayLineHash::find(const Entry&  e)
{
    return(find(e._key));
}

bool SubwayLineHash::find(const KeyType& k)
{
    _pos = hashFunction(k);

    if(_pTable[_pos]._key==NULLKEY)
        return false;
    int lastPos = _pos;

    while(_pTable[_pos]._key!=k){

        if(++_pos%_capacity == lastPos)
            return false;
    }

    return true;
}

bool SubwayLineHash::insert(const Entry& e)
{
    if((_size*1.0)/_capacity>0.75)
        rehash();    if(find(e))
        return false;
    _pTable[_pos] = e;
    ++_size;
    return true;
}

bool SubwayLineHash::remove(const Entry& e)
{
    if(!find(e))
        return false;
    _pTable[_pos]._key = NULLKEY;
    --_size;
     //rehash();
    return true;
}

void SubwayLineHash::clear()
{
    delete []_pTable;
    _size = _capacity = 0;
}

Entry& SubwayLineHash::operator[](KeyType key)
{
    if(!find(key))
        insert(Entry(key,0));
    return _pTable[_pos];
}

int SubwayLineHash::size()
{
    return _size;
}

int SubwayLineHash::hashFunction(KeyType key)
{
    int keyNum =0;
    for(unsigned  int i=0;i<key.size();i++){
        keyNum+=(int)key.c_str()[i];
    }
    return keyNum%_capacity;
}

void SubwayLineHash::display()
{
    cout << "capacity = " << _capacity << ", size = " << _size << endl;
    for(int i=0; i<_capacity; i++){
        if(_pTable[i]._key!=NULLKEY)
            cout << "key=" << _pTable[i]._key << ",value=" << _pTable[i]._value << endl;
    }
}


void SubwayLineHash::rehash()
{
    cout << "begin rehash..." << endl;
    Entry *p = new Entry[_size];s
    for(int i=0; i<_capacity; i++){
        if(_pTable[i]._key != NULLKEY)
            *(p+i) = _pTable[i];
    }
    delete []_pTable;
    int lastSize = _size;
    _size = 0;

    _capacity = nextPrime();
    _pTable = new Entry[_capacity];
    for(int i=0; i<lastSize; i++)
        insert(*(p+i));
    delete []p;
}  
