#include<stdlib.h>
#include<iostream>

#include "../linAlg/Matrix/matrix.h"
#include "../linAlg/Matrix/vector.h"

#include "../linAlg/Utils/Utils.h"

int main() {

    Matrix<int, 2, 2> mat1 {1, 2, 3, 4};
    Matrix<int, 2, 2> Vec1 {4, 3,3,4};

    Matrix<int, 2, 2> res = mat1 * Vec1;

    std::cout<<"\nBefore Apply\n";
    print(res);

    apply(res, [](int x){
           return x*x; 
    });

    std::cout<<"\nAfter Apply\n";
    print(res);

}