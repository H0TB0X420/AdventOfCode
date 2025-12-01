#include <iostream>

#include "day1/day1.h"

int main(int argc, char* argv[]) {
    auto secret_entrance = SecretEntrance(argv[1]);
    std::cout << "Cracked Code: "<< secret_entrance.CrackCode() << std::endl;
    // std::cout << "On Zero: " << secret_entrance.GetOnZero() << std::endl;
    // std::cout << "At Zero: " << secret_entrance.GetAtZero() << std::endl;
    
    // all.txt -> 1 1 2 2 3 4 4 5 6
}