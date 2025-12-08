#include "day8.h"

#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>

std::istream& operator>>(std::istream& is, Point& p) {
    std::string segment;

    if (std::getline(is, segment, ',')) {
        p.x = std::stoi(segment);
    } else {
        return is; 
    }
    if (std::getline(is, segment, ',')) {
        p.y = std::stoi(segment);
    } else {
        return is;
    }
    if (std::getline(is, segment)) {
        try {
            p.z = std::stoi(segment); 
        } catch (...) {
            is.setstate(std::ios_base::failbit); 
        }
    }
    return is;
}


auto Playground::ReadFile() -> void {
    std::string line;
    while(std::getline(fp_, line)){
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        Point point;
        while (ss >> point) {
            junctions_.push_back(point);
        }
    }
    // for (const auto& j: junctions_){
    //     std::cout<<"X: "<< j.x << ", Y: " << j.y << ", Z: " << j.z << std::endl;
    //     std::cout<< "Point size: " << j.merged_size << std::endl;
    // }
}

auto Playground::ConnectJunctionBoxes(size_t iterations) -> long long {
    std::vector<std::tuple<size_t, size_t, long long>> distances;
    for (size_t j = 0; j < junctions_.size(); ++j){
        for (size_t k = j + 1; k < junctions_.size(); ++k){
            long long distance = junctions_[j].Distance(junctions_[k]);
            distances.push_back(std::make_tuple(j, k, distance));
        }
    }
    std::sort(distances.begin(), distances.end(),
    [](const std::tuple<size_t, size_t, long long>& lhs, const std::tuple<size_t, size_t, long long>& rhs) {
        return std::get<2>(lhs) < std::get<2>(rhs);
    });

    
    /*
    auto uf = UnionFind(distances.size());
    for(size_t i = 0; i < iterations; ++i) {
        auto [u, v, dist] = distances[i];
        uf.Union(u, v);
    }
    
    std::vector<size_t> sizes = uf.GetComponentSizes();
    
    std::sort(sizes.begin(), sizes.end(), std::greater<size_t>());
    std::cout << "Top 3 sizes: " << sizes[0] << ", " << sizes[1] << ", " << sizes[2] << std::endl;
    // for (auto size: sizes){
    //     std::cout<< size << std::endl;
    // }
    long long result = 1;
    if (sizes.size() >= 3) {
        result = (long long)sizes[0] * sizes[1] * sizes[2];
    }*/
    
    auto uf = UnionFind(junctions_.size());
    for (const auto& [u, v, dist] : distances) {
        if (!uf.Connected(u, v)) {
            uf.Union(u, v);
            if (uf.comps_ == 1) {
                long long x1 = junctions_.at(u).x;
                long long x2 = junctions_.at(v).x;
                
                std::cout << "Final Connection found between " << x1 << " and " << x2 << std::endl;
                return x1 * x2;
            }
        }
    }

    return 0; // Should not reach here
    
}
