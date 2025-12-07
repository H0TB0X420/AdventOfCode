#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Laboratories{
    private:
        std::ifstream fp_;
        std::unordered_set<size_t> beam_positions_;
        std::unordered_map<size_t, long> beam_timelines_;
        
    public:
        Laboratories(std::string file_name) : fp_(file_name){}
        ~Laboratories(){}
        auto ResetFp() -> void {
            fp_.clear();
            fp_.seekg(0, std::ios::beg);
        }
       
        auto TachyonManifolds() -> int;
        auto QuantumTachyonManifolds() -> long;
};