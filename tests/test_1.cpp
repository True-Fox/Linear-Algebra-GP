/*
* Test file for Instantiation, Operations, and determinant
*
*/

#include<stdlib.h>
#include<iostream>

#include "../linAlg/Base/vector.h"
#include "../linAlg/Base/matrix.h"

#include "../linAlg/Utils/Utils.h"

int main() {

    Matrix<int, 2, 3> mat1 {1, 2, 3, 4, 5, 6};
    Matrix<int, 3, 2> mat2;
    mat2[0][0] = 1;
    mat2[0][1] = 2;
    mat2[1][0] = 3;
    mat2[1][1] = 4;
    mat2[2][0] = 5;
    mat2[2][1] = 6;

    print(mat1);

    print(mat2);

    // std::cout<<"\nMat1*Mat2:\n";
    auto mat3 (mat1 * mat2);
    auto mat4 (mat3 * mat3);

    print(mat3);
    print(mat4);

    mat3.determinant();

    Vector<int, 4> vec {1,2,3,4};
    
    print(vec);

}