#pragma once

#include <fstream>
#include <tuple>
#include <iostream>

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
    std::basic_ostream<Ch, Tr> &os_;

public:
    explicit HelperCallable(std::basic_ostream<Ch, Tr> &os) : os_(os)
    {}

    template<typename ...Args>
    void operator()(const Args &... args)
    {
        printTuple(os_, args...);
    }
};

template<typename Ch, typename Tr, typename... Args>
auto operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Args...> const &tp)
{
    std::apply(HelperCallable(os), tp);
    return &os;
}