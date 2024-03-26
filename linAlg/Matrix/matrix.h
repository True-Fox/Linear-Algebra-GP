#include<stdlib.h>

/*Base Matrix Class
    - getCols() : Returns the number of columns
    - getRows() : Returns the number of rows
*/
template<typename T, int Rows, int Cols>
class Matrix{
    private:
        T **data;
    public:
        //Constructor
        Matrix(){
            data = (T**)std::calloc(Rows, sizeof(T*));
            for(int i = 0; i<Rows; i++){
                data[i] = (T*)std::calloc(Cols, sizeof(T*));
            }
        }

        //Destructor
        ~Matrix(){
            for(int i = 0; i<Rows; i++){
                free(data[i]);
            }
            free(data);
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
};

template<typename T, int Cols>
class Matrix<T, 1, Cols>{

        private:
        T *data;
        int Rows = 1;
    public:
        //Constructor
        Matrix(){
            data = (T*)std::calloc(Cols, sizeof(T*));
        }

        //Destructor
        ~Matrix(){
            free(data);
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
            data = (T*)std::calloc(Rows, sizeof(T*));
        }

        //Destructor
        ~Matrix(){
            free(data);
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
        T& operator[](int row) {
            return data[row];
        }

        //Required for const-correctness
        const T& operator[](int row) const {
            return data[row];
        }
};