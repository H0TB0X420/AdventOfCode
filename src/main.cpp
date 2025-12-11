#include <iostream>

#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"
#include "day8.h"
#include "day9.h"
#include "day10.h"
#include "day11.h"


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
    

    auto trash_compactor = TrashCompactor(argv[1]);
    long result = trash_compactor.CephalopodMath();
    std::cout<<"Expected: " << 4277556 << std::endl;
    std::cout<<"Actual: " << result << std::endl << std::endl;

    trash_compactor.ResetFp();
    result = trash_compactor.BigCephalopodMath();
    std::cout<<"Expected: " << 3263827 << std::endl;
    std::cout<<"Actual: " << result << std::endl; 
    
    auto lab = Laboratories(argv[1]);
    long result = lab.TachyonManifolds();
    std::cout<< "Expected: " << 21 << std::endl;
    std::cout << "Actual: " << result << std::endl;
    lab.ResetFp();
    result = lab.QuantumTachyonManifolds();
    std::cout<< "Expected: " << 40 << std::endl;
    std::cout << "Actual: " << result << std::endl;
    
    auto playgroundSmall = Playground("./inputs/day8/small.txt");
    playgroundSmall.ReadFile();
    long long result = playgroundSmall.ConnectJunctionBoxes(10);
    std::cout<< "Expected: " << 25272 << std::endl; // p1: 40
    std::cout<<"Actual: " << result << std::endl;

    auto playgroundTest = Playground("./inputs/day8/test.txt");
    playgroundTest.ReadFile();
    long long resultTest = playgroundTest.ConnectJunctionBoxes(1000);
    std::cout<<"Result: " << resultTest << std::endl;
    
    auto movie_theater = MovieTheater("./inputs/day9/small.txt");
    auto result = movie_theater.MaximumRectangle();
    std::cout << "Expected: " << 24 << std::endl; // P1 -> 50, P2 -> 24
    std::cout << "Actual: " << result << std::endl;

    auto movie_theater_test = MovieTheater("./inputs/day9/test.txt");
    result = movie_theater_test.MaximumRectangle();
    std::cout << "Result: " << result << std::endl; //P2 too high: 4619863120

    Factory factory("./inputs/day10/small.txt");
    auto result = factory.ResetIndicators();
    std::cout<< "Expected: " << 7 << std::endl;
    std::cout<< "Actual: " << result << std::endl;


    Factory testfactory("./inputs/day10/test.txt");
    result = testfactory.ResetIndicators();
    std::cout<< "Result: " << result << std::endl;

    result = factory.SetJoltages();
    std::cout<< "Expected: " << 33 << std::endl;
    std::cout<< "Actual: " << result << std::endl;

    result = testfactory.SetJoltagesFast();
    std::cout<< "Result: " << result << std::endl;
    */
    auto reactor = Reactor("./inputs/day11/small.txt");
    auto result = reactor.FindAllPaths("you", "out");
    std::cout << "Expected: " << 5 << std::endl;
    std::cout << "Actual: " << result << std::endl;

    auto testreactor = Reactor("./inputs/day11/test.txt");
    result = testreactor.FindAllPaths("you", "out");
    std::cout << "Result: " << result << std::endl << std::endl;

    
    auto dacfft_reactor = Reactor("./inputs/day11/dacfft.txt");
    result = dacfft_reactor.FindAllDacFftPaths("svr", false, false);
    std::cout << "Expected: " << 2 << std::endl;
    std::cout << "Actual: " << result << std::endl;
    
    long long test = testreactor.FindAllDacFftPaths("svr", false, false);
    // testreactor.ViewGraphs();
    std::cout << "Result: " << test << std::endl; // P2 too low -> 91708416
    // Not right: 759274471139838
    // Too high: 154108069022874777, 

}