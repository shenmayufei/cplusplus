#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>     /* srand, rand */

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

struct Node {
    string name;
    Node* next;
public:
    Node(string s) : name(s), next(nullptr) {}
};

class QueryProcessor {
private:
    int bucket_count;
    // store all strings in one vector
    vector<Node*> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        elems = vector<Node*>(bucket_count, nullptr);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    const Node* check(int ind) const {
        if (ind >= bucket_count) {
            return nullptr;
        }
        return elems[ind];
    }

    void processQuery(const Query& query) {
        if (query.type == "add") {
            int hashCode = hash_func(query.s);
            Node* locPtr = elems[hashCode];

            while(locPtr != nullptr) {
                if (locPtr->name == query.s) {
                    return; // already exists
                }
                locPtr = locPtr->next;
            }

            // add the new data
            Node* newNode = new Node(query.s);
            newNode->next = elems[hashCode];
            elems[hashCode] = newNode;
        } else if (query.type == "find") {
            int hashCode = hash_func(query.s);
            Node* locPtr = elems[hashCode];

            while(locPtr != nullptr) {
                if (locPtr->name == query.s) {
                    break;
                }
                locPtr = locPtr->next;
            }
            writeSearchResult(locPtr != nullptr);
        } else if (query.type == "del") {
            int hashCode = hash_func(query.s);
            Node* locPtr = elems[hashCode];
            // not exist
            if (locPtr == nullptr) return;
            // first element
            if (locPtr->name == query.s) {
                elems[hashCode] = locPtr->next;
                delete locPtr;
                return;
            } 
            // later element
            while(locPtr->next != nullptr) {
                if (locPtr->next->name == query.s) {
                    break;
                }
                locPtr = locPtr->next;
            }
            if (locPtr->next == nullptr) return;
            Node* tmpNode = locPtr->next;
            locPtr->next = tmpNode->next;
            delete tmpNode;
        } else if (query.type == "check" ) {
            const Node* curPtr = check(query.ind);
            while(curPtr != nullptr) {
                std::cout << curPtr->name << " ";
                curPtr = curPtr->next;
            }
            std::cout << std::endl;
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int testInfinite() {
    string types[] = {"add", "find", "check", "delete"};
    while(true) {
        size_t bucketCount = rand() % 100 + 3;
        QueryProcessor proc(bucketCount);
        size_t queryCount = rand() % 1000 + 10;
        for(size_t i = 0 ; i < queryCount; i++ ) {
            Query query;
            int randNum = rand() % 6;
            if (randNum > 3) randNum = 3;  // 增加 delete 出现的概率
            query.type = types[randNum];
            int count = 0;
            if (query.type == "check") {
                query.ind = rand() % bucketCount;
            } else if (query.type == "add") {
                size_t sLen = rand() % 10 + 1;
                while(sLen-->0) query.s.push_back(rand()%26 + 'a');
                count++;
            } else if (query.type == "del" ) {
                if(rand()%2 == 0) {
                    size_t sLen = rand() % 10 + 1;
                    while(sLen-->0) query.s.push_back(rand()%26 + 'a');
                } else {
                    // find out one already exists to delete
                    while(count > 0) { // count ensures there must be one
                        size_t ind = rand() % bucketCount;
                        const Node* ptr = proc.check(ind);
                        if (ptr == nullptr) continue;
                        query.s = ptr->name;
                        count--;
                        break;
                    }
                } 
            } else if (query.type == "find" ) {
                if(rand()%2 == 0) {
                    size_t sLen = rand() % 10 + 1;
                    while(sLen-->0) query.s.push_back(rand()%26 + 'a');
                } else {
                    // find out one already exists to delete
                    while(count > 0) { // count ensures there must be one
                        size_t ind = rand() % bucketCount;
                        const Node* ptr = proc.check(ind);
                        if (ptr == nullptr) continue;
                        query.s = ptr->name;
                        break;
                    }
                } 
            }
            proc.processQuery(query);
        }    
    }

}

int main() {
    std::ios_base::sync_with_stdio(false);
    // if(testInfinite() == 0) {
    //     std::cout << "test passed" << std::endl;
    // } else {
    //     std::cout << "test failed" << std::endl;
    // }
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
