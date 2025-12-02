#pragma once

#include <string>
#include <fstream>

class SecretEntrance{
private:
    int min_ = 0;
    int max_ = 99;
    int position_ = 50;
    int on_zero_ = 0;
    int at_zero_ = 0;
    std::ifstream fp_;

public:
    SecretEntrance(std::string file_name);
    ~SecretEntrance(){};
    auto CrackCode() -> int;
    auto OnZero() -> void;
    auto AtZero(int turns) -> void;
    auto SetPosition(int turns) -> void;
    auto GetOnZero() {return on_zero_;}
    auto GetAtZero() {return at_zero_;}
};
