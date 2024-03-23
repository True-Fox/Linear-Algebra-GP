#include<stdlib.h>

/*Base Matrix Class
    - getCols() : Returns the number of columns
    - getRows() : Returns the number of rows
*/
class Matrix{
    private:
        int rows, cols;
        double **data;
    public:
        //Constructor
        Matrix(int rows, int cols):rows(rows),cols(cols){
            data = (double**)std::calloc(rows, sizeof(double*));
            for(int i = 0; i<rows; i++){
                data[i] = (double*)std::calloc(cols, sizeof(double*));
            }
        }

        //Destructor
        ~Matrix(){
            for(int i = 0; i<rows; i++){
                free(data[i]);
            }
            free(data);
        }

        //get number of rows
        int getRows(){
            return rows;
        }

        //get number of columns
        int getCols(){
            return cols;
        }

        //Overloading the [] operator
        double* operator[](int row) {
            return data[row];
        }

        //Required for const-correctness
        const double* operator[](int row) const {
            return data[row];
        }

};