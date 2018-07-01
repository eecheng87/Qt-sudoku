#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H



class sudoku_solver
{
public:
    sudoku_solver();
    static bool check_row(int row,int col,int table_num[][9]);
    static bool check_col(int row,int col,int table_num[][9]);
    static bool check_box(int cur_row,int cur_col,int table_num[][9]);
    static bool all_safe(int row,int col,int table_num[][9]);
    static bool solve(int table_num[][9]);
    static bool no_zero(int table_num[][9]);

    static int table_num[9][9]; // access my table's data]
};

#endif // SUDOKU_SOLVER_H
