#include<stdlib.h>
#include<iostream>

#include "linAlg/Matrix/vector.h"

int main() {

    Vector<int, 4> rowVec;

    rowVec[0] = 1;
    rowVec[1] = 2;
    rowVec[2] = 3;
    rowVec[3] = 4;

    std::cout<<"Row Vector: \n";
    for (int j = 0; j < rowVec.getCols(); j++) {
        std::cout << rowVec[j] << " ";
    }
    std::cout << std::endl;

    C_Vector<int, 3> colVec;

    colVec[0] = 1;
    colVec[1] = 2;
    colVec[2] = 3;

    std::cout<<"Column Vector: \n";
    for (int i = 0; i < colVec.getRows(); i++) {
        std::cout << colVec[i] << std::endl;
    }
}