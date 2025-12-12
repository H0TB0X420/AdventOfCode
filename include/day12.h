#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <functional>


class Present {
    public:
        std::vector<std::string> shape_;
        int fill_size_;
        Present(std::vector<std::string> s, int f): shape_(s), fill_size_(f){}
        Present(std::vector<std::string> s): shape_(s){
            fill_size_ = 0;
            for (auto row: shape_){
                for (auto c: row){
                    if (c == '#'){
                        ++fill_size_;
                    }
                }
            }
        }
        bool operator==(const Present& other) const {
            return other.shape_ == shape_;
        }
        auto rotate90(const std::vector<std::string>& grid) -> std::vector<std::string>{
            if (grid.empty()) return {};
            int rows = grid.size();
            int cols = grid[0].size();        
            std::vector<std::string> new_grid(cols, std::string(rows, ' '));        
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    new_grid[c][rows - 1 - r] = grid[r][c];
                }
            }
            return new_grid;
        }
        auto Rotate(int rotations) -> Present { // 0-> no change, 1 -> 90, 2 -> 180, 3 -> 270
            std::vector<std::string> new_shape;
            for (int i = 0; i < rotations; ++i) {
                new_shape = rotate90(shape_);
            }
            return Present(new_shape, fill_size_);
        }
        auto Reflect(char d) -> Present { // 'v' is vertical, 'h' is horizontal
            std::vector<std::string> new_shape = shape_;
            if (d == 'v') {
                std::reverse(new_shape.begin(), new_shape.end());
            }
            
            else if (d == 'h') {
                for (auto& row : new_shape) {
                    std::reverse(row.begin(), row.end());
                }
            }
            
            return Present(new_shape, fill_size_);

        }
        
        ~Present() = default;
};

class Tree {
    public:
        int length_;
        int width_;
        std::vector<std::string> grid_; // starts as grid of all '.' of length_*width_
        std::vector<int> required_presents_; // index represents which shape is needed, value at index represents number of presents needed
        Tree(int l, int w, std::vector<int> p): length_(l), width_(w), required_presents_(p){
            std::string row;
            row.assign(l, '.');
            for (int i = 0; i < w; ++i){
                grid_.push_back(row);
            }
        }
        ~Tree() = default;
        auto Display() const -> void {
            std::cout<<"Required Presents Remaining: ";
            for (auto rp: required_presents_){
                std::cout<< rp << " ";
            }
            std::cout << std::endl << std::string(50, '*') << std::endl;
            for (auto g: grid_){
                std::cout<< g << std::endl;
            }
           std::cout << std::string(50, '*')<< std::endl;
        }
        auto PlaceOnGrid(const Present& present) -> bool; // Take a Present place on grid if possible
};


namespace std {
    template <>
    struct hash<Present> {
        std::size_t operator()(const Present& p) const noexcept {
            std::size_t seed = 0;
            // Helper lambda to combine hash values (Boost-style hash_combine)
            // This distributes bits better than simple XOR to prevent collisions
            auto hash_combine = [&](std::size_t val) {
                seed ^= val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            };
            hash_combine(std::hash<int>{}(p.fill_size_));
            for (const auto& row : p.shape_) {
                hash_combine(std::hash<std::string>{}(row));
            }
            return seed;
        }
    };
}

class ChristmasTreeFarm{
    private:
        std::ifstream fp_;
        std::map<int, std::vector<Present>> presents_; // present id, list of all permutations
        std::vector<Tree> trees_;
    public:
        ChristmasTreeFarm(std::string file_name) : fp_(file_name){
            if (!fp_.is_open()) {return;}

            std::string line;
            int current_shape_id = -1;
            std::vector<std::string> current_shape_grid;

            while (std::getline(fp_, line)) {
    
                if (line.empty()) continue;

                if (line.find('x') != std::string::npos && line.find(':') != std::string::npos) {
                    std::replace(line.begin(), line.end(), ':', ' ');
                    std::replace(line.begin(), line.end(), 'x', ' ');
                    
                    std::stringstream ss(line);
                    int len, wid, count;
                    ss >> len >> wid;
                    
                    std::vector<int> counts;
                    while (ss >> count) {
                        counts.push_back(count);
                    }
                    
                    trees_.emplace_back(Tree(len, wid, counts));
                }
                
                else if (isdigit(line[0]) && line.back() == ':') {
                    if (current_shape_id != -1 && !current_shape_grid.empty()) {
                        presents_[current_shape_id].push_back(Present(current_shape_grid));
                        current_shape_grid.clear();
                        current_shape_id = -1;
                    }
                    line.pop_back(); // Remove ':'
                    current_shape_id = std::stoi(line);
                }
                
                else if (line.find('#') != std::string::npos || line.find('.') != std::string::npos) {
                    current_shape_grid.push_back(line);
                }
            }

            if (current_shape_id != -1 && !current_shape_grid.empty()) {
                presents_[current_shape_id].push_back(Present(current_shape_grid));
            }
            
            fp_.close();
            GetPresentVariations();
        }
        auto ViewPresents() const -> void {
            std::cout << "--- Loaded Presents & Variations ---" << std::endl;

            for (const auto& pair : presents_) {
                int id = pair.first;
                const std::vector<Present>& variations = pair.second;

                std::cout << "\n[Shape ID: " << id << "] has " << variations.size() << " unique variations:" << std::endl;

                for (size_t i = 0; i < variations.size(); ++i) {
                    std::cout << "  Variation " << i + 1 << ":" << std::endl;
                    for (const std::string& row : variations[i].shape_) {
                        std::cout << "    " << row << std::endl;
                    }
                    std::cout << std::endl;
                }
                std::cout << "------------------------------------" << std::endl;
            }
        }
        auto ViewTrees() const -> void {
            std::cout << "--- Trees ---" << std::endl;
            
            for (const auto& tree : trees_) {
                tree.Display();
                std::cout<< std::endl;
            }
        }
        auto GetPresentVariations() -> void {
            for (auto [id, shapes]: presents_){
                std::unordered_set<Present> unique_variations;                
                auto current = shapes.at(0);

                for (auto reflect : std::vector<char>{'v', 'h'}) {
                    for (int rot = 0; rot < 4; ++rot) {
                        unique_variations.insert(Present(current.shape_, current.fill_size_));
                        current = current.Rotate(1);
                    }
                    current = current.Reflect(reflect);
                }
                for (const auto& p : unique_variations) {
                    presents_[id].push_back(p);
                }
            }
    
        }
        ~ChristmasTreeFarm() = default;
        auto PlacePresents() -> long long;
        auto Solve(Tree& tree, const std::vector<int>& present_ids, size_t index) -> bool;
        auto ShouldPrune(const Tree& tree, const std::vector<int>& present_ids, size_t index) -> bool;

};
