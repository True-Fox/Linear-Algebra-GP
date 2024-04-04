/*
* Test file for Instantiation, Operations, and determinant
*
*/

#include<stdlib.h>
#include<iostream>

#include "../linAlg/Matrix/vector.h"
#include "../linAlg/Matrix/matrix.h"

int main() {

    Matrix<int, 2, 3> mat1 {1, 2, 3, 4, 5, 6};
    Matrix<int, 3, 2> mat2;
    mat2[0][0] = 1;
    mat2[0][1] = 2;
    mat2[1][0] = 3;
    mat2[1][1] = 4;
    mat2[2][0] = 5;
    mat2[2][1] = 6;


    // std::cout<<"Matrix mat1: \n";
    // for(int i=0; i<mat1.getRows(); i++){
    //     for(int j=0; j<mat1.getCols();j++){
    //         std::cout<<mat1[i][j]<<" ";
    //     }
    //     std::cout<<"\n";
    // }

    // std::cout<<"\nMatrix mat2: \n";
    // for(int i=0; i<mat2.getRows(); i++){
    //     for(int j=0; j<mat2.getCols();j++){
    //         std::cout<<mat2[i][j]<<" ";
    //     }
    //     std::cout<<"\n";
    // }

    // std::cout<<"\nMat1*Mat2:\n";
    Matrix<int, 2, 2> mat3 (mat1 * mat2);
    Matrix<int, 2, 2> mat4 (mat3 * mat3);
    // for(int i=0; i<mat3.getRows(); i++){
    //     for(int j=0; j<mat3.getCols();j++){
    //         std::cout<<mat3[i][j]<<" ";
    //     }
    //     std::cout<<"\n";
    // }

    mat3.determinant();

}