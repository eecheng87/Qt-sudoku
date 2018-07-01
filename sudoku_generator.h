#ifndef SUDOKU_GENERATOR_H
#define SUDOKU_GENERATOR_H
#include <stdlib.h>
#include <ctime>
#include "sudoku_solver.h" // need us its solve() func

class sudoku_generator
{
public:
    sudoku_generator();
    static int test_table[9][9];
    static void generate();

};

#endif // SUDOKU_GENERATOR_H
