#pragma once

#include <limits>
#include <memory>
#include <vector>
#include <stdexcept>

#include "TupleUtility.hpp"

template<typename ...Args>
class CSVParser
{
private:
    class InputIterator;

    std::ifstream &input_file;

    int line_offset;

    char column_delimiter;
    char row_delimiter;
    char escape_sym;

    int current_line = 0;

    std::string getRow()
    {
        std::string row;
        std::getline(input_file, row, row_delimiter);

        ++current_line;

        return row;
    }

    std::vector<std::string> getRowCells(const std::string &row)
    {
        std::vector<std::string> row_cells(1);
        std::string cell;

        bool is_escape_sym = false;
        for (char sym: row)
        {
            if (sym == escape_sym)
            {
                is_escape_sym = true;
                continue;
            }

            if (sym == column_delimiter)
            {
                if (is_escape_sym)
                {
                    cell += sym;
                    continue;
                }
                row_cells.back() = cell;
                row_cells.emplace_back();
                cell.clear();
                continue;
            }

            cell += sym;
        }

        if (!cell.empty())
        {
            row_cells.back() = cell;
        }

        return row_cells;
    };

public:
    explicit CSVParser(
            std::ifstream &input_file,
            int line_offset = 0,
            char column_delimiter = ',',
            char line_delimiter = '\n',
            char escape_sym = '\"') :
            input_file(input_file),
            line_offset(line_offset),
            column_delimiter(column_delimiter),
            row_delimiter(line_delimiter),
            escape_sym(escape_sym)
    {
        if (!input_file.is_open())
        {
            throw std::ifstream::failure("File is not open");
        }

        for (; current_line < line_offset; ++current_line)
        {
            if (!input_file.ignore(std::numeric_limits<std::streamsize>::max(), input_file.widen(line_delimiter)))
            {
                throw std::ifstream::failure("File does not contain " + std::to_string(line_offset) + " lines");
            }
        }
    }

    InputIterator begin()
    {
        return InputIterator(*this, InputIterator::Mode::begin);
    }

    InputIterator end()
    {
        return InputIterator(*this, InputIterator::Mode::end);
    }
};

template<typename ...Args>
class CSVParser<Args...>::InputIterator
{
public:
    using value_type = std::tuple<Args...>;
    using reference = std::tuple<Args...> &;
    using pointer = std::shared_ptr<std::tuple<Args...>>;

    enum class Mode
    {
        begin,
        end
    };

    InputIterator(CSVParser &m_parent, Mode mode) : m_parent(m_parent)
    {
        switch (mode)
        {
            case Mode::begin:
                updatePtr();
                break;
            case Mode::end:
                m_ptr = nullptr;
        }
    }

    reference operator*() const
    {
        return *m_ptr;
    }

    pointer operator->()
    {
        return m_ptr;
    }

    InputIterator &operator++()
    {

        updatePtr();
        return *this;
    }

    InputIterator operator++(int)
    {
        InputIterator tmp = *this;
        updatePtr();
        return tmp;
    }

    friend bool operator==(const InputIterator &a, const InputIterator &b)
    {
        return a.m_ptr == b.m_ptr;
    }

    friend bool operator!=(const InputIterator &a, const InputIterator &b)
    {
        return a.m_ptr != b.m_ptr;
    }

private:
    CSVParser<Args...> m_parent;
    pointer m_ptr;

    void updatePtr()
    {
        std::string row = m_parent.getRow();
        if (row.empty())
        {
            m_ptr = nullptr;
            return;
        }

        std::vector<std::string> rowCells = m_parent.getRowCells(row);

        if (rowCells.size() > sizeof...(Args))
        {
            throw std::invalid_argument("Too many arguments on " + std::to_string(m_parent.current_line) + " line");
        }
        if(rowCells.size() < sizeof...(Args))
        {
            throw std::invalid_argument("Too few arguments on " + std::to_string(m_parent.current_line) + " line");
        }

        try
        {
            m_ptr = std::make_shared<value_type>(makeTuple<Args...>(rowCells));
        }
        catch (const std::invalid_argument &ex)
        {
            std::string msg = ex.what();
            msg +=  std::to_string(m_parent.current_line) + " row";
            throw std::invalid_argument(msg);
        }
    }
};