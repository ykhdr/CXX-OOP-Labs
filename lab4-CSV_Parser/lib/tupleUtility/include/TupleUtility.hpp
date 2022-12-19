#pragma once

#include <fstream>
#include <tuple>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

template<std::size_t>
struct size_t_ {};

namespace
{
    template<typename Ch, typename Tr, class Tuple>
    std::basic_ostream<Ch, Tr> &printTuple(std::basic_ostream<Ch, Tr> &os, const Tuple &t, size_t_<1>)
    {
        return os << std::get<std::tuple_size<Tuple>::value - 1>(t);
    }

    template<typename Ch, typename Tr, class Tuple>
    std::basic_ostream<Ch, Tr> &printTuple(std::basic_ostream<Ch, Tr> &os, const Tuple &t, size_t_<0>)
    {
        return os;
    }

    template<typename Ch, typename Tr, class Tuple, size_t Pos>
    std::basic_ostream<Ch, Tr> &printTuple(std::basic_ostream<Ch, Tr> &os, const Tuple &t, size_t_<Pos>)
    {
        os << std::get<std::tuple_size<Tuple>::value - Pos>(t) << ", ";
        return printTuple(os, t, size_t_<Pos - 1>());
    }

    template<typename Type>
    Type readValue(const std::string &row)
    {
        std::istringstream iss(row);
        Type value;

        if (!(iss >> value))
        {
            throw std::invalid_argument("bad reading type of \"" + row + "\" at ");
        }

        return value;
    }

    template<>
    std::string readValue<std::string>(const std::string &row)
    {
        return row;
    }

    template<typename... Types>
    void fillTuple(std::tuple<Types...> &tp, const std::vector<std::string> &rowCells, size_t_<1>)
    {
        try
        {
            std::get<0>(tp) = readValue<typename std::tuple_element<0, std::tuple<Types...>>::type>(rowCells[0]);
        }
        catch (const std::exception &ex)
        {
            std::string msg = ex.what();
            msg += std::to_string(1) + " column, ";

            throw std::invalid_argument(msg);
        }
    }

    template<typename... Types, size_t N>
    void fillTuple(std::tuple<Types...> &tp, const std::vector<std::string> &rowCells, size_t_<N>)
    {
        try
        {
            std::get<N - 1>(tp) = readValue<typename std::tuple_element<N - 1, std::tuple<Types...>>::type>(
                    rowCells.at(N - 1));
        }
        catch (const std::invalid_argument &ex)
        {
            std::string msg = ex.what();
            msg += std::to_string(N) + " column, ";

            throw std::invalid_argument(msg);
        }

        fillTuple<Types...>(tp, rowCells, size_t_<N - 1>());
    }
}

template<typename Ch, typename Tr, typename... Types>
auto operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Types...> const &tp)
{
    printTuple(os, tp, size_t_<sizeof...(Types)>());
    return &os;
}

template<typename... Types>
std::tuple<Types...> makeTuple(const std::vector<std::string> &rowCells)
{
    std::tuple<Types...> tp;
    fillTuple(tp, rowCells, size_t_<sizeof...(Types)>());

    return tp;
}