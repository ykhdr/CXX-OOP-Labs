#pragma once

#include <fstream>
#include <tuple>
#include <iostream>
namespace
{
    void printTuple(std::ostream &os)
    {
        os << "";
    }

    template<typename Arg>
    void printTuple(std::ostream &os, Arg arg)
    {
        os << arg;
    }

    template<typename First, typename... Args>
    void printTuple(std::ostream &os, First first, Args... args)
    {
        os << first << ", ";
        printTuple(os, args...);
    }

    template<typename Ch, typename Tr>
    class HelperCallable
    {
    private:
        std::basic_ostream<Ch, Tr> &os;

    public:
        explicit HelperCallable(std::basic_ostream<Ch, Tr> &os) : os(os)
        {}

        template<typename ...Args>
        void operator()(const Args &... args)
        {
            printTuple(os, args...);
        }
    };
}

template<typename Ch, typename Tr, typename... Types>
auto operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Types...> const &tp)
{
    std::apply(HelperCallable(os), tp);
    return &os;
}


// прописать здесь ридинг tuple'a по типам.

template<typename... Types>
std::tuple<Types...> makeTuple(const std::vector<std::string> &rowCells)
{
    auto tp_ptr = std::make_shared<std::tuple<Types...>>();


    reutrn *tp_ptr;
}