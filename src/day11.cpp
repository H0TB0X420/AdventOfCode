#include "day11.h"
#include <queue>
auto Reactor::FindAllPaths(std::string start, std::string stop) -> int {
    int paths = 0;
    std::queue<std::string> q;
    q.push(start); 
        
    while (!q.empty()){
        auto device = q.front();
        q.pop();
        for(auto neighbor: graph_[device]){
            if (neighbor == stop){
                ++paths;
            } else {
                q.push(neighbor);
            }
        }
    }
    return paths;
}

auto Reactor::FindAllDacFftPaths(std::string node, bool fft, bool dac) -> long long {
    if (node == "fft") {
        fft = true;
    }
    if (node == "dac") {
        dac = true;
    }

    std::string key = node + ":" + (fft ? "true": "false") + ":" + (dac ? "true": "false");

    if (cache_.contains(key)){
        return cache_[key];
    }
    
    if (node == "out"){
        return (dac && fft) ? 1 : 0;
    }

    long long paths = 0;
    for (const auto neighbor: graph_[node]){
        paths += FindAllDacFftPaths(neighbor, fft, dac);  
    }
    
    cache_[key] = paths; 
    return paths;
}