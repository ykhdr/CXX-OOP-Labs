#include "fstream"
#include <iostream>
#include "CSVParser.hpp"
#include "TuplePrint.hpp"

int main(int argc, char const *argv[])
{
    std::tuple tp{1, "1", 10223.123, char(213)};

    std::ofstream os{"text.txt"};
    std::cout << tp;
    os << tp;

    std::tuple tp1;
    std::cout << tp1;

    return 0;
}
