#include "sudoku_class.hpp"

Sudoku::Sudoku(std::deque<std::deque<int>> input)
{
    rec_flag = false;
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

std::unordered_set<int> Sudoku::check_xy(std::deque<std::deque<int>> sud, int row, int col)
{
    std::set<int> digs;
    std::unordered_set<int> checked;
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
            checked.insert(i + 1);
    }
    return checked;
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
                auto temp = check_xy(sud, row, col);
                if(temp.size() == 1)
                {
                    sud[row][col] = *temp.begin();
                }
                if(temp.size() == 0)
                {
                    return;
                }
                if(temp.size() > 1)
                {
                    for(auto it : temp)
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
                auto temp = check_xy(sudoku, row, col);
                if(temp.size() == 1)
                {
                    sudoku[row][col] = *temp.begin();
                }
            }
        }
    }
}


void Sudoku::solve()
{
    std::deque<std::deque<int>> sud = sudoku;

    stand_method();
    while(sud != sudoku)
    {
        while(sud != sudoku)
        {
            sud = sudoku;
            stand_method();
        }
        sud = sudoku;
        sudoku = check_row_ones(sudoku);
        while(sud != sudoku)
        {
            sud = sudoku;
            stand_method();
        }
        sudoku = check_col_ones(sudoku);
    }

    check_sud(sudoku);


}

std::deque<std::deque<int>> Sudoku::check_row_ones(std::deque<std::deque<int>> sud)
{
    int mem[9];
    for(int i = 0; i < 9; i++)
    {
        mem[i] = 0;
    }
    for(int row = 0; row < sudoku.size(); row++)
    {
        for(int col = 0; col < sudoku.size(); col++)
        {
            if(sudoku[row][col] == -1)
            {
                auto temp = check_xy(sudoku, row, col);
                if(temp.size() > 1)
                {
                    for(auto it : temp)
                    {
                        mem[it - 1]++;
                    }
                }
            }
        }

        for(int i = 0; i < 9; i++)
        {
            if(mem[i] == 1)
            {
                for(int col = 0; col < sudoku.size(); col++)
                {
                    if(sudoku[row][col] == -1)
                    {
                        auto temp = check_xy(sudoku, row, col);
                        if(temp.size() > 1)
                        {
                            for(auto it : temp)
                            {
                                if(it - 1 == i)
                                    sud[row][col] = i + 1;
                            }
                        }
                    }
                }
            }
            mem[i] = 0;
        }
    }
    return sud;
}

std::deque<std::deque<int>> Sudoku::check_col_ones(std::deque<std::deque<int>> sud)
{
    int mem[9];
    for(int i = 0; i < 9; i++)
    {
        mem[i] = 0;
    }
    for(int col = 0; col < sudoku.size(); col++)
    {
        for(int row = 0; row < sudoku.size(); row++)
        {
            if(sudoku[row][col] == -1)
            {
                auto temp = check_xy(sudoku, row, col);
                if(temp.size() > 1)
                {
                    for(auto it : temp)
                    {
                        mem[it - 1]++;
                    }
                }
            }
        }
        for(int i = 0; i < 9; i++)
        {
            if(mem[i] == 1)
            {
                for(int row = 0; row < sudoku.size(); row++)
                {
                    if(sudoku[row][col] == -1)
                    {
                        auto temp = check_xy(sudoku, row, col);
                        if(temp.size() > 1)
                        {
                            for(auto it : temp)
                            {
                                if(it - 1 == i)
                                    sud[row][col] = i + 1;
                            }
                        }
                    }
                }
            }
            mem[i] = 0;
        }
    }

    return sud;
}

