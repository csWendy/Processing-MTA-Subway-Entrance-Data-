/*************************************************************************************
 Title          : subway_station_hash.cpp
 Author         : Xiaoning Wang
 Created on     : May 6, 2018
 Instructor     : Stewart Weiss
 Course         : CSCI 33500
 Assignment     : Project 3
 Description    : The .cpp file for subway_station_hash class
 Purpose        : Create a hash table for subway station.
 ************************************************************************************/

#include <math.h>
#include <stdlib.h>
#include "subway_station_hash.h"



SubwayStationHash::SubwayStationHash()
{
    _capacity = 1024;//初始化SubwayStationHash容量为3,便于观察rehash过程
    _pTable = new SEntry[_capacity];
    _size = 0;
    primeIndex = 1;
}

SubwayStationHash::~SubwayStationHash()
{
    clear();
}

 //p(n) = n^2 - n + 41, n<41, p<1681
int SubwayStationHash::nextPrime()
{
    int p =(int)pow(static_cast<float>(primeIndex),2) - primeIndex + 41;
    primeIndex = primeIndex << 1;
    if(primeIndex >= 41){
        cout << "Max capacity reached. exit!" << endl;
        exit(-1);
    }
    return p;
}

bool SubwayStationHash::find(const SEntry&  e)
{
    return(find(e._key));
}

bool SubwayStationHash::find(const SKeyType& k)
{
    _pos = hashFunction(k);
    if(_pTable[_pos]._key==SNULLKEY)
        return false;
    int lastPos = _pos;
    while(_pTable[_pos]._key!=k){
        if(++_pos%_capacity == lastPos)
            return false;
    }
    return true;
}

bool SubwayStationHash::insert(const SEntry& e)
{
    if((_size*1.0)/_capacity>0.75)
        rehash(); // check if the hash table has to be resized.
    if(find(e))
        return false;
    _pTable[_pos] = e;
    ++_size;
    return true;
}

bool SubwayStationHash::remove(const SEntry& e)
{
    if(!find(e))
        return false;
    _pTable[_pos]._key = SNULLKEY;
    --_size;
    //rehash();//check if the hash table has to reduce size.
    return true;
}

void SubwayStationHash::clear()
{
    delete []_pTable;
    _size = _capacity = 0;
}

SEntry& SubwayStationHash::operator[](SKeyType key)
{

    if(!find(key))
        insert(SEntry(key,*new SubwayStation()));
    return _pTable[_pos];
}

int SubwayStationHash::size()
{
    return _size;
}

int SubwayStationHash::hashFunction(SKeyType key)
{
    return key%_capacity;
}

void SubwayStationHash::display()
{
    cout << "capacity = " << _capacity << ", size = " << _size << endl;
    for(int i=0; i<_capacity; i++){
        if(_pTable[i]._key!=SNULLKEY)
            cout << "key=" << _pTable[i]._key<<endl;
    }
}


void SubwayStationHash::rehash()
{
    cout << "begin rehash..." << endl;
    SEntry *p = new SEntry[_size];//temp save the hash table
    for(int i=0; i<_capacity; i++){
        if(_pTable[i]._key != SNULLKEY)
            *(p+i) = _pTable[i];
    }
    delete []_pTable;
    int lastSize = _size;
    _size = 0;

    _capacity = nextPrime();//p(n) = n^2 - n + 41, n<41, p<1681
    _pTable = new SEntry[_capacity];// create a new hash table of size "_capacity".
    for(int i=0; i<lastSize; i++)
        insert(*(p+i));  // insert the elements to the new table according to (p+i).
    delete []p;
}  
