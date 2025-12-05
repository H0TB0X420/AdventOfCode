#include "day5.h"
#include <utility>
#include <iostream>

Cafeteria::Cafeteria(std::string file_name): fp_(file_name){

}

auto Cafeteria::ResetFp() -> void{
    fp_.clear();
    fp_.seekg(0, std::ios::beg);
}
auto Cafeteria::ReadIngredients() -> void {
    std::string range_str = "overwritten";
    while (std::getline(fp_, range_str) && range_str != ""){
        size_t split_index = range_str.find('-');
        std::string first_str = range_str.substr(0, split_index);
        std::string second_str = range_str.substr(split_index + 1, range_str.length());
        long first = std::stol(first_str);
        long second = std::stol(second_str);
        if (second < first) {
            std::swap(first, second);
        }
        ranges_.push_back(std::make_pair(first, second));
    }
    std::sort(ranges_.begin(), ranges_.end(), [](auto &left, auto &right) { return left.second < right.second; });
    std::sort(ranges_.begin(), ranges_.end());
    std::cout<<"length before merge: " << ranges_.size() << std::endl;
    MergeRanges();
    std::cout<<"length after merge: " << ranges_.size() << std::endl;
    for (auto p: ranges_){
        std::cout<< p.first << " - " << p.second << std::endl;
    }
    std::string ingredients_str;
    while (std::getline(fp_, ingredients_str)){
        ingredients_.push_back(std::stol(ingredients_str));
    }
    // for (auto elem: ingredients_){
    //     std::cout << elem << std::endl;
    // }
}
auto Cafeteria::GetFreshIngredients() -> int{ //p1
    int fresh = 0;
    ReadIngredients();
    for(const auto& ingredient: ingredients_){
        for (const auto& [start, end]: ranges_){
            if (start <= ingredient && ingredient <= end){
                ++fresh;
            }
        }
    }
    return fresh;
}

auto Cafeteria::GetTotalFreshIngredientRanges() -> long long{ //p2
    long long fresh = 0;
    
    for (const auto& [start, end]: ranges_){
        fresh += (end - start + 1);
    }
    
    return fresh;
}

auto Cafeteria::MergeRanges() -> void {
    std::vector<std::pair<long, long>> merged;
    merged.push_back(ranges_[0]);

    for (size_t i = 1; i < ranges_.size(); ++i){
        auto& last_merged = merged.back();
        auto current = ranges_.at(i);
        if (current.first <= last_merged.second || current.first == last_merged.second + 1){
            last_merged.second = std::max(last_merged.second, current.second);
        } else {
            merged.push_back(current);
        }
    }
    ranges_ = merged;
}