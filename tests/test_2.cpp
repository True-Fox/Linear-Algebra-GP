#include<stdlib.h>
#include<iostream>

#include "../linAlg/Matrix/matrix.h"
#include "../linAlg/Matrix/vector.h"

#include "../linAlg/Utils/Utils.h"

int main() {
//     Matrix X Matrix = Matrix   DONE -> Overloading done in Matrix class
//     Matrix X Column Vector = Column Vector DONE -> Overloading done in Matrix class
//     Row Vector X Matrix = Row Vector DONE -> Overloading done in Row class
//     Row Vector X Column Vector = Single Element  -> Overloading done in Row Class
//     Column Vector X Row Vector = Matrix -> Overloading done in Column Classes

    Matrix<int, 5, 2> mat {1,2,3,4,5,6,7,8,9,10};
    C_Vector<int, 2> c_vec {1,2};

    std::cout<<"Matrix x Column Vector\n";
    auto res = mat * c_vec;
    print(res);

    std::cout<<"Row Vector X Matrix\n";
    Vector<int, 2> vec {1,2};
    Matrix<int, 2, 2> mat1 {1,2,3,4};

    auto res1 = vec * mat1;
    print(res1);

    std::cout<<"Row Vector X Column Vector\n";
    Vector<int, 2> vec2 {2,4};
    C_Vector<int,2> C_vec2 {1,2};

    auto res2 = vec2 * C_vec2;
    print(res2);

    std::cout<<"Column Vector X Row Vector\n";
    C_Vector<int, 5> c_vec3 {1,2,3,4,5};
    Vector<int, 5> vec3 {1,2,3,4,5};

    auto res3 = c_vec3 * vec3;

    print(res3);

    std::cout<<"\nBefore Apply\n";
    print(res3);

    apply(res3, [](int x){
           return x*x; 
    });

    std::cout<<"\nAfter Apply\n";
    print(res3);

    Vector<int, 5> vec5 {1,2,3,4,5};
    Vector<int, 5> vec6 {3,4,5,6,7};
    C_Vector<int, 5> vec8 {1,2,3,4,5};
    C_Vector<int, 5> vec9 {3,4,5,6,7};
    auto vec7 = vec5+vec6;
    auto vec10 = vec8 + vec9;

    std::cout<<"Addition of two vectors: \n";
    print(vec7);
    print(vec10);

    std::cout<<"\nCombination of addition and multiplication\n";
    auto res11 = (vec10 * vec7) + (res3 * res3);
    print(res11);
}