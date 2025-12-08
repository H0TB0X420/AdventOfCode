#include <cmath>
#include <numeric>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <string>
#include <memory>

class Point{
    public:
        Point() = default;
        Point(int x_, int y_, int z_, size_t size): 
        x(x_), y(y_), z(z_) {}
        int x;
        int y;
        int z;
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
        auto Distance(const Point& other) -> long long{
            return std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2);
        }
};

class UnionFind {
    public:
        size_t comps_;
        UnionFind(size_t n) : comps_(n){
            parents_.resize(n);
            std::iota(parents_.begin(), parents_.end(), 0);
            sizes_.assign(n, 1);
        }
        auto Union(size_t x, size_t y) -> void {
            size_t rootX = Find(x);
            size_t rootY = Find(y);

            if (rootX != rootY) {
                if (sizes_[rootX] > sizes_[rootY]) {
                    std::swap(rootX, rootY);
                }
                
                parents_[rootX] = rootY;
                sizes_[rootY] += sizes_[rootX];
                comps_--;
            }
        }
        auto Find(size_t x) -> size_t{
            if (x != parents_.at(x)){
                parents_[x] = Find(parents_.at(x));
            }
            return parents_.at(x);
        }
        auto Connected(size_t x, size_t y) -> bool {
            return Find(x) == Find(y);
        }

        auto GetComponentSizes() -> std::vector<size_t> {
            std::vector<size_t> valid_sizes;
            for (size_t i = 0; i < parents_.size(); ++i) {
                if (parents_[i] == i) {
                    valid_sizes.push_back(sizes_[i]);
                }
            }
            return valid_sizes;
        }
    private:
        std::vector<size_t> parents_;
        std::vector<size_t> sizes_;
        

};


std::istream& operator>>(std::istream& is, Point& p);


class Playground {
    private:
        std::ifstream fp_;
        std::vector<Point> junctions_; 
        
    public:
        Playground(std::string file_name) : fp_(file_name){}
        ~Playground(){}
        auto ResetFp() -> void {
            fp_.clear();
            fp_.seekg(0, std::ios::beg);
        }
        auto ReadFile() -> void;
        auto ConnectJunctionBoxes(size_t) -> long long;
};