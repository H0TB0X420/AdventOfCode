#include "day4.h"
#include <string>
#include <vector>
#include <utility>
#include <iostream>

PrintingDepartment::PrintingDepartment(std::string file_name): fp_(file_name)
{
}

auto PrintingDepartment::ResetFp() -> void {
    fp_.clear();
    fp_.seekg(0, std::ios::beg);
}

auto PrintingDepartment::GetAccessibleRolls() -> int{
    std::vector<std::vector<char>> grid;
    std::string line;
    while (std::getline(fp_, line)){
        std::vector<char> row = {};
        for (const auto& cell: line){
            row.push_back(cell);
        }
        grid.push_back(row);
    }
    row_bounds_ = grid.size();
    col_bounds_ = grid[0].size();
    std::cout<<"Rows: " << row_bounds_ << std::endl;
    std::cout<<"Cols: " << col_bounds_ << std::endl;
    int total = 0;
    int prev_total = 0;
    do {
        
        prev_total = total;
        for (size_t r = 0; r < row_bounds_; ++r){
            for (size_t c = 0; c < col_bounds_; ++c){
                if (grid[r][c] == '@'){ 
                    std::vector<std::pair<int, int>> dirs = {
                            std::make_pair(r-1, c-1),std::make_pair(r-1, c), std::make_pair(r-1, c+1),
                            std::make_pair(r, c-1), std::make_pair(r, c+1),
                            std::make_pair(r+1, c-1), std::make_pair(r+1, c), std::make_pair(r+1, c+1)
                            };
                    int adjacent_rolls = 0;
                    for (const auto [dr, dc]: dirs){
                       
                        if (InBounds(dr, dc) && (grid[dr][dc] == '@' || grid[dr][dc] == 'x')){
                            ++adjacent_rolls;
                        }
                    }
                    if (adjacent_rolls < 4){
                        grid[r][c] = 'x';
                        ++total;
                    }
                }
            }
        }
        for (size_t r = 0; r < row_bounds_; ++r){
            for (size_t c = 0; c < col_bounds_; ++c){
                if (grid[r][c] == 'x'){
                    grid[r][c] = '.';
                }
            }
        }
    } while(total != prev_total);
    return total;
}

auto PrintingDepartment::InBounds(int row, int col) -> bool{
    return row >= 0 && row < static_cast<int>(row_bounds_) && col >= 0 && col < static_cast<int>(col_bounds_);
}