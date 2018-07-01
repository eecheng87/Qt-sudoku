#include "sudoku_solver.h"

sudoku_solver::sudoku_solver()
{

}

bool sudoku_solver::no_zero(int table_num[][9]){
        for(int i = 0 ; i < 9 ;++i)
                for(int j = 0 ; j < 9  ;++j)
                        if(table_num[i][j]==0)
                                return false;
                        return true;//no zero exist!
}
bool sudoku_solver::solve(int table_num[][9]){

        if(no_zero(table_num))
                        return true;

                for(int row = 0 ; row<9 ;++row)
                        for(int col = 0 ; col<9 ;++col){
                                if(table_num[row][col]==0){
                                        for(int try_num=1 ; try_num<=9 ;++try_num){
                                                table_num[row][col]=try_num;
                                                if(all_safe(row,col,table_num)){
                                                        if(solve(table_num))
                                                                return true;
                                                }
                                                if(try_num==9 && !all_safe(row,col,table_num)){
                                                        table_num[row][col]=0;
                                                        return false;
                                                }

                                        }
                                }
                        }
   // return false; //maybe delete
}
bool sudoku_solver::all_safe(int row,int col,int table_num[][9]){
                if(!check_row(row,col,table_num)||!check_col(row,col,table_num)||!check_box(row,col,table_num))
                        return false;
                else
                        return true;
}
bool sudoku_solver::check_row(int row,int col,int table_num[][9]){
        for(int i = 0 ; i < 9 ; ++i)
                if(table_num[row][i] == table_num[row][col] && i!=col)
                        return false;

                        return true;

}
bool sudoku_solver::check_col(int row,int col,int table_num[][9]){
        for(int i = 0 ; i < 9 ; ++i)
                if(table_num[i][col] == table_num[row][col] && i!=row)
                        return false;

                        return true;

}
bool sudoku_solver::check_box(int cur_row,int cur_col,int table_num[][9]){
        int tmpb = cur_col - cur_col%3;
        int tmpa = cur_row - cur_row%3;

        int count[10]={0};//count box data
        for(int start_row = cur_row - cur_row%3 ; start_row<tmpa+3 ; ++start_row)
                for(int start_col = cur_col-cur_col%3 ; start_col<tmpb+3 ; ++start_col)
                        ++count[table_num[start_row][start_col]];
        for(int i = 1 ; i < 10 ; ++i){
                if(count[i]>1)
                        return false;
        }
                        return true;
}

