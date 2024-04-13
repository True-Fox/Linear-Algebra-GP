#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include<stdlib.h>
#include<cassert>

/*Base Matrix Class
    - getCols() : Returns the number of columns
    - getRows() : Returns the number of rows
*/
template<typename T>
concept Numeric = requires {
    std::is_arithmetic_v<T>;
};


template<Numeric Numeric_Type, int Rows, int Cols>
class Matrix;

template<Numeric Numeric_Type, int Cols>
class Matrix<Numeric_Type, 1, Cols>;

template<Numeric Numeric_Type, int Rows>
class Matrix<Numeric_Type, Rows, 1>;

template<Numeric Numeric_Type, int size>
using Vector = Matrix<Numeric_Type, 1, size>;

template<Numeric Numeric_Type, int size>
using C_Vector = Matrix<Numeric_Type, size, 1>;

template<Numeric Numeric_Type, int Rows, int Cols>
class Matrix{
    public:
        //Default Constructor
        Matrix(){
            data = new Numeric_Type*[Rows];
            for(int i = 0; i<Rows; i++){
                data[i] = new Numeric_Type[Cols]();
            }
        }

        //Intialize matrix with list
        //Example: Matrix<int, 2,2> M {1,2,3,4}
        Matrix(std::initializer_list<Numeric_Type> list){
            // assert(list.size() == Rows * Cols && "Initializer list size does not match matrix size");
            if(list.size() != Rows * Cols){
                throw std::invalid_argument("Initializer list size does not match matrix size");
            }
            data = new Numeric_Type*[Rows];
            for(int i = 0; i<Rows; i++){
                data[i] = new Numeric_Type[Cols]();
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

        //get number of rows
        int getRows(){
            return Rows;
        }

        //get number of columns
        int getCols(){
            return Cols;
        }

        //Overloading the [] operator
        Numeric_Type* operator[](int row) {
            return data[row];
        }

        //Required for const-correctness
        const Numeric_Type* operator[](int row) const {
            return data[row];
        }

        //addition of two matrices
        template<int OtherRow, int OtherColumn>
        typename std::enable_if<(Cols == OtherColumn && Rows == OtherRow), Matrix<Numeric_Type, Rows, Cols>>::type
        operator+(const Matrix<Numeric_Type, OtherRow, OtherColumn>& other) const {
            Matrix<Numeric_Type, Rows, Cols> result;
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    result[i][j] = (*this)[i][j] + other[i][j];
                }
            }
            return result;
        }

        template<int OtherRow, int OtherColumn>
        typename std::enable_if<(Cols == OtherColumn && Rows == OtherRow), Matrix<Numeric_Type, Rows, Cols>>::type
        operator+(const Matrix<Numeric_Type, OtherRow, OtherColumn>&& other) const {
            Matrix<Numeric_Type, Rows, Cols> result;
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    result[i][j] = (*this)[i][j] + other[i][j];
                }
            }
            return result;
        }

        //matrix multiplication
        template<int OtherRows ,int OtherCols>
        typename std::enable_if<Cols == OtherRows, Matrix<Numeric_Type, Rows, OtherCols>>::type
        operator*(const Matrix<Numeric_Type, OtherRows, OtherCols>& other) const {
            static_assert(Cols == OtherRows,"The given matrix dimensions are not compatible for multiplication");

            Matrix<Numeric_Type, Rows, OtherCols> result;

            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < OtherCols; ++j) {
                    for (int k = 0; k < Cols; ++k) {
                        result[i][j] += (*this)[i][k] * other[k][j];
                    }
                }
            }

            return result;
        }  

        template<int OtherRows, int OtherCols>
        typename std::enable_if<Cols == OtherRows, Matrix<Numeric_Type, Rows, OtherCols>>::type
        operator*(const Matrix<Numeric_Type, OtherRows, OtherCols>&& other) const {
            Matrix<Numeric_Type, Rows, OtherCols> result;

            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < OtherCols; ++j) {
                    for (int k = 0; k < Cols; ++k) {
                        result[i][j] += (*this)[i][k] * other[k][j];
                    }
                }
            }

            return result;
        }

        template<int VectorRows>
        typename std::enable_if<Cols == VectorRows, C_Vector<Numeric_Type, Rows>>::type
        operator*(const C_Vector<Numeric_Type, VectorRows>& other) const {
            C_Vector<Numeric_Type, Rows> result;

            for (int i = 0; i < Rows; ++i) {
                Numeric_Type sum = 0;
                for (int j = 0; j < VectorRows; ++j) {
                    sum += (*this)[i][j] * other[j];
                }
                result[i] = sum;
            }

            return result;
        }


        //Overloading Assignment operator
        Matrix<Numeric_Type, Rows, Cols>& operator=(const Matrix<Numeric_Type, Rows, Cols>& other) {
            if (this != &other) {
                for (int i = 0; i < Rows; ++i) {
                    delete[] data[i];
                }
                delete data;

                int OtherRows = other.rows;
                int OtherCols = other.cols;

                data = new Numeric_Type*[Rows];
                for (int i = 0; i < OtherRows; ++i) {
                    data[i] = new Numeric_Type[Cols]();
                    for (int j = 0; j < OtherCols; ++j) {
                        data[i][j] = other.data[i][j];
                    }
                }
            }
            return *this;
        }

        //determinant of the square matrices only
        template<int dim = Rows>
        typename std::enable_if<(dim == Cols), Numeric_Type>::type determinant() const {
            return determinantHelper(*this);
        }

    private:
        Numeric_Type **data;
        //calculate determinant recursively
        template<int dim = Rows>
        typename std::enable_if<(dim == 1),Numeric_Type>::type determinantHelper(const Matrix& mat) const {
            return mat[0][0];
        }

        template<int dim = Rows>
        typename std::enable_if<(dim == 2), Numeric_Type>::type determinantHelper(const Matrix& mat) const {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }

        template<int dim = Rows>
        typename std::enable_if<(dim > 2), Numeric_Type>::type determinantHelper(const Matrix& mat) const {
            Numeric_Type det = 0;
            for (int j = 0; j < Cols; ++j) {
                Numeric_Type sign = (j % 2 == 0) ? 1 : -1;
                Matrix<Numeric_Type, dim - 1, dim - 1> minorMat;
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