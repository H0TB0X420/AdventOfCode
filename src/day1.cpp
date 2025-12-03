#include "day1.h"

#include <sstream>
#include <string>
#include <iostream>

// FIX 1: Initialize position_ to 50 (the dial starts at 50, not 0)
SecretEntrance::SecretEntrance(std::string file_name) : fp_(file_name) {
}

auto SecretEntrance::CrackCode() -> int {
    std::string line;
    int zeros = 0;
    while (std::getline(fp_, line))
    {
        int direction = line[0] == 'R' ? 1 : -1;
        int rotations = std::stoi(line.substr(1, line.length()));
        AtZero(direction * rotations);
        SetPosition(direction * rotations);
        std::cout << "The dial is rotated " << line << " to point at " << position_<< std::endl;
        std::cout<< "TOTAL: "<< on_zero_ + at_zero_ << std::endl;
        std::cout << "==========" << std::endl;
    }
    return on_zero_ + at_zero_;
}

auto SecretEntrance::OnZero() -> void {
    if (position_ == 0) {
        ++on_zero_;
    }
}

auto SecretEntrance::AtZero(int turns) -> void {
    int raw_position = position_ + turns;
    int new_position = ((position_ + turns) % 100 + 100) % 100;
    
    // Count full rotations
    int full_turns = std::abs(turns) / 100;
    at_zero_ += full_turns;
    
    // Check partial crossing (but NOT if we start at 0)
    int partial = turns % 100;
    int partial_raw = position_ + partial;
    
    if (position_ != 0) {  // Only count crossing if we DON'T start at 0
        if (partial_raw > 100) {
            at_zero_++;
        } else if (partial_raw < 0) {
            at_zero_++;
        }
    }
    // Landing on 0 always counts
    if (new_position == 0) {
        on_zero_++;
    }
}
auto SecretEntrance::SetPosition(int turns) -> void {
    position_ = ((position_ + turns) % 100 + 100) % 100;
}