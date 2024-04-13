#include<stdlib.h>
#include<cassert>
#include<concepts>
#include<type_traits>

template<typename T>
concept Numeric_Type = std::is_arithmetic_v<T>;


template<Numeric_Type T, int Rows, int Cols>
class Matrix;

template<Numeric_Type T, int Cols>
class Matrix<T, 1, Cols>;

template<Numeric_Type T, int Rows>
class Matrix<T, Rows, 1>;

template<Numeric_Type T, int size>
using Vector = Matrix<T, 1, size>;

template<Numeric_Type T, int size>
using C_Vector = Matrix<T, size, 1>;