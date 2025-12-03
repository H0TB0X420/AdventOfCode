#include <iostream>

#include "day1.h"
#include "day2.h"
#include "day3.h"

int main(int argc, char* argv[]) {
    /*
    auto secret_entrance = SecretEntrance(argv[1]);
    std::cout << "Cracked Code: "<< secret_entrance.CrackCode() << std::endl;
    // std::cout << "On Zero: " << secret_entrance.GetOnZero() << std::endl;
    // std::cout << "At Zero: " << secret_entrance.GetAtZero() << std::endl;
    // all.txt -> 1 1 2 2 3 4 4 5 6
    
//    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
//    std::cout << "Size of long: " << sizeof(long) << " bytes" << std::endl;
    auto gift_shop = GiftShop(argv[1]);
    long long result = gift_shop.CountInvalidIDs();
    std::cout<< "-----Part 1-----"<< std::endl;
    std::cout<< "Sum of invalid ids: " <<  result << std::endl;
    std::cout << "Expected: " << 1227775554 << std::endl;
    std::cout <<"Off by: " << std::abs(result - 1227775554) << std::endl;
    gift_shop.ResetFp();
    std::cout<< "-----Part 2-----"<< std::endl;
    result = gift_shop.CountGeneratedRepeatSequences();
    std::cout<< "Sum of invalid ids: " <<  result << std::endl;
    std::cout << "Expected: " << 4174379265 << std::endl;
    std::cout <<"Off by: " << std::abs(result - 4174379265) << std::endl;
    */
    auto lobby = Lobby(argv[1]);
    long result1 = lobby.MaximumJoltage2();
    std::cout<<"Expected: " << 357 << std::endl;
    std::cout<<"Actual: " << result1 << std::endl;
    std::cout<<"Difference: "<< std::abs(357-result1) << std::endl;
    std::cout << std::endl;
    lobby.ResetFp();
    long long result2 = lobby.MaximumJoltage12();
    std::cout<<"Expected: " << 3121910778619 << std::endl;
    std::cout<<"Actual: " << result2 << std::endl;
    std::cout<<"Difference: "<< std::abs(3121910778619-result2) << std::endl;
    //987654321111 -- 987654321111
    //811111111119 -- 811111111119
    //434234234278 -- 434234234278
    //888911112111 -- 888911112111
}