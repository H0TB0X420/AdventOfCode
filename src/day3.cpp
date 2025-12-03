#include "day3.h"
#include <iostream>
#include <utility>
#include <vector>

Lobby::Lobby(std::string file_name): fp_(file_name){
}

auto Lobby::ResetFp() -> void {
    fp_.clear();
    fp_.seekg(0, std::ios::beg);
}

auto Lobby::MaximumJoltage2() -> int {
    std::string bank;
    
    int total = 0;
    while(std::getline(fp_, bank)){
        std::string result;
        char first = '0';
        int first_index = 0;
        for (int i = 0; i < bank.length() - 1; ++i){
            if (bank[i] > first){
                first_index = i;
                first = bank[i];
            }
        }
        result += first;
        char second = '0';
        for (int j = first_index + 1; j < bank.length(); ++j){
            if (bank[j] > second){
                second = bank[j];
            }
        }
        result += second;
        
        total += std::stoi(result);
    }
    return total;
}

auto Lobby::MaximumJoltage12() -> long long {
    std::string bank,line;
    
    long long total = 0;
    
    while(std::getline(fp_, line)){
        bank = line;
        std::string result = "";
        int start_index = 0; //This index is relative to the substr we are searching
        while (result.length() < 12){
            bank = bank.substr(start_index, bank.length());
            // std::cout << bank << std::endl;
            auto index_to_add = FindFirstIndex(bank, '9', 12 - result.length());
            if (index_to_add == -1){
                std::cout << "We have a problem" << std::endl;
                break;
            }
            result += bank[index_to_add];
            start_index = index_to_add + 1;
        }
        std::cout << "Result: " << result << std::endl;
        total += std::stol(result);
    }
    return total;
}

auto Lobby::FindFirstIndex(const std::string& bank, char digit, int remaining_digits) -> int {
    if (digit == '0'){return -1;} //Should never occur
    auto index = bank.find_first_of(digit, 0);
    // std::cout<< "Bank find first of " << digit << " located at " << index << std::endl;
    if (index == std::string::npos || index > bank.length() - remaining_digits){
        return FindFirstIndex(bank, digit - 1, remaining_digits);
    } 
    // std::cout<< "Bank find first of " << digit << " located at " << index << std::endl;
    return index;
}
