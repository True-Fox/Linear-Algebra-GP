#include<stdlib.h>
#include<iostream>

#include "../linAlg/Base/matrix.h"
#include "../linAlg/Base/vector.h"

#include "../linAlg/Utils/Utils.h"
#include "../linAlg/Utils/LU_Decomposition.h"
#include "../linAlg/Utils/eigen.h"

int main(){

    Matrix<int ,3, 3> res {2,1,1,1,3,2,1,2,3};

    auto eigenVector = eigen(res);

    print(eigenVector);

}