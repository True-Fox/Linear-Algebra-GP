#include<stdlib.h>
#include<iostream>

#include "linAlg/Matrix/matrix.h"

int main(){
    Matrix mat(3,4);
    std::cout << "No of cols: "<<mat.getCols()<<"\n";
    std::cout << "No of rows: "<<mat.getRows()<<"\n";
    
    mat[0][0] = 1.0;
    mat[0][1] = 2.0;
    mat[1][2] = 3.0;
    mat[2][3] = 4.0;

    for(int i=0; i<mat.getRows() ;i++){
        for(int j=0;j<mat.getCols(); j++){
            std::cout<<mat[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}