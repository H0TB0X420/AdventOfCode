#include <string>
#include <fstream>
#include <vector>
#include <utility>

class Cafeteria{
    private:
        std::ifstream fp_;
        std::vector<std::pair<long, long>> ranges_;
        std::vector<long> ingredients_;
    public:
        Cafeteria(std::string file_name);
        ~Cafeteria(){};
        auto ResetFp() -> void;
        auto ReadIngredients() -> void;
        auto GetFreshIngredients() -> int;
        auto MergeRanges() -> void;
        auto GetTotalFreshIngredientRanges() -> long long;
};