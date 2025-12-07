#include <numeric>
#include <iostream>
#include "day7.h"


auto Laboratories::TachyonManifolds() -> int {
    std::string line;
    bool first_row = true;
    int splits = 0;
    while(std::getline(fp_, line)){
        for (size_t i = 0; i  < line.length(); ++i){
            if (first_row && line.at(i) == 'S'){
                beam_positions_.insert(i);
                first_row = false;
            } else if (line.at(i) == '^' && beam_positions_.count(i)) {
                beam_positions_.insert(i + 1);
                beam_positions_.insert(i - 1);
                beam_positions_.erase(i);
                ++splits;
            }
        }
    }
    return splits;
}

auto Laboratories::QuantumTachyonManifolds() -> long {
    std::string line;
    bool first_row = true;
    std::cout << "In function"<< std::endl;
    while(std::getline(fp_, line)){
        for (size_t i = 0; i  < line.length(); ++i){
            if (first_row && line.at(i) == 'S'){
                beam_timelines_[i] = 1L;
                first_row = false;
            } else if (line.at(i) == '^' && beam_timelines_.find(i) != beam_timelines_.end()) {
                if (i < line.length() - 1) {
                    if (beam_timelines_.find(i + 1) == beam_timelines_.end()){
                        beam_timelines_[i + 1] = 0L;
                    }
                    beam_timelines_.at(i + 1) = beam_timelines_.at(i + 1) + beam_timelines_.at(i);
                }
                if (i > 0) {
                    if (beam_timelines_.find(i - 1) == beam_timelines_.end()){
                        beam_timelines_[i - 1] = 0L;
                    }
                    beam_timelines_.at(i - 1) = beam_timelines_.at(i - 1) + beam_timelines_.at(i);
                }
                beam_timelines_.at(i) = 0L;
            }
        }
    }
    return std::accumulate(beam_timelines_.begin(), beam_timelines_.end(), 0L,
            [](long current_sum, const std::pair<size_t, long>& pair) {
                return current_sum + pair.second;
            });
}
