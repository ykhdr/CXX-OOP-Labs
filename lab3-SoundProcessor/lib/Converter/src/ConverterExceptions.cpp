#include "ConverterException.hpp"

using namespace ConverterExceptions;

BadFirstArgumentMixConverter::BadFirstArgumentMixConverter(int argument) : argument_(argument)
{}

const char *BadFirstArgumentMixConverter::what() const noexcept
{
    std::string str = "Bad first argument for mix converter : " + std::to_string(argument_);
    return str.c_str();
}

BadSecondArgumentMixConverter::BadSecondArgumentMixConverter(int argument) : argument_(argument)
{}

const char *BadSecondArgumentMixConverter::what() const noexcept
{
    std::string str = "Bad second argument for mix converter : " + std::to_string(argument_);
    return str.c_str();
}

BadFirstArgumentMuteConverter::BadFirstArgumentMuteConverter(int argument) : argument_(argument)
{}

const char *BadFirstArgumentMuteConverter::what() const noexcept
{
    std::string str = "Bad first argument for mute converter : " + std::to_string(argument_);
    return str.c_str();
}

BadSecondArgumentMuteConverter::BadSecondArgumentMuteConverter(int argument) : argument_(argument)
{}

const char *BadSecondArgumentMuteConverter::what() const noexcept
{
    std::string str = "Bad second argument for mute converter : " + std::to_string(argument_);
    return str.c_str();
}

BadFirstArgumentDoubleMixConverter::BadFirstArgumentDoubleMixConverter(int argument) : argument_(argument)
{}

const char *BadFirstArgumentDoubleMixConverter::what() const noexcept
{
    std::string str = "Bad first argument for double mix converter : " + std::to_string(argument_);
    return str.c_str();
}

BadSecondArgumentDoubleMixConverter::BadSecondArgumentDoubleMixConverter(int argument) : argument_(argument)
{}

const char*BadSecondArgumentDoubleMixConverter::what() const noexcept
{
    std::string str = "Non-existent second argument for double mix converter  : " + std::to_string(argument_);
    return str.c_str();
}

RecurringSecondArgumentDoubleMixConverter::RecurringSecondArgumentDoubleMixConverter(int argument) : argument_(argument)
{}

const char*RecurringSecondArgumentDoubleMixConverter::what() const noexcept
{
    std::string str = "Recurring second argument for double mix converter  : " + std::to_string(argument_);
    return str.c_str();
}