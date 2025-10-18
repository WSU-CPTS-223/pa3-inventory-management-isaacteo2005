#ifndef HASHMAP_H
#define HASHMAP_H
#include <iostream>
#include <vector>
#include <list>
#include "HashNode.h"
using namespace std;
template <typename K, typename V>
class HashMap{
    private:
    vector<list<HashNode<K, V>>> map;
    int capacity;
    int size;
    double loadFactor;
    public:
    HashMap(int maxsize = 16, double load = 0.75) : capacity(maxsize), size(0), loadFactor(load){}
    void rehash();

    
};
#endif