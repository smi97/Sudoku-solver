#pragma once
#include <deque>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>


class Sudoku
{
private:
    std::deque<std::deque<int>> sudoku;
    bool rec_flag, change_flag;
    bool if_dig(int a);

    void check_xy(std::deque<std::deque<int>> sud, int row, int col, std::unordered_set<int> * temp);
    std::deque<std::deque<int>> check_row_ones(std::deque<std::deque<int>> sud);
    std::deque<std::deque<int>> check_col_ones(std::deque<std::deque<int>> sud);
    std::deque<std::deque<int>> check_square_ones(std::deque<std::deque<int>> sud);
    void print(std::deque<std::deque<int>> sud);

    void stand_method();

    void check_sud(std::deque<std::deque<int>> sud);


public:
    Sudoku(std::deque<std::deque<int>> input);

    std::deque<std::deque<int>> get();

    void solve();
};




