#pragma once
#include <deque>
#include <string>
#include <algorithm>
#include <set>


class Sudoku
{
private:
    std::deque<std::deque<int>> sudoku;
    bool rec_flag;
    bool if_dig(int a);

    std::set<int> check_row(std::deque<std::deque<int>> sud, int row);
    std::set<int> check_column(std::deque<std::deque<int>> sud, int col);
    std::set<int> check_square(std::deque<std::deque<int>> sud, int row, int col);
    std::set<int> check_xy(std::deque<std::deque<int>> sud, int row, int col);

    void check_sud(std::deque<std::deque<int>> sud);


public:
    Sudoku(std::deque<std::deque<int>> input);

    std::deque<std::deque<int>> get();

    void solve();
};




