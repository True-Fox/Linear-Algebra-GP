#include<stdlib.h>
#include<iostream>

#include "../linAlg/Base/matrix.h"
#include "../linAlg/Base/vector.h"

#include "../linAlg/Utils/Utils.h"

int main(){
    C_Vector<double, 4> vec = {1,2,3,4};
    auto mag = vec.magnitude();
    std::cout<<vec.magnitude() << "\n";

    print("Norm of vector: ");
    apply(vec, [mag](int x){
        return (double)x/mag;
    });    

    print(vec);
}