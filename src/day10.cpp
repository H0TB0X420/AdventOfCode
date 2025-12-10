#include "day10.h"
#include <tuple>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <functional>
#include <climits>
#include <cmath>
#include <algorithm>


auto Factory::ResetIndicators() -> int {
    int result = 0;
    for (const auto& manual: manuals_){
        // auto manual = manuals_.at(0);
        int minimum_steps = 10000;
        std::unordered_set<std::string> visited;
        std::tuple<int, std::string> inital = {0, manual.current_indicator_};
        std::queue<std::tuple<int, std::string>> q;
        q.push(inital); // q = [(step count, state)...]
        
        while (!q.empty()){
            auto [steps, state] = q.front();
            // std::cout<< "Steps: " << steps << ',' << "State: " << state << std::endl;
            q.pop();
            for(const auto& button: manual.buttons_){
                std::string new_state = state;
                for (size_t i = 0; i < button.size(); ++i){
                    new_state[button.at(i)] = new_state[button.at(i)] == '.' ? '#' : '.';
                }
                if (new_state == manual.start_indicator_){
                    minimum_steps = std::min(minimum_steps, steps + 1);
                } else if (!visited.count(new_state)) {
                    visited.insert(new_state);
                    q.push(std::make_tuple(steps + 1, new_state));
                }
            }
        }
        result += minimum_steps;
    }
    return result;
}

auto Factory::SetJoltages() -> int { // works but too slow.
    int result = 0;
    for (const auto& manual: manuals_){
        // auto manual = manuals_.at(0);
        int minimum_steps = 10000;
        std::unordered_set<std::string> visited;
        std::tuple<int, std::vector<int>> inital = {0, manual.current_joltages_};
        std::queue<std::tuple<int, std::vector<int>>> q;
        q.push(inital); // q = [(step count, state)...]
        
        while (!q.empty()){
            auto [steps, state] = q.front();
            std::stringstream s;
            std::copy(state.begin(), state.end(), std::ostream_iterator<int>(s, ", "));
            // std::cout<< "Steps: " << steps << ',' << "State: " << s.str() << std::endl;
            q.pop();
            for(const auto& button: manual.buttons_){
                std::vector<int> new_state = state;
                for (size_t i = 0; i < button.size(); ++i){
                    new_state[button.at(i)]++;
                }
                std::stringstream ss;
                std::copy(new_state.begin(), new_state.end(), std::ostream_iterator<int>(ss, ", "));
                std::string new_state_str = ss.str();
                if (new_state == manual.required_joltages_){
                    minimum_steps = std::min(minimum_steps, steps + 1);
                } else if (!visited.count(new_state_str)){ // check if each joltage is over the required for that slot, if not continue
                    bool over_jolt = false;
                    for (size_t i = 0; i < manual.required_joltages_.size(); ++i){
                        if (new_state[i] > manual.required_joltages_[i]){
                            over_jolt = true;
                            break;
                        }
                    }
                    if (!over_jolt){
                        visited.insert(new_state_str);
                        q.push(std::make_tuple(steps + 1, new_state));
                    }
                }
            }
        }
        result += minimum_steps;
    }
    return result;
}

auto Factory::SetJoltagesFast() -> long long {
    long long result = 0;
    
    for (const auto& manual : manuals_) {
        int n = manual.required_joltages_.size();  // num counters (equations)
        int m = manual.buttons_.size();             // num buttons (variables)
        
        // Build augmented matrix [A | b]
        // A[i][j] = 1 if button j affects counter i
        std::vector<std::vector<double>> aug(n, std::vector<double>(m + 1, 0.0));
        
        for (int j = 0; j < m; ++j) {
            for (int idx : manual.buttons_[j]) {
                aug[idx][j] = 1.0;
            }
        }
        for (int i = 0; i < n; ++i) {
            aug[i][m] = manual.required_joltages_[i];
        }
        
        // Gaussian elimination to Reduced Row Echelon Form (RREF)
        std::vector<int> pivot_col(n, -1);
        int rank = 0;
        
        for (int col = 0; col < m && rank < n; ++col) {
            // Find pivot row
            int pivot_row = -1;
            for (int row = rank; row < n; ++row) {
                if (std::abs(aug[row][col]) > 1e-9) {
                    pivot_row = row;
                    break;
                }
            }
            if (pivot_row == -1) continue;
            
            std::swap(aug[rank], aug[pivot_row]);
            pivot_col[rank] = col;
            
            // Scale pivot row
            double scale = aug[rank][col];
            for (int j = 0; j <= m; ++j) {
                aug[rank][j] /= scale;
            }
            
            // Eliminate in all other rows
            for (int row = 0; row < n; ++row) {
                if (row != rank && std::abs(aug[row][col]) > 1e-9) {
                    double factor = aug[row][col];
                    for (int j = 0; j <= m; ++j) {
                        aug[row][j] -= factor * aug[rank][j];
                    }
                }
            }
            ++rank;
        }
        
        // Identify free variables (columns without pivots)
        std::vector<bool> is_pivot_col(m, false);
        for (int r = 0; r < rank; ++r) {
            if (pivot_col[r] >= 0) is_pivot_col[pivot_col[r]] = true;
        }
        
        std::vector<int> free_vars;
        for (int j = 0; j < m; ++j) {
            if (!is_pivot_col[j]) free_vars.push_back(j);
        }
        
        // Bound for free variable search
        long long max_target = *std::max_element(
            manual.required_joltages_.begin(), 
            manual.required_joltages_.end()
        );
        
        long long min_presses = LLONG_MAX;
        
        // Recursive search over free variables
        std::function<void(int, std::vector<long long>&)> search = 
            [&](int idx, std::vector<long long>& free_vals) {
            
            if (idx == static_cast<int>(free_vars.size())) {
                std::vector<long long> x(m, 0);
                
                // Set free variables
                for (size_t i = 0; i < free_vars.size(); ++i) {
                    x[free_vars[i]] = free_vals[i];
                }
                
                // Back-substitute to find pivot variables
                bool valid = true;
                for (int r = rank - 1; r >= 0 && valid; --r) {
                    int pcol = pivot_col[r];
                    double val = aug[r][m];
                    for (int j = 0; j < m; ++j) {
                        if (j != pcol) {
                            val -= aug[r][j] * x[j];
                        }
                    }
                    long long ival = std::llround(val);
                    if (ival < 0 || std::abs(val - ival) > 1e-6) {
                        valid = false;
                    } else {
                        x[pcol] = ival;
                    }
                }
                
                if (valid) {
                    long long total = 0;
                    for (int j = 0; j < m; ++j) total += x[j];
                    min_presses = std::min(min_presses, total);
                }
                return;
            }
            
            // Pruning based on current partial sum
            long long current_sum = 0;
            for (int i = 0; i < idx; ++i) current_sum += free_vals[i];
            
            for (long long v = 0; v <= max_target; ++v) {
                if (current_sum + v >= min_presses) break;
                free_vals[idx] = v;
                search(idx + 1, free_vals);
            }
        };
        
        std::vector<long long> free_vals(free_vars.size(), 0);
        search(0, free_vals);
        
        result += min_presses;
    }
    
    return result;
}

