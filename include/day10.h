#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Manual {
        
    public:
        std::string current_indicator_;
        std::vector<int> current_joltages_;
        std::string start_indicator_;
        std::vector<std::vector<int>> buttons_;
        std::vector<int> required_joltages_;
        Manual(std::string in_str, std::string b_str, std::string j_str): start_indicator_(in_str){
            current_indicator_.assign(start_indicator_.size(), '.');
            current_joltages_.assign(start_indicator_.size(), 0);
            std::stringstream ss(b_str);
            std::string value;
            
            char c;
            while (ss >> c) {         
                if (c == '(') {       
                    std::vector<int> row;
                    int value;
                    while (ss >> value) {
                        row.push_back(value);
                        ss >> c; 
                        if (c == ')') break;
                    }
                    buttons_.push_back(row);
                }
            }

            ss.clear();
            ss.str(j_str);

            while (std::getline(ss, value, ',')) {
                required_joltages_.push_back(std::stoi(value));
            }
            // ViewManual();
        }
        ~Manual(){}
        auto ViewManual() -> void {
            std::cout << "\n================ DEVICE MANUAL ================\n";
            std::cout << "Current indicator: " << current_indicator_ << "\n";
            std::cout << "Start indicator: " << (start_indicator_.empty() ? "None" : start_indicator_) << "\n";            
            std::cout << "Buttons Configuration:\n";
            if (buttons_.empty()) {
                std::cout << "    (No button groups defined)\n";
            } else {
                for (size_t i = 0; i < buttons_.size(); ++i) {
                    std::cout << "    Button " << std::setw(2) << i << ": ( ";
                    for (size_t j = 0; j < buttons_[i].size(); ++j) {
                        std::cout << buttons_[i][j] << (j < buttons_[i].size() - 1 ? ", " : "");
                    }
                    std::cout << " )\n";
                }
            }
            std::cout << "Joltages:   ";
            if (required_joltages_.empty()) {
                std::cout << "None";
            } else {
                std::cout << "{ ";
                for (size_t i = 0; i < required_joltages_.size(); ++i) {
                    std::cout << required_joltages_[i] << (i < required_joltages_.size() - 1 ? ", " : "");
                }
                std::cout << " }";
            }
            std::cout << "\n";
            std::cout << "Current joltages: ";
            std::cout << "{ ";
                for (size_t i = 0; i < current_joltages_.size(); ++i) {
                    std::cout << current_joltages_[i] << (i < current_joltages_.size() - 1 ? ", " : "");
                }
            std::cout << " }";
            std::cout << "===============================================\n\n";
        }

};

class Factory {
    private:
        std::ifstream fp_;
        std::vector<Manual> manuals_;
    public:
        Factory(std::string file_name): fp_(file_name){
            std::string line;
            while(std::getline(fp_, line)){
                std::string in_str, b_str, j_str;
                size_t first = line.find_first_of('[');
                size_t last = line.find_last_of(']');
                in_str = line.substr(first + 1, last - first  - 1);
                first = line.find_first_of('(');
                last = line.find_last_of(')');
                b_str = line.substr(first, last - first + 1);
                first = line.find_first_of('{');
                last = line.find_last_of('}');
                j_str = line.substr(first + 1, last - first - 1);
                manuals_.emplace_back(Manual(in_str, b_str, j_str));
            }
        }
        ~Factory(){}
        auto ResetFp() -> void {
            fp_.clear();
            fp_.seekg(0, std::ios::beg);
        }
        auto ResetIndicators() -> int;
        auto SetJoltages() -> int;
        auto SetJoltagesFast() -> long long;
};