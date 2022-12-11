#include "SoundProcessorExceptions.hpp"

#include <utility>

using namespace SoundProcessorExceptions;

BadConverterName::BadConverterName(const std::string &name) : invalid_argument("Bad converter name: " + name)
{}

HelpArgument::HelpArgument() : invalid_argument("")
{
}
