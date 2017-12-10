class Sudoku
{
private:
    std::vector<std::vector<std::vector<int>>> sudoku;
    bool rec_flag;

    std::vector<int> check_row(std::vector<std::vector<std::vector<int>>> sud, int row);
    std::vector<int> check_column(std::vector<std::vector<std::vector<int>>> sud, int col);
    std::vector<int> check_square(std::vector<std::vector<std::vector<int>>> sud, int row, int col);
    std::vector<int> merge_three(std::vector<int> row, std::vector<int> col, std::vector<int> sqr);
    std::vector<int> check_xy(std::vector<std::vector<std::vector<int>>> sud, int row, int col);
    void check_row_digs(std::vector<std::vector<std::vector<int>>> * sud, int row);

    void check_sud(std::vector<std::vector<std::vector<int>>> sud);

    void print(std::vector<std::vector<std::vector<int>>> sud);



public:
    Sudoku(std::ifstream& input);
    void print(std::ofstream & output_file);
    void solve();

};




