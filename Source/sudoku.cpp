#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "sudoku.hpp"
#include "sudoku.h"


int main(int argc, char ** argv)
{
    std::string input_path("input_"), output_path("output_");
    input_path += argv[2];
    input_path += ".dat";
    output_path += argv[2];
    output_path += ".ans";

    std::ifstream input_file(input_path);
    std::ofstream output_file(output_path);
    try
    {
        Sudoku sud(input_file);
        sud.solve();
        sud.print(output_file);
    }
    catch(std::string except)
    {
        std::cout << except;
    }

    return 0;
}

