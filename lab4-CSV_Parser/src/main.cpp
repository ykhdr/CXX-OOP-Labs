#include "fstream"
#include <iostream>
#include "CSVParser.hpp"
#include "TupleUtility.hpp"

namespace
{
    void printHelp()
    {
        std::cout << "\n\t\t\tCSV Parser" << std::endl
                  << std::endl
                  << "\t1 argument \t--\t input file path" << std::endl
                  << "\t2 argument \t--\t skip first lines count (default = 0)" << std::endl
                  << "\t3 argument \t--\t custom column delimiter (default = ',')" << std::endl
                  << "\t4 argument \t--\t custom row delimiter (default = '\\n')" << std::endl
                  << "\t5 argument \t--\t custom escape symbol (default = '\"')" << std::endl
                  << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        if (std::string_view(argv[1]) == "--help" || std::string_view(argv[1]) == "-h")
        {
            printHelp();
            return EXIT_SUCCESS;
        }

        if (argc < 2 || argc > 6)
        {
            throw std::invalid_argument("Wrong number of parameters. Use -h or --help for help");
        }

        std::ifstream file(argv[1]);

        if (argc == 2)
        {
            CSVParser<std::string, int, std::string> parser(file);
            for (const auto &row: parser)
            {
                std::cout << row << std::endl;
            }
        }
        else
        {
            int line_offset;
            try
            {
                line_offset = std::stoi(argv[2]);
            }
            catch (const std::exception &ex)
            {
                throw std::invalid_argument("Bad line offset parameter :" + std::string(argv[2]));
            }

            if (argc == 3)
            {
                CSVParser<std::string, int, std::string> parser(file, line_offset);
                for (const auto &row: parser)
                {
                    std::cout << row << std::endl;
                }
            }
            else if (argc == 4)
            {
                CSVParser<std::string, int, std::string> parser(file, line_offset, *argv[3]);
                for (const auto &row: parser)
                {
                    std::cout << row << std::endl;
                }
            }
            else if (argc == 5)
            {
                CSVParser<std::string, int, std::string> parser(file, line_offset, *argv[3], *argv[4]);
                for (const auto &row: parser)
                {
                    std::cout << row << std::endl;
                }
            }
            else if (argc == 6)
            {
                CSVParser<std::string, int, std::string> parser(file, line_offset, *argv[3], *argv[4], *argv[5]);
                for (const auto &row: parser)
                {
                    std::cout << row << std::endl;
                }
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
