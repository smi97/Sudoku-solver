#include "sudoku_class.hpp"

Sudoku::Sudoku(std::deque<std::deque<int>> input)
{
    rec_flag = false;
    change_flag = false;
    sudoku.resize(9);
    for (int i = 0, size = sudoku.size(); i < size; ++i)
        sudoku[i] = input[i];

}

std::deque<std::deque<int>> Sudoku::get()
{
    return sudoku;
}

void Sudoku::print(std::deque<std::deque<int>> sud)
{
    for(int row = 0; row < sud.size(); row++)
    {
        for(int col = 0; col < sud.size(); col++)
        {
            if(sud[row][col] != -1) std::cout << sud[row][col];
            else std::cout << ".";
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

void Sudoku::check_xy(std::deque<std::deque<int>> sud, int row, int col, std::unordered_set<int> * checked)
{
    std::unordered_set<int> digs;
    for(auto it : sud[row])
    {
        if(it != -1)
            digs.insert(it);
    }

    for(int i = 0; i < sud.size(); i++)
    {
        if(sud[i][col] != -1)
            digs.insert(sud[i][col]);
    }

    int beg_row = row - row % 3, end_row = row + (3 - row % 3);
    int beg_col = col - col % 3, end_col = col + (3 - col % 3);
    for(int i = beg_row; i < end_row; i++)
    {
        for(int j = beg_col; j < end_col; j++)
            if(sud[i][j] != -1)
                digs.insert(sud[i][j]);
    }
    
    for(int i = 0; i < 9; i++)
    {
        if(digs.find(i + 1) == digs.end())
            checked->insert(i + 1);
    }
}

void Sudoku::check_sud(std::deque<std::deque<int>> sud)
{
    if(rec_flag)
        return;

    bool flag = true;

    for(int row = 0; row < sud.size(); row++)
    {
        for(int col = 0; col < sud.size(); col++)
        {
            if(sud[row][col] == -1)
            {
                flag = false;
                std::unordered_set<int> * temp = new std::unordered_set<int>;
                check_xy(sud, row, col, temp);
                if(temp->size() == 1)
                {
                    sud[row][col] = *temp->begin();
                }
                if(temp->size() == 0)
                {
                    return;
                }
                if(temp->size() > 1)
                {
                    for(auto it : *temp)
                    {
                        sud[row][col] = it;
                        check_sud(sud);
                        if(rec_flag)
                            return;
                    }
                }
            }
        }
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


void Sudoku::stand_method()
{
    bool flag = true;
    for(int row = 0; row < sudoku.size(); row++)
    {
        for(int col = 0; col < sudoku.size(); col++)
        {
            if(sudoku[row][col] == -1)
            {
                flag = false;
                std::unordered_set<int> temp;
                check_xy(sudoku, row, col, &temp);
                if(temp.size() == 1)
                {
                    sudoku[row][col] = *temp.begin();
                    change_flag = true;
                }
            }
        }
    }
    if(flag) rec_flag = true;
}

void Sudoku::solve()
{
    stand_method();
    if(rec_flag) return;
    while(change_flag)
    {
        while(change_flag)
        {
            change_flag = false;
            stand_method();
            if(rec_flag) return;
        }
        change_flag = false;
        sudoku = check_row_ones(sudoku);
        while(change_flag)
        {
            change_flag = false;
            stand_method();
            if(rec_flag) return;
        }
        change_flag = false;
        sudoku = check_col_ones(sudoku);
        while(change_flag)
        {
            change_flag = false;
            stand_method();
            if(rec_flag) return;
        }
        change_flag = false;
        sudoku = check_square_ones(sudoku);
    }

    check_sud(sudoku);
}

std::deque<std::deque<int>> Sudoku::check_row_ones(std::deque<std::deque<int>> sud)
{
    int mem[9];
    for(int row = 0; row < sudoku.size(); row++)
    {
        for(int i = 0; i < 9; i++)
        {
            mem[i] = 0;
        }
        std::unordered_map<int, std::pair<int, int>> memas;
        for(int col = 0; col < sudoku.size(); col++)
        {
            if(sudoku[row][col] == -1)
            {
                std::unordered_set<int> temp;
                check_xy(sudoku, row, col, &temp);
                if(temp.size() > 1)
                {
                    for(auto it : temp)
                    {
                        mem[it - 1]++;
                        if(mem[it - 1] == 1)
                        {
                            std::pair<int,int> cord(row, col);
                            memas.insert(std::pair<int, std::pair<int,int>>(it - 1, cord));
                        }
                        if(mem[it - 1] > 1)
                        {
                            memas.erase(it - 1);
                        }
                    }
                }
            }
        }

        for(auto it : memas)
        {
            sud[it.second.first][it.second.second] = it.first + 1;
            change_flag = true;
        }
    }

    return sud;
}

std::deque<std::deque<int>> Sudoku::check_col_ones(std::deque<std::deque<int>> sud)
{
    int mem[9];

    for(int col = 0; col < sudoku.size(); col++)
    {
        for(int i = 0; i < 9; i++)
        {
            mem[i] = 0;
        }
        std::unordered_map<int, std::pair<int, int>> memas;
        for(int row = 0; row < sudoku.size(); row++)
        {
            if(sudoku[row][col] == -1)
            {
                std::unordered_set<int> temp;
                check_xy(sudoku, row, col, &temp);
                if(temp.size() > 1)
                {
                    for(auto it : temp)
                    {
                        mem[it - 1]++;
                        if(mem[it - 1] == 1)
                        {
                            std::pair<int,int> cord(row, col);
                            memas.insert(std::pair<int, std::pair<int,int>>(it - 1, cord));
                        }
                        if(mem[it - 1] > 1)
                        {
                            memas.erase(it - 1);
                        }
                    }
                }
            }
        }

        for(auto it : memas)
        {
            sud[it.second.first][it.second.second] = it.first + 1;
            change_flag = true;
        }
    }

    return sud;
}

std::deque<std::deque<int>> Sudoku::check_square_ones(std::deque<std::deque<int>> sud)
{
    int mem[9], n = 0, m = 0, sq_counter = 0;

    while(sq_counter != 9)
    {
        for(int i = 0; i < 9; i++)
        {
            mem[i] = 0;
        }
        std::unordered_map<int, std::pair<int, int>> memas;
        for(int row = n; row < n + 3; row++)
        {
            for(int col = m; col < m + 3; col++)
            {
                if(sudoku[row][col] == -1)
                {
                    std::unordered_set<int> temp;
                    check_xy(sudoku, row, col, &temp);
                    if(temp.size() > 1)
                    {
                        for(auto it : temp)
                        {
                            mem[it - 1]++;
                            if(mem[it - 1] == 1)
                            {
                                std::pair<int,int> cord(row, col);
                                memas.insert(std::pair<int, std::pair<int,int>>(it - 1, cord));
                            }
                            if(mem[it - 1] > 1)
                            {
                                memas.erase(it - 1);
                            }
                        }
                    }
                }
            }
        }
        if(sq_counter < 2)
        {
            m += 3;
        }
        if(sq_counter > 1 && sq_counter < 5)
        {
            if(sq_counter == 2)
            {
                m = 0;
                n += 3;
            }
            else m += 3;
        }
        if(sq_counter > 4)
        {
            if(sq_counter == 5)
            {
                m = 0;
                n += 3;
            }
            else m += 3;
        }
        sq_counter++;

        for(auto it : memas)
        {
            sud[it.second.first][it.second.second] = it.first + 1;
            change_flag = true;
        }
    }

    return sud;
}

