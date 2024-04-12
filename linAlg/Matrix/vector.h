#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"

//Forward Declarations (I am not sure why yet)

template<typename T, int Rows, int Cols>
class Matrix;

template<typename T, int Cols>
class Matrix<T, 1, Cols>;

template<typename T, int Rows>
class Matrix<T, Rows, 1>;

template<typename T, int size>
using Vector = Matrix<T, 1, size>;

template<typename T, int size>
using C_Vector = Matrix<T, size, 1>;



template<typename Numeric_Type, int Cols>
class Matrix<Numeric_Type, 1, Cols>{

        private:
        Numeric_Type *data;
        int Rows = 1;
    public:
        //Constructor
        Matrix(){
            data = new Numeric_Type[Cols];
        }


        Matrix(std::initializer_list<Numeric_Type> list){
            if(list.size() != Cols){
                throw std::invalid_argument("Initializer list size does not match Vector size");
            }
            data = new Numeric_Type[Cols];

            auto it = list.begin();
            for (int i = 0; i < Cols; ++i) {
                    data[i] = (it != list.end()) ? *it++ : 0;
            }
        }

        template<int OtherCols>
        typename std::enable_if<Cols == OtherCols, Vector<Numeric_Type, Cols>>::type
        operator+(Vector<Numeric_Type, OtherCols>& other){
            static_assert(Cols==OtherCols, "The dimensions do not match for the operation performed.");
            Vector<Numeric_Type, Cols> result;
            for(int i=0;i<Cols;i++){
                result[i] = (*this)[i] + other[i];
            }
            return result;
        }

        template<int MatrixRows, int MatrixCols>
        typename std::enable_if<Cols == MatrixRows, Vector<Numeric_Type, MatrixCols>>::type
        operator*(const Matrix<Numeric_Type, MatrixRows, MatrixCols>& other)const{
            static_assert(Cols == MatrixRows,"The given dimensions are not compatible for multiplication");

            Vector<Numeric_Type, MatrixCols> result;

            for(int i=0; i<MatrixRows; i++){
                Numeric_Type sum = 0;
                for(int j=0; j<Cols; j++){
                    sum = sum + ((*this)[j] * other[j][i]);
                }
                result[i] = sum;
            }

            return result;
        }

        template<int ColRows>
        typename std::enable_if<Cols == ColRows, Numeric_Type>::type
        operator*(const C_Vector<Numeric_Type,ColRows>& other){
            static_assert(Cols == ColRows,"The given dimensions are not compatible for multiplication");

            Numeric_Type result;

            for(int i=0; i<Cols; i++){
                Numeric_Type sum = 0;
                for(int j=0; j<ColRows; j++){
                    sum = sum + ((*this)[i] * other[j]);
                }
                result = sum;
            }

            return result;
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
        Numeric_Type& operator[](int row) {
            return data[row];
        }

        //Required for const-correctness
        const Numeric_Type& operator[](int row) const {
            return data[row];
        }
};

template<typename Numeric_Type, int Rows>
class Matrix<Numeric_Type, Rows, 1>{

        private:
        Numeric_Type *data;
        int Cols = 1;
    public:
        //Constructor
        Matrix(){
            data = new Numeric_Type[Rows];
        }

        //Intialize matrix with list
        //Example: Matrix<int, 2,2> M {1,2,3,4}
        Matrix(std::initializer_list<Numeric_Type> list){
            if(list.size() != Rows){
                throw std::invalid_argument("Initializer list size does not match Vector size");
            }
            data = new Numeric_Type[Rows];

            auto it = list.begin();
            for (int i = 0; i < Rows; ++i) {
                    data[i] = (it != list.end()) ? *it++ : 0;
            }
        }

        template<int OtherRows>
        typename std::enable_if<Rows==OtherRows, C_Vector<Numeric_Type, Rows>>::type
        operator+(C_Vector<Numeric_Type, OtherRows>& other){
            static_assert(Rows==OtherRows, "The dimensions do not match for the operation performed.");
            C_Vector<Numeric_Type, Rows> result;
            for(int i=0;i<Rows;i++){
                result[i] = (*this)[i] + other[i];
            }
            return result;
        }

        template<int MatrixCols>
        Matrix<Numeric_Type, Rows, MatrixCols> operator*(Vector<Numeric_Type, MatrixCols>& other){
            Matrix<Numeric_Type, Rows, MatrixCols> result;

            for(int i=0; i<Rows; i++){
                for(int j=0; j<MatrixCols; j++){
                    result[i][j] = result[i][j] + ((*this)[i]*other[j]);
                }
            }

            return result;
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
        Numeric_Type& operator[](int row) {
            return data[row];
        }

        //Required for const-correctness
        const Numeric_Type& operator[](int row) const {
            return data[row];
        }
};

#endif 