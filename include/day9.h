#include <string>
#include <fstream>
#include <cassert>
#include <cmath>
#include <sstream>
#include <iostream>
#include <vector>

class Vertex{
    private:    
        bool flat;
    public:
        Vertex() = default;
        Vertex(int x_, int y_): x(x_), y(y_), z(0), flat(true) {} // For 2D points
        Vertex(int x_, int y_, int z_): x(x_), y(y_), z(z_), flat(false) {} // For 3D points
        int x;
        int y;
        int z;
        
        bool operator==(const Vertex& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
        auto Distance(const Vertex& other) const -> long long{
            return std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2);
        }
        auto Height(const Vertex& other) const -> long long{
            return std::abs(x - other.x + 1);
        }
        auto Width(const Vertex& other) const -> long long{
            return std::abs(y - other.y + 1);
        }
       
};


std::istream& operator>>(std::istream& is, Vertex& p);


class MovieTheater {
    private:
        std::ifstream fp_;
        std::vector<Vertex> grid_;
    public:
        MovieTheater(std::string file_name): fp_(file_name){
            std::string line;
            
            while(std::getline(fp_, line)){
                std::stringstream ss(line);
                Vertex point(0, 0);
                while (ss >> point) {
                    grid_.emplace_back(point);
                }
            }
            ResetFp();
        }
        ~MovieTheater(){}
        auto ResetFp() -> void {
            fp_.clear();
            fp_.seekg(0, std::ios::beg);
        }
        auto MaximumRectangle() -> long;
        auto IsOrthogonal(Vertex a, Vertex b, Vertex c) -> bool;
        auto IsRectangle(Vertex a, Vertex b, Vertex c, Vertex d) -> bool;
        auto CanMakeRect(Vertex A, Vertex C, long* area) -> bool;
        auto PointOnBoundary(const Vertex& N) -> bool;
        auto PointWithinBoundary(const Vertex& N) -> bool;
        auto IntersectsBoundary(long minX, long maxX, long minY, long maxY) -> bool;

};
