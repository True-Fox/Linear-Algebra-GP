#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"

template<typename T, int Cols>
class Matrix<T, 1, Cols>{

        private:
        T *data;
        int Rows = 1;
    public:
        //Constructor
        Matrix(){
            data = new T[Cols];
        }

        // template<typename... Args>
        // Matrix(Args&&... args) {
        //     data = new T[Cols];
        //     int index = 0;
        //     ((data[index++] = static_cast<T>(args)), ...);
        // }

        Matrix(std::initializer_list<T> list){
            data = new T[Cols];

            auto it = list.begin();
            for (int i = 0; i < Cols; ++i) {
                    data[i] = (it != list.end()) ? *it++ : 0;
            }
        }

        //Destructor
        ~Matrix(){
            delete[] data;
        }

        //get number of rows
        int getRows(){
            return 1;
        }

        //get number of columns
        int getCols(){
            return Cols;
        }

        //Overloading the [] operator
        T& operator[](int row) {
            return data[row];
        }

        //Required for const-correctness
        const T& operator[](int row) const {
            return data[row];
        }
};

template<typename T, int Rows>
class Matrix<T, Rows, 1>{

        private:
        T *data;
        int Cols = 1;
    public:
        //Constructor
        Matrix(){
            data = new T[Rows];
        }

        //Intialize matrix with arguments
        //Example: Matrix<int, 2,2> M(1,2,3,4)
        template<typename... Args>
        Matrix(Args&&... args) {
            data = new T[Rows];
            int index = 0;
            ((data[index++] = args), ...);
        }

        //Intialize matrix with list
        //Example: Matrix<int, 2,2> M {1,2,3,4}
        Matrix(std::initializer_list<T> list){
            data = new T[Rows];

            auto it = list.begin();
            for (int i = 0; i < Rows; ++i) {
                    data[i] = (it != list.end()) ? *it++ : 0;
            }
        }

        //Destructor
        ~Matrix(){
            delete[] data;
        }

        //get number of rows
        int getRows(){
            return Rows;
        }

        //get number of columns
        int getCols(){
            return 1;
        }

        //Overloading the [] operator
        T& operator[](int row) {
            return data[row];
        }

        //Required for const-correctness
        const T& operator[](int row) const {
            return data[row];
        }
};

template<typename T, int size>
using Vector = Matrix<T, 1, size>;

template<typename T, int size>
using C_Vector = Matrix<T, size, 1>;

#endif 