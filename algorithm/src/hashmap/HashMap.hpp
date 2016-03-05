/**********************************************************
   author:     zhaosl
   created:    20160303
   purpose:    HashMap template, 散列表 (从Java拷贝过来的函数声明)
**********************************************************/

/*
Java HashMap Constructors
    HashMap()
    Constructs an empty HashMap with the default initial capacity (16) and the default load factor (0.75).
    HashMap(int initialCapacity)
    Constructs an empty HashMap with the specified initial capacity and the default load factor (0.75).
    HashMap(int initialCapacity, float loadFactor)
    
    HashMap(Map<? extends K,? extends V> m)
    Constructs a new HashMap with the same mappings as the specified Map.

 */
#ifndef HASHMAP_TEMPLATE_H
#define HASHMAP_TEMPLATE_H
namespace zhaosl
{
    template <typename V>
    struct HashNode
    {
    public:
        V     data;
        HashNode<V> * next;
        HashNode(const V value)
        :data(value)
        {
            next = NULL;
        }
    };

    template <typename K, typename V>
    class HashMap
    {
    private:
        static const int INITIAL_CAPACITY = 16;
        static constexpr double LOAD_FACTOR = 0.75;
        int m_nCapacity;             //初始容量
        double m_dMaxLoadFactor;            //负载因子的阈值
        double m_dLoadFactor;               //实际负载因子
        int m_nSize;                        // 实际键值对的数量
        HashNode<V>**  m_pMap;              //存储数据的地方 
    public:
        // Constructs an empty HashMap with the default initial capacity (16) and the default load factor (0.75).
        HashMap();
        // Constructs an empty HashMap with the specified initial capacity and the default load factor (0.75).
        HashMap(int initialCapacity);
        // Constructs an empty HashMap with the specified initial capacity and load factor.
        HashMap(int initialCapacity, double loadFactor);
        // Destructs current HashMap object
        ~HashMap();

        // Removes all of the mappings from this map.
        void clear();
        // Returns true if this map contains no key-value mappings.
        bool isEmpty();
        // Returns true if this map contains a mapping for the specified key.
        bool containsKey(K key);
        // Returns true if this map maps one or more keys to the specified value.
        bool containsValue(V value);
        
        // Returns a Set view of the mappings contained in this map.
        // Set<Map.Entry<K,V>> entrySet();
        
        // Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
        V   get(K key);

        // Returns a Set view of the keys contained in this map.
        // Set<K>  keySet()
        // Associates the specified value with the specified key in this map.
        V   put(K key, V value);
        // Copies all of the mappings from the specified map to this map.
        // void    putAll(Map<? extends K,? extends V> m)

        // Removes the mapping for the specified key from this map if present.    
        V   remove(K key);
        // size Returns the number of key-value mappings in this map.
        int size();

        // Returns the hashed value of key as the index in the map.
        int hash(K key);
    
        // Returns a Collection view of the values contained in this map.
        // Collection<V>   values()
        
    };

    template <typename K, typename V>
    HashMap<K, V>::HashMap():m_nCapacity(INITIAL_CAPACITY),m_dMaxLoadFactor(LOAD_FACTOR),m_nSize(0) {
        m_pMap = new HashNode<V>*[INITIAL_CAPACITY];
    }

    template <typename K, typename V>
    HashMap<K, V>::HashMap(int initialCapacity):m_nCapacity(initialCapacity),m_dMaxLoadFactor(LOAD_FACTOR), m_nSize(0) {
        if (m_nCapacity < INITIAL_CAPACITY) {
            m_nCapacity = INITIAL_CAPACITY;
        }
        m_pMap = new HashNode<V> *[m_nCapacity];
    }
    
    template <typename K, typename V>
    HashMap<K, V>::HashMap(int initialCapacity, double loadFactor):m_nCapacity(initialCapacity),m_dMaxLoadFactor(loadFactor), m_nSize(0) {
        if (m_nCapacity < INITIAL_CAPACITY) {
            m_nCapacity = INITIAL_CAPACITY;
        }
        m_pMap = new HashNode<V>*[m_nCapacity];
    }

    template <typename K, typename V>
    HashMap<K, V>::~HashMap() {
        delete[] m_pMap;
    }

    template <typename K, typename V>
    void HashMap<K, V>::clear() {
        for (int i = 0; i < m_nCapacity; i++) {
            m_pMap[i] = NULL;
        }
    }

    template <typename K, typename V>
    bool HashMap<K, V>::isEmpty() {
        return m_nSize == 0;
    }

    template <typename K, typename V>
    int HashMap<K, V>::size() {
        return m_nSize;
    }

    // @TODO: need to determine a way to hash values of all types
    // without reflection, it can be difficult
    template <typename K, typename V>
    int HashMap<K, V>::hash(K key) {
        unsigned int HashVal = 0;
        while(*key != '\0')
            HashVal += (HashVal << 5) + *key++;
        return HashVal % m_nCapacity;
    }
};

#endif
