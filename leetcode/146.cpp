/*
    Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

    get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
    set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
*/
#include<iostream>
#include<map>
#include<list>

class Pair {
    public:
        int key;
        int val;
        Pair(int k, int v):key(k),val(v){};
};

class LRUCache{
private:
    
    int cap;
    
public:
    std::list<Pair> datalist;
    std::map<int, std::list<Pair>::iterator> cache;
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        std::map<int, std::list<Pair>::iterator >::iterator it = cache.find(key);
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
    
    void set(int key, int value) {
        std::map<int, std::list<Pair>::iterator >::iterator it = cache.find(key);
        if (it != cache.end()){
            std::cout << "＊＊＊ set(" << key << "," << value << "): " << it->first << ": "<< it->second->key << "--" << it->second->val << std::endl;
            datalist.erase(it->second);
        }
        if (datalist.size() == cap) {
            std::cout << "llllll\n";
            Pair unused_rec = datalist.front();
            datalist.pop_front();
            cache.erase(unused_rec.key);
        }
        Pair record(key, value);
        datalist.push_back(record);
        cache[key] = --datalist.end();

    }
};

void printList(LRUCache &cache) {
    std::list<Pair> &list = cache.datalist;
    std::cout << "--------Cache keys: ";
    for (std::map<int, std::list<Pair>::iterator>::iterator it = cache.cache.begin(); it != cache.cache.end(); it++) {
        std::cout << it->first << ", ";
    }
    std::cout << "\nList: " << std::endl;
    for (std::list<Pair>::iterator it = list.begin(); it != list.end(); it++) {
        std::cout << "key: " << it->key << ", val:" << it->val << std::endl;;
    }
    std::cout << "List end----------" << std::endl;
}
int main() {
    LRUCache cache(2);
    std::cout << "get(2): "<< cache.get(2) << std::endl;
    std::cout << "set(2,6)" << std::endl; 
    cache.set(2,6);
    printList(cache);
    std::cout << "get(1): "<< cache.get(1) << std::endl; 
    printList(cache);
    std::cout << "set(1,5)" << std::endl; 
    cache.set(1, 5);
    printList(cache);
    std::cout << "set(1,2)" << std::endl; 
    cache.set(1, 2);
    printList(cache);
    std::cout << "get(1): "<< cache.get(1) << std::endl; 
    printList(cache);
    std::cout << "get(2): "<< cache.get(2) << std::endl; 
    printList(cache);
    
}
