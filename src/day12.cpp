#include "day12.h"
#include <numeric>
#include <algorithm>

auto ChristmasTreeFarm::ShouldPrune(const Tree& tree, const std::vector<int>& present_ids, size_t index) -> bool {
    
    int min_present_size = 1000000;
    long long required_area = 0;
    
    for (size_t i = index; i < present_ids.size(); ++i) {
        int id = present_ids[i];
        if (presents_.find(id) != presents_.end() && !presents_.at(id).empty()) {
            int size = presents_.at(id)[0].fill_size_;
            if (size < min_present_size) min_present_size = size;
            required_area += size;
        }
    }
    
    if (required_area == 0) return false;

    int rows = tree.grid_.size();
    int cols = tree.grid_[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    long long useful_empty_space = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (tree.grid_[r][c] == '.' && !visited[r][c]) {
                
                int island_size = 0;
                std::vector<std::pair<int, int>> stack;
                stack.push_back({r, c});
                visited[r][c] = true;

                while (!stack.empty()) {
                    auto [curr_r, curr_c] = stack.back();
                    stack.pop_back();
                    island_size++;

                    int dr[] = {1, -1, 0, 0};
                    int dc[] = {0, 0, 1, -1};

                    for (int i = 0; i < 4; ++i) {
                        int nr = curr_r + dr[i];
                        int nc = curr_c + dc[i];

                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                            tree.grid_[nr][nc] == '.' && !visited[nr][nc]) {
                            visited[nr][nc] = true;
                            stack.push_back({nr, nc});
                        }
                    }
                }
                if (island_size >= min_present_size) {
                    useful_empty_space += island_size;
                }
            }
        }
    }
    return useful_empty_space < required_area;
}

auto Tree::PlaceOnGrid(const Present& present) -> bool {
    int p_height = present.shape_.size();
    int p_width = present.shape_[0].size();
    int grid_height = grid_.size();
    int grid_width = grid_[0].size();
    for (int r = 0; r <= grid_height - p_height; ++r) {
        for (int c = 0; c <= grid_width - p_width; ++c) {            
            bool collision = false;
            for (int pr = 0; pr < p_height; ++pr) {
                for (int pc = 0; pc < p_width; ++pc) {
                    if (present.shape_[pr][pc] == '#' && grid_[r + pr][c + pc] == '#') {
                        collision = true;
                        break;
                    }
                }
                if (collision) break;
            }
            if (!collision) {
                for (int pr = 0; pr < p_height; ++pr) {
                    for (int pc = 0; pc < p_width; ++pc) {
                        if (present.shape_[pr][pc] == '#') {
                            grid_[r + pr][c + pc] = '#';
                        }
                    }
                }
                return true; 
            }
        }
    }
    return false; 
}

auto ChristmasTreeFarm::PlacePresents() -> long long{
    int solved_count = 0;

    for (auto& tree : trees_) {
        std::vector<int> presents_to_fit;
        for (size_t id = 0; id < tree.required_presents_.size(); ++id) {
            int count = tree.required_presents_[id];
            for (int k = 0; k < count; ++k) {
                presents_to_fit.push_back(id);
            }
        }
        std::sort(presents_to_fit.begin(), presents_to_fit.end(), 
            [&](int a, int b) {
                if (presents_[a].empty()) return false;
                if (presents_[b].empty()) return true;
                return presents_[a][0].fill_size_ > presents_[b][0].fill_size_;
            }
        );
        // Ensure grid is initialized with dots
        tree.grid_ = std::vector<std::string>(tree.length_, std::string(tree.width_, '.'));
        
        if (Solve(tree, presents_to_fit, 0)) {
            solved_count++;
        }
    }

    return solved_count;
}

auto ChristmasTreeFarm::Solve(Tree& tree, const std::vector<int>& present_ids, size_t index) -> bool{
    if (index >= present_ids.size()) {
        return true;
    }

    if (ShouldPrune(tree, present_ids, index)) {
        return false;
    }

    int current_id = present_ids[index];
    const auto& variations = presents_[current_id];
    for (const auto& present : variations) {
        std::vector<std::string> backup_grid = tree.grid_;
        if (tree.PlaceOnGrid(present)) {
            if (Solve(tree, present_ids, index + 1)) {
                return true;
            }
            tree.grid_ = backup_grid;
        }
    }
    return false;
}