#pragma once

#include <limits>

#include "TuplePrint.hpp"

template<typename ...Types>
class CSVParser
{
private:
    class InputIterator;

    std::ifstream &input_file_;

    int line_offset_;

    char column_delimiter_;
    char line_delimiter_;
    char escape_sym_;

    int current_line_ = 0;

public:
    explicit CSVParser(
            std::ifstream &input_file,
            int line_offset = 0,
            char column_delimiter = ',',
            char line_delimiter = '\n',
            char escape_sym = '\"') :
            input_file_(input_file),
            line_offset_(line_offset),
            column_delimiter_(column_delimiter),
            line_delimiter_(line_delimiter),
            escape_sym_(escape_sym)
    {
        if (!input_file_.is_open())
        {
            throw std::ifstream::failure("File is not open");
        }

        for (current_line_; current_line_ < line_offset; ++current_line_)
        {
            if (!input_file_.ignore(std::numeric_limits<std::streamsize>::max(), input_file.widen(line_delimiter_)))
            {
                throw std::ifstream::failure("File does not contain " + std::to_string(line_offset_) + " lines");
            }
        }
    }

    CSVParser(const CSVParser &) = delete;

    InputIterator begin()
    {

    }

    InputIterator end()
    {

    }
};

template<typename ...Types>
class CSVParser<Types...>::InputIterator
{
    
};