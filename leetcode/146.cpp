/*
    Design and implement a data structure for Least Recently Used (LRU) cache. 
    It should support the following operations: get and put.

    1. get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
    2. put(key, value) - put or insert the value if the key is not already present. 
        When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
*/
#include<iostream>
#include<list>
#include<unordered_map>

class Pair {
    public:
        int key;
        int val;
        Pair(int k, int v):key(k),val(v){};
};

class LRUCache{
private:
    std::unordered_map<int, std::list<Pair>::iterator> cache;
    int cap;
    std::list<Pair> datalist;
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        std::unordered_map<int, std::list<Pair>::iterator >::iterator it = cache.find(key);
        if (it != cache.end()) {
            Pair record = *(it->second); // memory allocation(need to optimize)
            datalist.erase(it->second);
            datalist.push_back(record);
            cache[key] = --datalist.end();
            return record.val;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        std::unordered_map<int, std::list<Pair>::iterator >::iterator it = cache.find(key);
        if (it != cache.end()){
            datalist.erase(it->second);
        }
        if (datalist.size() == cap) {
            Pair unused_rec = datalist.front();
            datalist.pop_front();
            cache.erase(unused_rec.key);
        }
        Pair record(key, value);
        datalist.push_back(record);
        cache[key] = --datalist.end();

    }
};

int main() {
    LRUCache cache(2);
    std::cout << "get(2): "<< cache.get(2) << std::endl;
    std::cout << "put(2,6)" << std::endl; 
    cache.put(2,6);
    std::cout << "get(1): "<< cache.get(1) << std::endl; 
    std::cout << "put(1,5)" << std::endl; 
    cache.put(1, 5);
    std::cout << "put(1,2)" << std::endl; 
    cache.put(1, 2);
    std::cout << "get(1): "<< cache.get(1) << std::endl; 
    std::cout << "get(2): "<< cache.get(2) << std::endl; 
    
}
