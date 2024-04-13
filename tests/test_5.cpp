#include<stdlib.h>
#include<iostream>

#include "../linAlg/Base/matrix.h"
#include "../linAlg/Base/vector.h"

#include "../linAlg/Decomposition/LU_Decomposition.h"

int main(){

    Matrix<int, 3, 3> mat {2, -1, -2, -4, 6, 3, -4, -2, 8};
    
    print(mat);
    auto lu = LU_Decompose(mat);
    std::cout<<"\nLower Triangular Matrix\n";
    print(lu.L);
    std::cout<<"\nUpper Triangle Matrix\n";
    print(lu.U);
    std::cout<<"\nProduct of L and U\n";
    auto mat1 = lu.L * lu.U;
    print(mat1);
}