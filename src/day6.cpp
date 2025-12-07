#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <regex>
#include "day6.h"

auto TrashCompactor::ReadFile() -> void {
    std::string line;
    std::vector<long> numbers;
    std::string ops = "+*";
    while (std::getline(fp_, line)){
        std::string token;
        std::stringstream ss(line);
        while (ss >> token){
            if (std::all_of(token.begin(), token.end(), ::isdigit)){
                numbers.push_back(std::stol(token));
            } else if (ops.find(token) != std::string::npos){
                operators_.push_back(token);
            }
        }
    }
    data_.resize(operators_.size());
    for (size_t i = 0; i < numbers.size(); ++i){
        size_t data_index = i % operators_.size();
        data_.at(data_index).push_back(numbers[i]);
    }
}

auto TrashCompactor::CephalopodMath() -> long {
    ReadFile();
    long acc;
    std::vector<long> results;
    
    for (size_t i = 0; i < operators_.size(); ++i){
        // std::cout<<"Operator: " << operators_[i] << '\t';
        // for (auto d: data_[i]){
        //     std::cout<< d << '\t';
        // }

        if (operators_[i] == "+"){
            acc = std::accumulate(data_[i].begin(), data_[i].end(), 0L);
            
        }
        else if (operators_[i] == "*"){
            acc = std::accumulate(data_[i].begin(), data_[i].end(), 1L,
                [](long accumulator, long current_element) {
                    return accumulator * current_element;
                }
            );
        }
        results.push_back(acc);
    }
    return std::accumulate(results.begin(), results.end(), 0L);
}

auto TrashCompactor::BigCephalopodMath() -> long {
    std::string line;
    while (std::getline(fp_, line)){
        str_data_.push_back(line);
    }
    // --- STEP 1: Normalize Geometry (Right Padding) ---
    // Ensure the grid is a perfect rectangle so we don't hit index errors.
    size_t max_len = 0;
    for (const auto& r : str_data_) {
        max_len = std::max(max_len, r.size());
    }

    for (auto& r : str_data_) {
        if (r.size() < max_len) {
            r.resize(max_len, ' '); // Pad right with spaces
        }
    }

    // --- STEP 2: The Cephalopod Scan (Right-to-Left) ---
    long grand_total = 0;
    std::vector<long> current_problem_numbers;
    
    // We work backwards through the operators vector as we move Right-to-Left
    int op_index = operators_.size() - 1; 

    // Iterate Columns from Width-1 down to 0
    for (int col = max_len - 1; col >= 0; --col) {
        
        // A. Construct the vertical string for this column
        std::string vertical_str;
        for (const auto& row : str_data_) {
            vertical_str += row[col];
        }

        // B. Clean up the vertical string (remove spaces)
        // In this math, a vertical column is just digits (like "431") or pure space.
        vertical_str.erase(std::remove_if(vertical_str.begin(), vertical_str.end(), ::isspace), vertical_str.end());

        // C. Logic: Is this Data or Separator?
        if (!vertical_str.empty()) {
            // It's a number (or part of a block of numbers)
            current_problem_numbers.push_back(std::stol(vertical_str));
        } 
        else {
            // It's a whitespace column. This indicates the END of the current problem block.
            // If we have numbers buffered, calculate their result now.
            if (!current_problem_numbers.empty()) {
                
                // Get the operator for this specific block
                std::string op = (op_index >= 0) ? operators_[op_index] : "+"; // Default safety
                
                long block_result = current_problem_numbers[0];
                for (size_t i = 1; i < current_problem_numbers.size(); ++i) {
                    if (op == "+") block_result += current_problem_numbers[i];
                    else if (op == "*") block_result *= current_problem_numbers[i];
                }

                grand_total += block_result;
                
                // Reset for the next problem (to the left)
                current_problem_numbers.clear();
                op_index--;
            }
        }
    }

    // --- STEP 3: Handle the Final (Leftmost) Block ---
    // The loop finishes at col -1, so the last block never hit a "whitespace separator"
    if (!current_problem_numbers.empty()) {
        std::string op = (op_index >= 0) ? operators_[op_index] : "+";
        
        long block_result = current_problem_numbers[0];
        for (size_t i = 1; i < current_problem_numbers.size(); ++i) {
            if (op == "+") block_result += current_problem_numbers[i];
            else if (op == "*") block_result *= current_problem_numbers[i];
        }
        grand_total += block_result;
    }

    return grand_total;
}