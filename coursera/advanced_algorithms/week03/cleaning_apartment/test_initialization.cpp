#include <iostream>

int main() {
    int m[3][3] = {{1}};
    for(int i = 0; i < 3; i++) 
        for(int j = 0; j < 3; j++) 
            std::cout << "val=" << m[i][j] << std::endl;
}