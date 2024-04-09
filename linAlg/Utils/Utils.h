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
    std::cout<<"\n";
}

template<typename T>
void print(T& out){
    std::cout<<out<<"\n";
}

template<typename T, int Rows, int Cols, typename Func>
void apply(Matrix<T, Rows, Cols>& Mat, Func&& func){
    for(int i = 0; i < Rows; ++i){
        for(int j = 0; j < Cols; ++j){
            Mat[i][j] = func(Mat[i][j]);
        }
    }
}

template<typename T, int Cols, typename Func>
void apply(Vector<T, Cols>& Vec, Func&& func){
    for(int i = 0; i < Cols; ++i){
        Vec[i] = func(Vec[i]);
    }
}

template<typename T, int Rows, typename Func>
void apply(C_Vector<T, Rows>& Vec, Func&& func){
    for(int i = 0; i < Rows; ++i){
        Vec[i] = func(Vec[i]);
    }
}

template<typename T, int Rows, int Cols>
Matrix<T, Cols, Rows> transpose(Matrix<T, Cols, Rows>& mat){
    Matrix<T, Cols, Rows> result;
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Cols; ++j) {
            result[j][i] = mat[i][j];
        }
    }
    return result;    
}

template<typename T, int Cols>
C_Vector<T, Cols> transpose(Vector<T, Cols>& mat){
    C_Vector<T, Cols> result;
    for (int j = 0; j < Cols; ++j) {
        result[j] = mat[j];
    }
    return result;    
}