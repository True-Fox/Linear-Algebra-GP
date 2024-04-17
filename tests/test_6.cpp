#include<stdlib.h>
#include<iostream>
#include "../linAlg/Utils/eigen.h"

#include "../linAlg/Utils/Utils.h"
#include "../linAlg/Utils/LU_Decomposition.h"


int main(){
    constexpr int Rows = 3;
    constexpr int Cols = 3;

    // Create a matrix
    EigenMatrix<double, Rows, Cols> A = {10.0, 12.0, 1.0, 16.0, 23.0, 0.0, 23.0, 34.0, 2.0};

    // Find the dominant Eigen value and Eigen vector
    auto result = eigen(A);

    // Print the result
    std::cout << "Dominant Eigen vector:" << std::endl;
    print(*result);

    return 0;

}