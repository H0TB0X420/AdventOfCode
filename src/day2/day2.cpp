#include "day2.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm> 

GiftShop::GiftShop(std::string file_name): fp_(file_name){    
}
auto GiftShop::ResetFp() -> void {
    fp_.seekg(0, std::ios::beg);
}
auto GiftShop::CountInvalidIDs() -> long long{
    std::string line;
    long long total = 0;
    std::getline(fp_, line); // all contents of file are on single line but comma separated
    std::stringstream ss(line);
    std::string id_range;
    while(std::getline(ss, id_range, ',')){
        std::string first = id_range.substr(0, id_range.find("-"));
        std::string last = id_range.substr(id_range.find("-")+1, id_range.length());
        for (long i = std::stol(first); i < std::stol(last) + 1; ++i){
            std::string id = std::to_string(i);
            if (IdMirror(id)){ 
                total += i;
            }
        }
    }
    
    return total;
}
auto GiftShop::IdMirror(std::string id) -> bool {
    int len = id.length();
    if (len % 2){return false;}// needs to be even length to be mirror
    return id.substr(0, len / 2) == id.substr(len / 2, len);
}

auto GiftShop::CountGeneratedRepeatSequences() -> long long {
    std::string line;
    long long total = 0;
    std::getline(fp_, line); // all contents of file are on single line but comma separated
    std::stringstream ss(line);
    std::string id_range;
    std::vector<std::string> ids(2);
    while(std::getline(ss, id_range, ',')){
        std::string first = id_range.substr(0, id_range.find("-"));
        std::string last = id_range.substr(id_range.find("-")+1, id_range.length());
        ids.at(0) = first;
        ids.at(1) = last;
        std::set<long> visited;
        /*for (const auto& id: ids){
            for (int i = id.length() / 2; i > 0; --i){
                if (id.length() % i == 0){// only factors fit cleanly
                    std::string pattern = id.substr(0, i);
                    std::string result_str = "";
                    while (result_str.length() <= id.length()){
                        result_str.append(pattern);
                        long result_id = std::stol(result_str);
                        if (visited.find(result_id) == visited.end() && result_id >= std::stol(first) && result_id <= std::stol(last)){
                            visited.insert(result_id);
                            total += result_id;
                        }
                    }
                    
                }
            }
        }*/
        for (int digit_length = first.length(); digit_length <= last.length(); ++digit_length){
            for (int i = 1; i <= digit_length / 2 ; ++i){
                if (digit_length % i == 0){
                    for(long j = pow(10, i-1); j < pow(10, i);++j){
                        std::string j_str = std::to_string(j);
                        std::string result_str = "";
                        while (result_str.length() < digit_length){
                            result_str.append(j_str);
                        }
                        long result_id = std::stol(result_str);
                        if (visited.find(result_id) == visited.end() && result_id >= std::stol(first) && result_id <= std::stol(last)){
                            visited.insert(result_id);
                            total += result_id;
                        }
                        
                    }
                }
            }
        }
    }
    
    return total;
}
