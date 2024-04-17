#include "../Base/matrix.h"
#include "../Base/vector.h"

// Power method implementation
template<typename T, int Rows, int Cols>
std::pair<T, C_Vector<T, Rows>> eigen(Matrix<T, Rows, Cols>& mat ,T tolerance = static_cast<T>(1e-6), int maxIterations = 100000){
    // Initialize Eigen vector
    C_Vector<T, Rows> x;
    for (int i = 0; i < Rows; ++i) {
        x[i] = 1; // Initial guess
    }

    // Perform power iteration
    for (int iter = 0; iter < maxIterations; ++iter) {
        // Multiply matrix with current Eigen vector
        C_Vector<T, Rows> x_new = mat * x;

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
        if (std::abs(maxElement - x[0]) < tolerance) {
            return std::make_pair(maxElement, x_new);
        }

        // Update Eigen vector
        x = x_new;
    }

    // Return the last computed Eigen vector
    return std::make_pair(0,x);
}