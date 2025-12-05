#include <string>
#include <fstream>

class PrintingDepartment{

    private:
        std::fstream fp_;
        size_t row_bounds_ = 0;
        size_t col_bounds_ = 0;
    public:
        PrintingDepartment(std::string file_name);
        ~PrintingDepartment(){};
        auto ResetFp() -> void;
        auto GetAccessibleRolls() -> int; 
        auto InBounds(int row, int col) -> bool;
};
