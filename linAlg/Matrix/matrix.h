#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include<stdlib.h>

/*Base Matrix Class
    - getCols() : Returns the number of columns
    - getRows() : Returns the number of rows
*/
template<typename T, int Rows, int Cols>
class Matrix{
    public:
        //Default Constructor
        Matrix(){
            data = new T*[Rows];
            for(int i = 0; i<Rows; i++){
                data[i] = new T[Cols]();
            }
        }

        //Intialize matrix with list
        //Example: Matrix<int, 2,2> M {1,2,3,4}
        Matrix(std::initializer_list<T> list){
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

        //Intialize matrix with arguments
        //Example: Matrix<int, 2,2> M(1,2,3,4)
        // template<typename... Args>
        // Matrix(Args&&... args) {
        //     data = new T*[Rows];
        //     for (int i = 0; i < Rows; ++i) {
        //         data[i] = new T[Cols](); 
        //     }

        //     int index = 0;
        //     ([&]{
        //         int row = index/Cols;
        //         int cols = index%Cols;
        //         data[row][cols] = args;
        //         ++index;
        //     }(),...);
        // }
        

        //Destructor
        ~Matrix(){
            for(int i = 0; i<Rows; i++){
                delete[] data[i];
            }
            delete[] data;
        }

        //get number of rows
        int getRows(){
            return Rows;
        }

        //get number of columns
        int getCols(){
            return Cols;
        }

        //Overloading the [] operator
        T* operator[](int row) {
            return data[row];
        }

        //Required for const-correctness
        const T* operator[](int row) const {
            return data[row];
        }

        //addition of two matrices
        Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                result[i][j] = (*this)[i][j] + other[i][j];
            }
        }
        return result;
        }

        //matrix multiplication
        template<int OtherRows ,int OtherCols>
        Matrix<T, Rows, OtherCols> operator*(const Matrix<T, OtherRows, OtherCols>& other) const {
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

        //determinant of the square matrices only
        template<int dim = Rows>
        typename std::enable_if<(dim == Cols), T>::type determinant() const {
            return determinantHelper(*this);
        }

    private:
        T **data;
        //calculate determinant recursively
        template<int dim = Rows>
        typename std::enable_if<(dim == 1), T>::type determinantHelper(const Matrix& mat) const {
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