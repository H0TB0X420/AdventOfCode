#include "day9.h"
#include <sstream>
#include <string>

std::istream& operator>>(std::istream& is, Vertex& p) {
    std::string segment;
    
    p.z = 0; 

    if (!std::getline(is, segment, ',')) return is;
    p.x = std::stoi(segment);

    if (!std::getline(is, segment, ',')) return is;
    p.y = std::stoi(segment);
    if (!is.eof()) {
        if (std::getline(is, segment)) {
            p.z = std::stoi(segment);
        }
    }
    if (is.fail()) {
        std::cout << "DEBUG: Stream failed inside operator!" << std::endl;
    }
    return is;
}

auto MovieTheater::MaximumRectangle() -> long {
    long result = 0;
    long area = 0;
    long* ref = &area;
    for(size_t i = 0; i < grid_.size(); ++i){
        for (size_t j = i + 1; j < grid_.size(); ++j){
            if (CanMakeRect(grid_[i], grid_[j], ref)){
                // std::cout<<"("<< grid_[i].x << "," << grid_[i].y<< ")" << std::endl;
                // std::cout<<"("<< grid_[j].x << "," << grid_[j].y<< ")" << std::endl;
                // std::cout<<"Area: " << area << std::endl;
                if (area > result){
                    result = area;
                }
            }
        }
    }
    return result;
}

auto MovieTheater::PointOnBoundary(const Vertex& N) -> bool{
    // This function assumes no diagonals are possible 
    for (size_t i = 0; i < grid_.size(); ++i){
        Vertex X = grid_[i];
        Vertex Y = grid_[(i+1) % grid_.size()];
        if (N.x == X.x && N.x == Y.x && (std::min(X.y, Y.y) <= N.y && N.y <= std::max(X.y, Y.y))){
            return true;
        } else if (N.y == X.y && N.y == Y.y && (std::min(X.x, Y.x) <= N.x && N.x <= std::max(X.x, Y.x))) {
            return true;
        }
    }
    return false;
    
}

auto MovieTheater::PointWithinBoundary(const Vertex& N) -> bool{
    bool inside = false;
    for (size_t i = 0; i < grid_.size(); ++i){
        Vertex X = grid_[i];
        Vertex Y = grid_[(i+1) % grid_.size()];
        if (N.x == X.x && N.x == Y.x && (std::min(X.y, Y.y) <= N.y && N.y <= std::max(X.y, Y.y))) {
            return true;
        } 
        else if (N.y == X.y && N.y == Y.y && (std::min(X.x, Y.x) <= N.x && N.x <= std::max(X.x, Y.x))) {
            return true;
        }

        bool spansY = (X.y > N.y) != (Y.y > N.y);

        if (spansY) {
            double intersectX = X.x + (double)(N.y - X.y) * (Y.x - X.x) / (Y.y - X.y);
            if (N.x < intersectX){
                inside = !inside;
            }
        }
    }
    return inside;
}


auto MovieTheater::IsOrthogonal(Vertex a, Vertex b, Vertex c) -> bool{
    return (b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y) == 0;
}

auto MovieTheater::IsRectangle(Vertex a, Vertex b, Vertex c, Vertex d) -> bool{
    return
        IsOrthogonal(a, b, c) &&
        IsOrthogonal(b, c, d) &&
        IsOrthogonal(c, d, a);
}
auto MovieTheater::CanMakeRect(Vertex A, Vertex C, long* area) -> bool{
        // Create the other 2 points using self and other
        // A = (2, 5), C = (9, 7) : self and other
        
        const Vertex& B = Vertex(C.x, A.y); // B = (9, 5)
        const Vertex& D = Vertex(A.x, C.y); // D = (2, 7),
        if (A == B || A == D || C == B || C == D) {
            return false;
        }
        // P2 only
        if ((!PointOnBoundary(B) && !PointWithinBoundary(B)) || (!PointOnBoundary(D) && !PointWithinBoundary(D))){
            return false;
        } 
        
        long minX = std::min(A.x, C.x);
        long maxX = std::max(A.x, C.x);
        long minY = std::min(A.y, C.y);
        long maxY = std::max(A.y, C.y);
        // if any boundary lines cross the rectangle edges
        if (IntersectsBoundary(minX, maxX, minY, maxY)) {
            return false;
        }
        for (const auto& V : grid_) { // check no boundary vertex is strictly inside rectangle
            if (V.x > minX && V.x < maxX && V.y > minY && V.y < maxY) {
                return false;
            }
        }
        long width = maxX - minX + 1;
        long height = maxY - minY + 1;
        *area = width * height;

        return true;
        // End P2 only
        // P1 below
        // if (IsRectangle(A, B, C, D)){
        //     *area = A.Height(B) * B.Width(C);
        //     return true;
        // } else if (IsRectangle(B, C, A, D)){
        //     *area = B.Height(C) * C.Width(D);
        //     return true;
        // } else if (IsRectangle(C, A, B, D)){
        //     *area = C.Height(D) * D.Width(A);
        //     return true;
        // }
        // return false;
}

auto MovieTheater::IntersectsBoundary(long minX, long maxX, long minY, long maxY) -> bool {
    for (size_t i = 0; i < grid_.size(); ++i) {
            Vertex P1 = grid_[i];
            Vertex P2 = grid_[(i + 1) % grid_.size()];
            if (std::max(P1.x, P2.x) <= minX || std::min(P1.x, P2.x) >= maxX ||
                std::max(P1.y, P2.y) <= minY || std::min(P1.y, P2.y) >= maxY) {
                continue;
            }
            long targetsY[] = {minY, maxY};
            for (long yVal : targetsY) {
                if ((P1.y < yVal && P2.y > yVal) || (P1.y > yVal && P2.y < yVal)) {
                    double t = (double)(yVal - P1.y) / (P2.y - P1.y);
                    double intersectX = P1.x + t * (P2.x - P1.x);
                    if (intersectX > minX && intersectX < maxX) return true;
                }
            }

            long targetsX[] = {minX, maxX};
            for (long xVal : targetsX) {
                if ((P1.x < xVal && P2.x > xVal) || (P1.x > xVal && P2.x < xVal)) {
                    double t = (double)(xVal - P1.x) / (P2.x - P1.x);
                    double intersectY = P1.y + t * (P2.y - P1.y);
                    if (intersectY > minY && intersectY < maxY) return true;
                }
            }
        }
    return false; 
}