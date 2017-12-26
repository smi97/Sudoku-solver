#include <iostream>
#include <deque>
#include <string>
#include <fstream>
#include "sudoku_class.cpp"

std::deque<std::deque<int>> set(std::ifstream & input);

void print(std::ofstream & output_file, std::deque<std::deque<int>> sudoku);

bool if_dig(int a);

int main(int argc, char ** argv)
{
    std::string input_path("./tests/input_"), output_path("./tests/output_");
    input_path += argv[1];
    input_path += ".dat";
    output_path += argv[1];
    output_path += ".ans";

    std::ifstream input_file(input_path);
    try
    {
        std::deque<std::deque<int>> sudoku = set(input_file);
        Sudoku sud(sudoku);
        sud.solve();
        std::ofstream output_file(output_path);
        print(output_file, sud.get());
    }
    catch(std::string except)
    {
        std::cout << except;
    }
    return 0;
}

bool if_dig(std::string a)
{
    std::string b [] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "-1"};
    for(int i = 0; i < 11; i++)
        if (a == b[i])
            return true;
    return false;
}

std::deque<std::deque<int>> set(std::ifstream & input)
{
    std::deque<std::deque<int>> sudoku;
    sudoku.resize(9);
    for (int i = 0, size = sudoku.size(); i < size; ++i)   sudoku[i].resize(9);
    std::string buf;
    int x, row = 0, col = 0;
    if (!input.is_open())
    {
        std::string except("Файл не может быть открыт\n");
        throw except;
    }

    while(!input.eof() && row < 9)
    {
        input >> buf;
        if(buf.empty() || !if_dig(buf))
        {
            std::cout << buf;
            std::string except("Ошибочный файл\n");
            throw except;
        }

        x = atoi(buf.c_str());

        sudoku[row][col] = x;
        col++;
        if(col == 9)
        {
            row++;
            col = 0;
        }
    }
    return sudoku;
}


void print(std::ofstream & output_file, std::deque<std::deque<int>> sudoku)
{
    for(std::deque<std::deque<int>>::iterator it = sudoku.begin(); it != sudoku.end(); it++)
    {
        for(std::deque<int>::iterator it1 = it->begin(); it1 != it->end(); it1++)
        {
            if(*it1 != -1) output_file << *it1;
            else output_file << ".";
            output_file << " ";
        }
        output_file << std::endl;
    }
    output_file << std::endl;
}
