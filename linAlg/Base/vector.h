#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"
#include <math.h>

//Forward Declarations 

// Forward declaration of Matrix class template
template<Numeric T, int Rows, int Cols>
class Matrix;

// Forward declaration of Matrix specialization for a row vector
template<Numeric T, int Cols>
class Matrix<T, 1, Cols>;

// Forward declaration of Matrix specialization for a column vector
template<Numeric T, int Rows>
class Matrix<T, Rows, 1>;

// Alias for row vector
template<Numeric T, int size>
using Vector = Matrix<T, 1, size>;

//Alias for column vector
template<Numeric T, int size>
using C_Vector = Matrix<T, size, 1>;


// Matrix specialization for row vector
template<Numeric T, int Cols>
class Matrix<T, 1, Cols>{

        private:
        T *data;
        int Rows = 1;
    public:
        //Constructor
        Matrix(){
            data = new T[Cols];
        }


        Matrix(std::initializer_list<T> list){
            if(list.size() != Cols){
                throw std::invalid_argument("Initializer list size does not match Vector size");
            }
            data = new T[Cols];

            auto it = list.begin();
            for (int i = 0; i < Cols; ++i) {
                    data[i] = (it != list.end()) ? *it++ : 0;
            }
        }

        // Overloading addition for row vectors
        template<int OtherCols>
        typename std::enable_if<Cols == OtherCols, Vector<T, Cols>>::type
        operator+(Vector<T, OtherCols>& other){
            static_assert(Cols==OtherCols, "The dimensions do not match for the operation performed.");
            Vector<T, Cols> result;
            for(int i=0;i<Cols;i++){
                result[i] = (*this)[i] + other[i];
            }
            return result;
        }


        // Overloading subtraction for row vectors
        template<int OtherCols>
        typename std::enable_if<Cols == OtherCols, Vector<T, Cols>>::type
        operator-(Vector<T, OtherCols>& other){
            static_assert(Cols==OtherCols, "The dimensions do not match for the operation performed.");
            Vector<T, Cols> result;
            for(int i=0;i<Cols;i++){
                result[i] = (*this)[i] - other[i];
            }
            return result;
        }

        // Overloading mulitplication for vector matrix multiplication
        template<int MatrixRows, int MatrixCols>
        typename std::enable_if<Cols == MatrixRows, Vector<T, MatrixCols>>::type
        operator*(const Matrix<T, MatrixRows, MatrixCols>& other)const{
            static_assert(Cols == MatrixRows,"The given dimensions are not compatible for multiplication");

            Vector<T, MatrixCols> result;

            for(int i=0; i<MatrixRows; i++){
                T sum = 0;
                for(int j=0; j<Cols; j++){
                    sum = sum + ((*this)[j] * other[j][i]);
                }
                result[i] = sum;
            }

            return result;
        }

        // Overload multiplication operator for vector-column vector multiplication
        template<int ColRows>
        typename std::enable_if<Cols == ColRows, T>::type
        operator*(const C_Vector<T,ColRows>& other){
            static_assert(Cols == ColRows,"The given dimensions are not compatible for multiplication");

            T result;

            for(int i=0; i<Cols; i++){
                T sum = 0;
                for(int j=0; j<ColRows; j++){
                    sum = sum + ((*this)[i] * other[j]);
                }
                result = sum;
            }

            return result;
        }

        // Calculate the magnitude of the vector
        double magnitude_helper(T value) const {
            return value * value;
        }

        template<typename... Args>
        double magnitude_helper(T first, Args... args) const {
            return first * first + magnitude_helper(args...);
        }

        double magnitude() const {
            return std::sqrt(magnitude_helper(data[0], data[1]));
        }

        //Destructor
        ~Matrix(){
            delete[] data;
        }

        // Get number of rows
        int getRows(){
            return 1;
        }

        // Get number of columns
        int getCols(){
            return Cols;
        }

        // Overloading the [] operator
        T& operator[](int row) {
            return data[row];
        }

        // Required for const-correctness
        const T& operator[](int row) const {
            return data[row];
        }
};

// Matrix specialization for column vectors
template<Numeric T, int Rows>
class Matrix<T, Rows, 1>{

        private:
        T *data;
        int Cols = 1;
    public:
        //Constructor
        Matrix(){
            data = new T[Rows];
        }

        //Intialize matrix with list
        //Example: Matrix<int, 2,2> M {1,2,3,4}
        Matrix(std::initializer_list<T> list){
            if(list.size() != Rows){
                throw std::invalid_argument("Initializer list size does not match Vector size");
            }
            data = new T[Rows];

            auto it = list.begin();
            for (int i = 0; i < Rows; ++i) {
                    data[i] = (it != list.end()) ? *it++ : 0;
            }
        }

        // Overload addition operator for column vector addition
        template<int OtherRows>
        typename std::enable_if<Rows==OtherRows, C_Vector<T, Rows>>::type
        operator+(C_Vector<T, OtherRows>& other){
            static_assert(Rows==OtherRows, "The dimensions do not match for the operation performed.");
            C_Vector<T, Rows> result;
            for(int i=0;i<Rows;i++){
                result[i] = (*this)[i] + other[i];
            }
            return result;
        }

        // Overload subtraction operator for column vector subtraction
        template<int OtherRows>
        typename std::enable_if<Rows==OtherRows, C_Vector<T, Rows>>::type
        operator-(C_Vector<T, OtherRows>& other){
            static_assert(Rows==OtherRows, "The dimensions do not match for the operation performed.");
            C_Vector<T, Rows> result;
            for(int i=0;i<Rows;i++){
                result[i] = (*this)[i] - other[i];
            }
            return result;
        }        

        // Overload multiplication operator for column vector-matrix multiplication
        template<int MatrixCols>
        Matrix<T, Rows, MatrixCols> operator*(Vector<T, MatrixCols>& other){
            Matrix<T, Rows, MatrixCols> result;

            for(int i=0; i<Rows; i++){
                for(int j=0; j<MatrixCols; j++){
                    result[i][j] = result[i][j] + ((*this)[i]*other[j]);
                }
            }

            return result;
        }

        // Calculate the magnitude of the vector
        double magnitude_helper(T value) const {
            return value * value;
        }

        template<typename... Args>
        double magnitude_helper(T first, Args... args) const {
            return first * first + magnitude_helper(args...);
        }

        double magnitude() const {
            return std::sqrt(magnitude_helper(data[0], data[1]));
        }

        //Destructor
        ~Matrix(){
            delete[] data;
        }

        // Get number of rows
        int getRows(){
            return Rows;
        }

        // Get number of columns
        int getCols(){
            return 1;
        }

        // Overloading the [] operator
        T& operator[](int row) {
            return data[row];
        }

        // Required for const-correctness
        const T& operator[](int row) const {
            return data[row];
        }
};

#endif 
