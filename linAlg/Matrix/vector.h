#include "matrix.h"

template<typename T, int size>
using Vector = Matrix<T, 1, size>;

template<typename T, int size>
using C_Vector = Matrix<T, size, 1>;

