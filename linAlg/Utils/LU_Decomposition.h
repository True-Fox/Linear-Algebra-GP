#include "../Base/matrix.h"
#include "../Base/vector.h"

template<Numeric T, int Rows, int Cols>
class __LU_Decompose{
    public:
        __LU_Decompose(const Matrix<T, Rows, Cols>& matrix){

            for(int i=0;i<Rows;i++){
                for(int j=0;j<Cols;j++){
                    L[i][i]=1;
                }
            }

            for(int k=0; k<Rows; k++){
                for(int j=k; j<Cols; ++j){
                    U[k][j] = matrix[k][j];
                    for(int p=0; p<k; p++){
                        U[k][j] -= L[k][p]*U[p][j];
                    }
                }

                for(int i=k+1; i<Rows; i++){
                    L[i][k] = matrix[i][k];
                    for(int p=0;p<k;p++){
                        L[i][k] -= L[i][p] * U[p][k];
                    }
                    L[i][k] /= U[k][k];
                }
            }
        };

        Matrix<double, Rows, Cols> L;
        Matrix<double, Rows, Cols> U;

};


template<typename T, int Rows, int Cols>
typename std::enable_if<Rows==Cols,__LU_Decompose<T, Rows, Cols>>::type
LU_Decompose(const Matrix<T, Rows, Cols>& mat){
    return __LU_Decompose<T, Rows, Cols>(mat);
}