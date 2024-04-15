#include<stdlib.h>
#include<iostream>

#include "../linAlg/Base/matrix.h"
#include "../linAlg/Base/vector.h"

#include "../linAlg/Utils/Utils.h"
#include "../linAlg/Utils/LU_Decomposition.h"

int main(){

    Matrix<int ,3, 3> res {1,1,1,4,3,-1,3,5,3};
    print(res);

    auto lu = LU_Decompose(res);

    print("Lower Matrix: ");
    print(lu.L);

    print("Upper Matrix: ");
    print(lu.U);
    
    print("Original matrix");
    auto OG = lu.L * lu.U;
    print(OG);
}