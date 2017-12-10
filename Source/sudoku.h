
bool Sudoku::if_dig(char a)
{
    char b [] = {"1234567890"};
    for(int i = 0; i < 10; i++)
        if (a == b[i])
            return true;
    return false;
}

Sudoku::Sudoku(std::ifstream& input)
{
    rec_flag = false;
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
        if(buf.empty() || buf.size() != 1 || !if_dig(buf[0]))
        {
            std::string except("Ошибочный файл\n");
            throw except;
        }

        x = atoi(buf.c_str());
        sudoku[row][col].push_back(x);
        col++;
        if(col == 9)
        {
            row++;
            col = 0;
        }
    }

}

void Sudoku::print(std::ofstream & output_file)
{
    for(std::vector<std::vector<std::vector<int>>>::iterator it = sudoku.begin(); it != sudoku.end(); it++)
    {
        for(std::vector<std::vector<int>>::iterator it1 = it->begin(); it1 != it->end(); it1++)
        {
            if(it1->front() != -1) output_file << it1->front();
            else output_file << ".";
            output_file << " ";
        }
        output_file << std::endl;
    }
    output_file << std::endl;

}

std::vector<int> Sudoku::check_row(std::vector<std::vector<std::vector<int>>> sud, int row)
{
    std::vector<int> b;
    int pos = 0;
    for(std::vector<std::vector<std::vector<int>>>::iterator it = sud.begin(); it != sud.end(); it++)
    {
        if (pos == row)
        {
            for(std::vector<std::vector<int>>::iterator it1 = it->begin(); it1 != it->end(); it1++)
            {
                if((it1->size() == 1) && (it1->front() != -1) )
                    for(std::vector<int>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
                    {
                        b.push_back(*it2);
                    }
            }
            break;
        }
        pos++;
    }
    return b;
}

std::vector<int> Sudoku::check_column(std::vector<std::vector<std::vector<int>>> sud, int col)
{
    std::vector<int> b;

    for(std::vector<std::vector<std::vector<int>>>::iterator it = sud.begin(); it != sud.end(); it++)
    {
        int pos = 0;
        for(std::vector<std::vector<int>>::iterator it1 = it->begin(); it1 != it->end(); it1++)
        {
            if((it1->size() == 1) && (pos == col) && (it1->front() != -1))
            {
                for(std::vector<int>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
                {
                    b.push_back(*it2);
                }
                break;
            }
            pos++;
        }
    }

    return b;
}

std::vector<int> Sudoku::check_square(std::vector<std::vector<std::vector<int>>> sud, int row, int col)
{
    int beg_row = row - row % 3, end_row = row + (3 - row % 3);
    int beg_col = col - col % 3, end_col = col + (3 - col % 3);
    int pos_row = 0;
    std::vector<int> b;
    for(std::vector<std::vector<std::vector<int>>>::iterator it = sud.begin(); it != sud.end(); it++)
    {
        int pos_col = 0;
        if ((pos_row >= beg_row) && (pos_row < end_row))
            for(std::vector<std::vector<int>>::iterator it1 = it->begin(); it1 != it->end(); it1++)
            {
                if((pos_col >= beg_col) && (pos_col < end_col) &&  (it1->front() != -1))
                    for(std::vector<int>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
                    {
                        b.push_back(*it2);
                    }
                pos_col++;
            }
        pos_row++;
    }
    return b;
}

std::vector<int> Sudoku::merge_three(std::vector<int> row, std::vector<int> col, std::vector<int> sqr)
{
    std::vector<int> vectorMerged, vectorMerged1;
    sort(row.begin(), row.end());
    sort(col.begin(), col.end());
    sort(sqr.begin(), sqr.end());
    vectorMerged.resize(row.size() + col.size());
    merge(row.begin(),row.end(),col.begin(),col.end(),vectorMerged.begin());
    vectorMerged1.resize(vectorMerged.size() + sqr.size());
    merge(vectorMerged.begin(),vectorMerged.end(),sqr.begin(),sqr.end(),vectorMerged1.begin());
    return vectorMerged1;
}

std::vector<int> Sudoku::check_xy(std::vector<std::vector<std::vector<int>>> sud, int row, int col)
{
    std::vector<int> a, b, c, m;
    a = check_row(sud, row);
    b = check_column(sud, col);
    c = check_square(sud, row, col);
    m = merge_three(a, b, c);
    bool fl[9];
    for(int i = 0; i < 9; i++)
        fl[i] = true;
    for(std::vector<int>::iterator it = m.begin(); it != m.end(); it++)
    {
        fl[*it - 1] = false;
    }
    m.clear();
    for(int i = 0; i < 9; i++)
        if(fl[i]) m.push_back(i + 1);
    return m;
}

void Sudoku::check_sud(std::vector<std::vector<std::vector<int>>> sud)
{

    if(rec_flag)
        return;
    int pos_row = 0;
    bool flag = true;
    for(std::vector<std::vector<std::vector<int>>>::iterator it = sud.begin(); it != sud.end(); it++)
    {
        int pos_col = 0;
        for(std::vector<std::vector<int>>::iterator it1 = it->begin(); it1 != it->end(); it1++)
        {
            if(it1->front() == -1)
            {
                flag = false;
                std::vector<int> temp = check_xy(sud, pos_row, pos_col);
                if(temp.size() == 1)
                {
                    it1->front() = temp.front();
                }
                if(temp.size() == 0)
                    return;
                if(temp.size() > 1)
                {
                    for(std::vector<int>::iterator it2 = temp.begin(); it2 != temp.end(); it2++)
                    {
                        it1->front() = *it2;
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
