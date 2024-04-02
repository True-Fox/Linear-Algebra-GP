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
            data = new T*[Rows];
            for(int i = 0; i<Rows; i++){
                data[i] = new T[Cols]();
            }
        }

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

        template<typename... Args>
        Matrix(Args&&... args) {
            data = new T*[Rows];
            for (int i = 0; i < Rows; ++i) {
                data[i] = new T[Cols](); 
            }

            int index = 0;
            ([&]{
                int row = index/Cols;
                int cols = index%Cols;
                data[row][cols] = args;
                ++index;
            }(),...);
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
        T* operator[](int row) {
            return data[row];
        }

        //Required for const-correctness
        const T* operator[](int row) const {
            return data[row];
        }
};