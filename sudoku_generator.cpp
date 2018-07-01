#include "sudoku_generator.h"
#include <QDebug>
sudoku_generator::sudoku_generator()
{

}
void sudoku_generator::generate(){
   //initialize my table
    for(int i = 0 ; i<9 ;++i)
        for(int j = 0; j<9 ;++j)
            test_table[i][j]=0;


    sudoku_solver SOL;

    srand(time(NULL));

    //set some number to solve , later in for loop to dig out about 40 number

    for(int i = 0 ; i < 4 ; ++i)

        test_table[i][rand()%9] = i ;

    while(1){

        if(SOL.solve(test_table)){

            for(int m = 0 ; m < 9 ; ++m){//row , more content less non zero cell

                test_table[m][rand()%9]=0;
                test_table[m][rand()%9]=0;
                test_table[m][rand()%9]=0;
                test_table[m][rand()%9]=0;
                test_table[m][rand()%9]=0;
                test_table[m][rand()%9]=0;
                test_table[m][rand()%9]=0;

            }
            return;
        }
        else{
            for(int i = 0 ; i < 4 ; ++i)
                test_table[i][rand()%9] = i ;
        }

    }

    return;
}
