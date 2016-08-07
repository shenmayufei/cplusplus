class Fruit{
    int no;          // 64bit: 4 byte value, 4 byte padding （32 bit: 4 byte value, no padding)
    double weight;   // 64bit: 8 byte, no padding (32 bit: 8 byte value, no padding)
    char key;        // 64bit: 1 byte value, 7 bytes padding (32 bit: 1 byte value, 3 byte padding)
public:
    void print() {   }
    virtual void process(){   }  // 64bit: vptr, 8 bytes (32 bit: 4 byte, no padding)
};
    
class Apple: public Fruit{  // inheritates 24 bytes from Fruit (excluding Fruit's vptr to virtual function table)
    int size;               // 4 bytes value, no padding 
    char type;              // 1 byte value, 3 bytes padding
    void save() {   }
    virtual void process(){   }   // 64bit: vptr 8 bytes (32 bit: 4 byte, no padding)
};
