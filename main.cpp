#include<stdlib.h>
#include<iostream>

#include "linAlg/Matrix/vector.h"

int main() {

    Matrix<int, 2, 3> mat1 {1, 2, 3, 4, 5, 6};
    Matrix<int, 2, 2> mat2 {1, 2, 3, 4};

    std::cout<<"Matrix mat1: \n";
    for(int i=0; i<mat1.getRows(); i++){
        for(int j=0; j<mat1.getCols();j++){
            std::cout<<mat1[i][j]<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"\nMatrix mat2: \n";
    for(int i=0; i<mat2.getRows(); i++){
        for(int j=0; j<mat2.getCols();j++){
            std::cout<<mat2[i][j]<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"\nMat1*Mat2:\n";
    Matrix<int, 2, 2> mat3 (mat1 * mat2);
    Matrix<int, 2, 2> mat3 = mat1 * mat2;
    for(int i=0; i<mat3.getRows(); i++){
        for(int j=0; j<mat3.getCols();j++){
            std::cout<<mat3[i][j]<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"\nDet(Mat3): "<<mat3.determinant()<<"\n";

}