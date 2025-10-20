#ifndef HASHMAP_H
#define HASHMAP_H
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "HashNode.h"
using namespace std;
template <typename K, typename V>
class HashMap{
    private:
    vector<list<HashNode<K, V>>> map;
    int capacity;
    int size;
    double loadFactor;
    int hashFunction(const K& key) const{
        hash<K> hasher;
        return hasher(key) % capacity;
    }
    bool isPrime(int num){
        if(num <= 1){
            return false;
        }
        if(num <= 2){
            return true;
        }
        if(num % 2 == 0){
            return false;
        }
        for(int i = 3; i * i <= num;i+=2){
            if(num % i == 0){
                return false;
            }
        }
        return true;
    }
    public:
    HashMap(int maxsize = 13, double load = 0.75) : capacity(maxsize), size(0), loadFactor(load){
        map.resize(capacity);
    }
    void rehash();
    void insert(const K& key, const V& value);
    bool get(const K& key, list<V>& values);
    bool remove(const K& key);
    int getSize() const;
    bool isEmpty() const;
};
template <typename K, typename V>
void HashMap<K,V>::insert(const K& key, const V& value){
    //inserts the function in constant time
    int index = hashFunction(key);
    map[index].push_back(HashNode<K, V>(key, value));
    size++;
    //rehashes if neccesary
    if ((double)size / capacity > loadFactor) {
            rehash();
    }
}
template <typename K, typename V>
void HashMap<K,V>::rehash(){
    int newSize = capacity * 2;
    //finds next prime number
    while(!isPrime(newSize)){
        newSize++;
    }
    //creates a new map and pushes all eleents to it
    vector<list<HashNode<K, V>>> newMap(newSize);
    for(list<HashNode<K, V>> bucket : map){
        for(HashNode<K, V> node : bucket){
            hash<K> hasher;
            int newIndex = hasher(node.getKey()) % newSize;
            newMap[newIndex].push_back(node);
        }
    }
    //swapps the old map with the new map
    map.swap(newMap);
    //sets the new size
    capacity = newSize;
}
template <typename K, typename V>
bool HashMap<K,V>::get(const K& key, list<V>& values){
    //gets index and goes to that location on the map
    int index = hashFunction(key);
    list<HashNode<K, V>> chain = map[index];
    //goes through each node in the list and adds it to a list if key matches
    bool found = false;
    for(HashNode<K, V> node : chain){
        if(node.getKey() == key){
            values.push_back(node.getValue());
            found = true;
        }
    }
    return found;
}
 template <typename K, typename V>   
 bool HashMap<K,V>::remove(const K& key){
    //gets the index and goes to that location on the map
    int index = hashFunction(key);
    auto& chain = map[index];
    //iterates through the list to find the key to remove
    bool removed = false;
    for(auto it = chain.begin(); it != chain.end();){
        //key was found, erase the key and decrement the size
        if(it->getKey() == key){
            it = chain.erase(it); //returns the next valid iterator
            size--;
            removed = true;
        }
        else{
            it++;
        }
    }
    return removed;
 }
template <typename K, typename V>   
int HashMap<K,V>::getSize() const{
    return this->size;
}
template <typename K, typename V> 
bool HashMap<K,V>::isEmpty() const{
    return size == 0;
}




#endif