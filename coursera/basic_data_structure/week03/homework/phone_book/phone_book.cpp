#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

using std::string;
using std::vector;
using std::cin;

int nextPrime(int limit);

struct Query {
    string type, name;
    int number;
};

struct Node {
    string name;
    int number;
    Node* next;
public:
    Node(string name, int number): name(name), number(number), next(nullptr) {}
};

class HashTable {
private:
    vector<Node*> m_vdata;
    int m_np, m_na, m_nb, m_nm;

    size_t hash(int number) {
        long long res = m_na;
        res = (res * number + m_nb) % m_np;
        res = res % m_nm;
        // std::cout << "m_na = " << m_na << ", m_nb = " << m_nb << ", m_np = " << m_np << ", number = " << number << ", hash:" << res << ", size_t = " << (size_t)res << std::endl;
        return (size_t)res;
    }
public:
    HashTable(int p, int a, int b, int m): m_na(a), m_nb(b), m_nm(m) {
        if (m <= 0) m_nm = 100000;
        m_vdata = vector<Node*>(m_nm, nullptr);

        m_np = nextPrime(p);
    }

    HashTable(int m = 100000): m_nm(m) {
        if (m_nm <= 0) m_nm = 100000;

        m_np = nextPrime(100000000);
        srand (time(NULL));
        m_na = rand() % (m_np-1) + 1;
        m_nb = rand() % m_np;
        m_vdata = vector<Node*>(m_nm, nullptr);
    }

    void add(string name, int number) {
        int hashCode = hash(number);
        auto firstPtr = m_vdata[hashCode];

        while(firstPtr != nullptr) {
            if (firstPtr->number == number) {
                firstPtr->name = name;  // update name
                return;
            }
            firstPtr = firstPtr->next;
        }

        Node* newNode = new Node(name, number);
        newNode->next = m_vdata[hashCode];
        m_vdata[hashCode] = newNode;
    }

    string find(int number) {
        int hashCode = hash(number);
        Node* firstPtr = m_vdata[hashCode];

        while(firstPtr != nullptr) {
            if (firstPtr->number == number) {
                return firstPtr->name;
            }
            firstPtr = firstPtr->next;
        }
        return "not found";
    }

    void del(int number) {
        int hashCode = hash(number);
        Node* firstPtr = m_vdata[hashCode];
        // number not found
        if (firstPtr == nullptr) return;
        // number in the list head
        if (firstPtr->number == number) {
            Node* tmpNode = firstPtr->next;
            delete firstPtr;
            m_vdata[hashCode] = tmpNode;
            return;
        } 
        // number in later items
        while(firstPtr->next != nullptr) {
            Node* tmpNode = firstPtr->next;
            if (tmpNode->number == number) {
                firstPtr->next = tmpNode->next;
                delete tmpNode;
                return;
            }
            firstPtr = firstPtr->next;
        }
    }
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

// nextPrime is used to generate the smallest prime number bigger than limit.
int nextPrime(int limit) {
    if (limit % 2 == 0) limit++;

    while(true) {
        bool isPrime = true;
        for(int i = 3; i * 2 < limit; i+=2 ) {
            if ( limit % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime == true) return limit;
        limit+=2;
    }
}

int testNextPrime() {
    std::cout << "nextPrime(1000)      = " << nextPrime(1000) << std::endl;
    std::cout << "nextPrime(10000)     = " << nextPrime(10000) << std::endl;
    std::cout << "nextPrime(1000000)   = " << nextPrime(1000000) << std::endl;
    std::cout << "nextPrime(100000000) = " << nextPrime(100000000) << std::endl;
    return 0;
}

// hash table algorithm
vector<string> process_queries_fast(const vector<Query>& queries) {
    vector<string> result;
    HashTable ht(queries.size());

    for (size_t i = 0; i < queries.size(); i++) {
        // std::cout << "shall " << queries[i].type << " name " << queries[i].name << " number " << queries[i].number << std::endl; 
        if (queries[i].type == "add") {
            ht.add(queries[i].name, queries[i].number);
        } else if (queries[i].type == "del") {
            ht.del(queries[i].number);
        } else {
            result.push_back(ht.find(queries[i].number));
        }
    }
    return result;
}

// naive algorithm
vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
        } else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        } else {
            string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);
        }
    return result;
}

int test(const vector<Query>& queries) {
    while(true) {
        std::cout << "-----------------" << std::endl;
        auto normal_results = process_queries(queries);
        auto fast_results = process_queries_fast(queries);
        for (int i = 0; i < normal_results.size(); i++) {
            if (normal_results[i] != fast_results[i]) {
                std::cout << "normal result: " << std::endl;
                write_responses(normal_results);
                std::cout << "fast   result: " << std::endl;
                write_responses(fast_results);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    // testNextPrime();
    auto queries = read_queries();
    // if (test(queries) != 0) {
    //     std::cout << "test failed" << std::endl;
    // }

    // raw algorithm
    // write_responses(process_queries(queries));

    // fast hash algorithm  
    write_responses(process_queries_fast(queries));

    return 0;
}
