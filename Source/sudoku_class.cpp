#include "sudoku_class.hpp"

Sudoku::Sudoku(std::deque<std::deque<int>> input)
{
    rec_flag = false;
    sudoku.resize(9);
    for (int i = 0, size = sudoku.size(); i < size; ++i)   sudoku[i] = input[i];
}

std::deque<std::deque<int>> Sudoku::get()
{
    return sudoku;
}

std::set<int> Sudoku::check_row(std::deque<std::deque<int>> sud, int row)
{
    std::set<int> b;
    for(auto it : sud[row])
    {
        if(it != -1)
            b.insert(it);
    }
    return b;
}

std::set<int> Sudoku::check_column(std::deque<std::deque<int>> sud, int col)
{
    std::set<int> b;

    for(int i = 0; i < sud.size(); i++)
    {
        if(sud[i][col] != -1)
            b.insert(sud[i][col]);
    }
    return b;
}

std::set<int> Sudoku::check_square(std::deque<std::deque<int>> sud, int row, int col)
{
    int beg_row = row - row % 3, end_row = row + (3 - row % 3);
    int beg_col = col - col % 3, end_col = col + (3 - col % 3);
    int pos_row = 0;
    std::set<int> b;
    for(int i = beg_row; i < end_row; i++)
    {
        for(int j = beg_col; j < end_col; j++)
            if(sud[i][j] != -1)
                b.insert(sud[i][j]);
    }
    return b;
}


std::set<int> Sudoku::check_xy(std::deque<std::deque<int>> sud, int row, int col)
{
    std::set<int> rows, cols, squs, checked;
    rows = check_row(sud, row);
    cols = check_column(sud, col);
    squs = check_square(sud, row, col);
    rows.insert(cols.begin(), cols.end());
    rows.insert(squs.begin(), squs.end());

    bool fl[9];
    for(int i = 0; i < 9; i++)
        fl[i] = true;
    for(auto it : rows)
    {
        fl[it - 1] = false;
    }
    for(int i = 0; i < 9; i++)
        if(fl[i]) checked.insert(i + 1);
    return checked;
}

void Sudoku::check_sud(std::deque<std::deque<int>> sud)
{
    if(rec_flag)
        return;
    int pos_row = 0;
    bool flag = true;
    for(auto it = sud.begin(); it != sud.end(); it++)
    {
        int pos_col = 0;
        for(auto it1 = it->begin(); it1 != it->end(); it1++)
        {
            if(*it1 == -1)
            {
                flag = false;
                auto temp = check_xy(sud, pos_row, pos_col);
                if(temp.size() == 1)
                {
                    *it1 = *temp.begin();
                }
                if(temp.size() == 0)
                    return;
                if(temp.size() > 1)
                {
                    for(auto it2 : temp)
                    {
                        *it1 = it2;
                        check_sud(sud);
                        if(rec_flag)
                            return;
                    }
                }
            }
            pos_col++;
        }
        pos_row++;
    }
    if(flag)
    {
        sudoku = sud;
        rec_flag = true;
        return;
    }
    check_sud(sud);

    return;
}

void Sudoku::solve()
{
    check_sud(sudoku);
}

