#ifndef EIGEN_H
#define EIGEN_H

#include "../Base/matrix.h"
#include "../Base/vector.h"

// Forward declaration of the eigen function template
template<Numeric T, int Rows, int Cols>
class EigenMatrix;

template<typename T, int Rows, int Cols>
C_Vector<T, Rows>* eigen(const EigenMatrix<T, Rows, Cols>& matrix, T tolerance = static_cast<T>(1e-6), int maxIterations = 10000000);


template<Numeric T, int Rows, int Cols>
class EigenMatrix: public Matrix<T, Rows, Cols> {
public:
    using Matrix<T, Rows, Cols>::Matrix;

    template<Numeric U, int R, int C>
    friend C_Vector<U, R>* eigen(const EigenMatrix<U, R, C>& matrix, U tolerance, int maxIterations);
};

template<typename T, int Rows, int Cols>
C_Vector<T, Rows>* eigen(const EigenMatrix<T, Rows, Cols>& matrix, T tolerance , int maxIterations ){
    C_Vector<double, Rows>* x = new C_Vector<double, Rows>();
        
        for(int i=0; i<Rows; ++i){
            (*x)[i] = 1; // Initial guess
        }

        // Perform power iteration
        for (int iter = 0; iter < maxIterations; ++iter) {
            // Multiply matrix with current Eigen vector
            C_Vector<T, Rows> x_new = matrix * (*x);

            // Find the maximum element in the new vector
            T maxElement = x_new[0];
            for (int i = 1; i < Rows; ++i) {
                if (std::abs(x_new[i]) > std::abs(maxElement)) {
                    maxElement = x_new[i];
                }
            }

            // Normalize the new vector
            for (int i = 0; i < Rows; ++i) {
                x_new[i] /= maxElement;
            }

            // Check for convergence
            if (std::abs(maxElement - (*x)[0]) < tolerance) {
                return x;
            }

            // Update Eigen vector
            *x = x_new;
        }

        return x;
    };

#endif