#pragma once

#include <fstream>
#include <string>

class GiftShop{
    private:
        std::ifstream fp_;
    public:
        GiftShop(std::string file_name);
        ~GiftShop(){};
        auto ResetFp() -> void;
        auto CountInvalidIDs() -> long long;
        auto IdMirror(std::string id) -> bool;
        auto CountGeneratedRepeatSequences() -> long long;
};
