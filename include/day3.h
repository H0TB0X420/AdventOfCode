#include <string>
#include <fstream>

class Lobby {
    private:
        std::ifstream fp_;
    public:
        Lobby(std::string file_name);
        ~Lobby(){};
        auto ResetFp() -> void;
        auto MaximumJoltage2() -> int;
        auto MaximumJoltage12() -> long long;
        auto FindFirstIndex(const std::string& bank, char digit, int remaining_digits) -> int;
};