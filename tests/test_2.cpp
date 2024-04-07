#include<stdlib.h>
#include<iostream>

#include "../linAlg/Matrix/matrix.h"
#include "../linAlg/Matrix/vector.h"

#include "../linAlg/Utils/PrintMatrix.h"

int main() {

    Matrix<int, 2, 2> mat1 {1, 2, 3, 4};
    Matrix<int, 2, 2> Vec1 {4, 3,3,4};

    Matrix<int, 2, 2> res = mat1 * Vec1;

    print(res);

}