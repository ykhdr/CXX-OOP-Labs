#include "fstream"
#include <iostream>
#include "CSVParser.hpp"
#include "TupleUtility.hpp"

int main(int argc, char const *argv[])
{
    try
    {
        if (argc < 2 || argc > 6)
        {
            throw std::invalid_argument("Wrong number of parameters. Use -h or --help for help");
        }

        std::ifstream file(argv[1]);

        if (argc == 2)
        {
            CSVParser<int, std::string> parser(file);
                for (const auto &rs: parser)
                {
                    std::cout << rs;
                    std::cout << std::endl;
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
                CSVParser<int, std::string> parser(file, line_offset);
//                for (const auto &rs: parser)
//                {
//                    std::cout << rs << std::endl;
//                }
            }
            else if(argc == 4)
            {
                CSVParser<int, std::string> parser(file, line_offset,*argv[3]);
//                for (const auto &rs: parser)
//                {
//                    std::cout << rs << std::endl;
//                }
            }
            else if(argc == 5)
            {
                CSVParser<int, std::string> parser(file, line_offset,*argv[3],*argv[4]);
//                for (const auto &rs: parser)
//                {
//                    std::cout << rs << std::endl;
//                }
            }
            else if(argc == 6)
            {
                CSVParser<int, std::string> parser(file, line_offset, *argv[3], *argv[4], *argv[5]);
//                for (const auto &rs: parser)
//                {
//                    std::cout << rs << std::endl;
//                }
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
