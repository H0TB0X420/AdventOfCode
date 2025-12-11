#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

class Reactor {
    private: 
        std::ifstream fp_;
    public:
        std::unordered_map<std::string, std::vector<std::string>> graph_;
        std::unordered_map<std::string, long long> cache_;
        Reactor(std::string file_name): fp_(file_name){
            std::string line;
            while (std::getline(fp_, line)){
                auto key = line.substr(0, line.find_first_of(':'));
                line = line.substr(line.find_first_of(':') + 1, line.length());
                std::stringstream ss(line);
                std::string output;
                std::vector<std::string> outputs;
                while (ss >> output){
                    outputs.push_back(output);
                }
                graph_[key] = outputs;
            }
            // ViewGraphs();
        }
        ~Reactor(){}
        auto ViewGraphs() -> void {
            for (auto& [key, value]: graph_){
                std::cout<<"Device: " << key << std::endl;
                std::cout<< "Outputs: ";
                for (auto v: value){
                    std::cout<< v << ' ';
                }
                std::cout<< '\n' <<"==========" << std::endl;
            }
        }
        auto FindAllPaths(std::string start, std::string stop) -> int;
        auto FindAllDacFftPaths(std::string node, bool fft, bool dac) -> long long;
};