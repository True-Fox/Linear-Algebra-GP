#include "../Matrix/matrix.h"
#include "../Matrix/vector.h"

template<typename T, int Rows, int Cols>
void print(Matrix<T, Rows, Cols>& mat) {
    for(int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Cols; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
}

template<typename T, int Rows>
void print(C_Vector<T, Rows>& vec){
    for(int i = 0; i < vec.getRows(); ++i) {
        std::cout << vec[i] << "\n";
    }
}

template<typename T, int Cols>
void print(Vector<T, Cols>& vec){
    for(int i = 0; i < vec.getCols(); ++i) {
        std::cout << vec[i] << " ";
    }
}