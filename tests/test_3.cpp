#include<stdlib.h>
#include<iostream>

#include "../linAlg/Base/matrix.h"
#include "../linAlg/Base/vector.h"

#include "../linAlg/Utils/Utils.h"

int main(){
    std::cout<<"Transpose (Matrix):\n";
    Matrix<int, 2, 2> vec {1,2,3,4};
    print(vec);
    auto res = transpose(vec);
    print(res);

    std::cout<<"Transpose (Vector):\n";
    Vector<int, 4> vec1 {1,2,3,4};
    print(vec1);
    auto res1 = transpose(vec1);
    print(res1);
    Matrix<int, 4,1> vec2 {1,2,3,4};

    auto res3 = vec1 * vec2;

    std::cout<<"Trial-1\n";
    auto res2 = transpose(vec1) * vec1 ;
    print(res2);

}