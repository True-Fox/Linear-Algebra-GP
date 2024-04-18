#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include<stdlib.h>
#include<cassert>
#include<concepts>
#include<type_traits>

/*Base Matrix Class
    - getCols() : Returns the number of columns
    - getRows() : Returns the number of rows
*/
template<typename T>
concept Numeric = requires {
    std::is_arithmetic_v<T>;
};

// Forward declarations : generic matrix
template<Numeric T, int Rows, int Cols>
class Matrix;

// Forward declarations : row vector
template<Numeric T, int Cols>
class Matrix<T, 1, Cols>;

// Forward declarations : column vector
template<Numeric T, int Rows>
class Matrix<T, Rows, 1>;

// Alias for row vector
template<Numeric T, int size>
using Vector = Matrix<T, 1, size>;

// Alias for column vector
template<Numeric T, int size>
using C_Vector = Matrix<T, size, 1>;

// Generic Matrix class with functions and operations
template<Numeric T, int Rows, int Cols>
class Matrix{
    public:
        // Default Constructor: Allocating memory
        Matrix(){
            data = new T*[Rows];
            for(int i = 0; i<Rows; i++){
                data[i] = new T[Cols]();
            }
        }

        // Initialize matrix with list
        // Example: Matrix<int, 2,2> M {1,2,3,4}
        Matrix(std::initializer_list<T> list){
            if(list.size() != Rows * Cols){
                throw std::invalid_argument("Initializer list size does not match matrix size");
            }
            data = new T*[Rows];
            for(int i = 0; i<Rows; i++){
                data[i] = new T[Cols]();
            }

            auto it = list.begin();
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    data[i][j] = (it != list.end()) ? *it++ : 0;
                }
            }
        }



        //Destructor
        ~Matrix(){
            for(int i = 0; i<Rows; i++){
                delete[] data[i];
            }
            delete[] data;
        }

        // Get the number of rows
        int getRows(){
            return Rows;
        }

        // Get the number of columns
        int getCols(){
            return Cols;
        }

        // Overloading the [] operator
        T* operator[](int row) {
            return data[row];
        }

        // Required for const-correctness 
        const T* operator[](int row) const {
            return data[row];
        }

        // Operator overloading

        // Addition of two matrices 
        template<int OtherRow, int OtherColumn>
        typename std::enable_if<(Cols == OtherColumn && Rows == OtherRow), Matrix<T, Rows, Cols>>::type
        operator+(const Matrix<T, OtherRow, OtherColumn>& other) const {
            Matrix<T, Rows, Cols> result;
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    result[i][j] = (*this)[i][j] + other[i][j];
                }
            }
            return result;
        }

        // Subtraction of two matrices 
        template<int OtherRow, int OtherColumn>
        typename std::enable_if<(Cols == OtherColumn && Rows == OtherRow), Matrix<T, Rows, Cols>>::type
        operator-(const Matrix<T, OtherRow, OtherColumn>& other) const {
            Matrix<T, Rows, Cols> result;
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    result[i][j] = (*this)[i][j] - other[i][j];
                }
            }
            return result;
        }        

        // Addition of two matrices 
        template<int OtherRow, int OtherColumn>
        typename std::enable_if<(Cols == OtherColumn && Rows == OtherRow), Matrix<T, Rows, Cols>>::type
        operator+(const Matrix<T, OtherRow, OtherColumn>&& other) const {
            Matrix<T, Rows, Cols> result;
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    result[i][j] = (*this)[i][j] + other[i][j];
                }
            }
            return result;
        }

        // Subtraction of two matrices 
        template<int OtherRow, int OtherColumn>
        typename std::enable_if<(Cols == OtherColumn && Rows == OtherRow), Matrix<T, Rows, Cols>>::type
        operator-(const Matrix<T, OtherRow, OtherColumn>&& other) const {
            Matrix<T, Rows, Cols> result;
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    result[i][j] = (*this)[i][j] - other[i][j];
                }
            }
            return result;
        }        

        // Multiplication of two matrices 
        template<int OtherRows ,int OtherCols>
        typename std::enable_if<Cols == OtherRows, Matrix<T, Rows, OtherCols>>::type
        operator*(const Matrix<T, OtherRows, OtherCols>& other) const {
            static_assert(Cols == OtherRows,"The given matrix dimensions are not compatible for multiplication");

            Matrix<T, Rows, OtherCols> result;

            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < OtherCols; ++j) {
                    for (int k = 0; k < Cols; ++k) {
                        result[i][j] += (*this)[i][k] * other[k][j];
                    }
                }
            }

            return result;
        }  

        // Multiplication of two matrices 
        template<int OtherRows, int OtherCols>
        typename std::enable_if<Cols == OtherRows, Matrix<T, Rows, OtherCols>>::type
        operator*(const Matrix<T, OtherRows, OtherCols>&& other) const {
            Matrix<T, Rows, OtherCols> result;

            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < OtherCols; ++j) {
                    for (int k = 0; k < Cols; ++k) {
                        result[i][j] += (*this)[i][k] * other[k][j];
                    }
                }
            }

            return result;
        }

        // Multiplication of a column vector and a matrix 
        template<int VectorRows>
        typename std::enable_if<Cols == VectorRows, C_Vector<T, Rows>>::type
        operator*(const C_Vector<T, VectorRows>& other) const {
            C_Vector<T, Rows> result;

            for (int i = 0; i < Rows; ++i) {
                T sum = 0;
                for (int j = 0; j < VectorRows; ++j) {
                    sum += (*this)[i][j] * other[j];
                }
                result[i] = sum;
            }

            return result;
        }


        //Overloading Assignment operator
        Matrix<T, Rows, Cols>& operator=(const Matrix<T, Rows, Cols>& other) {
            if (this != &other) {
                for (int i = 0; i < Rows; ++i) {
                    delete[] data[i];
                }
                delete data;

                int OtherRows = other.rows;
                int OtherCols = other.cols;

                data = new T*[Rows];
                for (int i = 0; i < OtherRows; ++i) {
                    data[i] = new T[Cols]();
                    for (int j = 0; j < OtherCols; ++j) {
                        data[i][j] = other.data[i][j];
                    }
                }
            }
            return *this;
        }

        // Determinant of the square matrices only
        template<int dim = Rows>
        typename std::enable_if<(dim == Cols), T>::type determinant() const {
            return determinantHelper(*this);
        }

    private:
        T **data;
        // Calculate determinant recursively
        template<int dim = Rows>
        typename std::enable_if<(dim == 1),T>::type determinantHelper(const Matrix& mat) const {
            return mat[0][0];
        }

        template<int dim = Rows>
        typename std::enable_if<(dim == 2), T>::type determinantHelper(const Matrix& mat) const {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }

        template<int dim = Rows>
        typename std::enable_if<(dim > 2), T>::type determinantHelper(const Matrix& mat) const {
            T det = 0;
            for (int j = 0; j < Cols; ++j) {
                T sign = (j % 2 == 0) ? 1 : -1;
                Matrix<T, dim - 1, dim - 1> minorMat;
                for (int k = 1; k < Rows; ++k) {
                    for (int l = 0, col = 0; l < Cols; ++l) {
                        if (l == j) continue;
                        minorMat[k - 1][col++] = mat[k][l];
                    }
                }
                det += sign * mat[0][j] * minorMat.determinant();
            }
            return det;
        }
};

#endif 
