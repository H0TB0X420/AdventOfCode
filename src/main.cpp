#include <iostream>

#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"

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

    auto printing_department = PrintingDepartment(argv[1]);
    auto result = printing_department.GetAccessibleRolls();
    std::cout<< "Sample Expected: " << 43 << std::endl;
    std::cout<< "Sample Actual: " << result << std::endl;
    std::cout<< "Diff: " << std::abs(43-result) << std::endl;
    

    auto cafeteria = Cafeteria(argv[1]);
    auto result1 = cafeteria.GetFreshIngredients();
    std::cout<< "P1 Expected: " << 3 <<std::endl;
    std::cout<<"P1 Actual: "<<  result1 << std::endl;

    long long result2 = cafeteria.GetTotalFreshIngredientRanges();
    std::cout<< "P2 Expected: " << 14 <<std::endl;
    std::cout<<"P2 Actual: "<<  result2 << std::endl; // 352556672963137 | 352556672963116
    */

    auto trash_compactor = TrashCompactor(argv[1]);
    long result = trash_compactor.CephalopodMath();
    std::cout<<"Expected: " << 4277556 << std::endl;
    std::cout<<"Actual: " << result << std::endl << std::endl;

    trash_compactor.ResetFp();
    result = trash_compactor.BigCephalopodMath();
    std::cout<<"Expected: " << 3263827 << std::endl;
    std::cout<<"Actual: " << result << std::endl; 
    // 5873191732773 - Too Low
    // 19515575917 - Way Too Low
    // 9233969706360
}