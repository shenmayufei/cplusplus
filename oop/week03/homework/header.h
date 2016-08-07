class Fruit{
    int no;          // 4 byte
    double weight;   // 8 byte
    char key;        // 1 byte, but use 4 byte storage (because of expansion)
public:
    void print() {   }
    virtual void process(){   }  // vptr, 8 bytes
};
    
class Apple: public Fruit{  // inheritates 24 bytes from Fruit
    int size;               // 4 bytes
    char type;              // 1 byte, but use 4 byte storage
public:
    void save() {   }
    virtual void process(){   }   // vptr 8 bytes
};