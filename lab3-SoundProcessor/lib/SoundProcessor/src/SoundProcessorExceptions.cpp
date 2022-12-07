#include "SoundProcessorExceptions.hpp"

#include <utility>

using namespace SoundProcessorExceptions;

BadConverterName::BadConverterName(std::string name) : name_(std::move(name))
{
}

const char *BadConverterName::what() const noexcept
{
    return std::string("Bad converter name : " + name_).c_str();
}

const char *HelpArgument::what() const noexcept
{
    return "";
}