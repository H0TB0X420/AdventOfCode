#include <string>
#include <fstream>
#include <vector>
#include <ranges>

class TrashCompactor{
    private:
        std::ifstream fp_;
        std::vector<std::vector<long>> data_;
        std::vector<std::string> operators_;
        std::vector<std::string> str_data_;
    public:
        TrashCompactor(std::string file_name) : fp_(file_name){}
        ~TrashCompactor(){}
        auto ResetFp() -> void {
            fp_.clear();
            fp_.seekg(0, std::ios::beg);
        }
        auto ReadFile() -> void;
        auto CephalopodMath() -> long;
        auto BigCephalopodMath() -> long;
};