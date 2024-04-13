#include<stdlib.h>
#include<iostream>

#include "../linAlg/Matrix/matrix.h"
#include "../linAlg/Matrix/vector.h"

#include "../linAlg/Utils/Utils.h"

int main(){
    Matrix<double, 2, 2> mat {1.2, 2.2, 3.3, 4.4};
    Matrix<int, 2, 2> mat1 {4, 3, 2, 1};
    auto res = transpose(mat1) * mat1;
    print(res);

    Matrix<char, 2, 2> cha {'a','b','c','d'};
    auto cha2 = cha+cha;
    print(cha2);
}