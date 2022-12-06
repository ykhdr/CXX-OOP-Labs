#pragma once

#include <exception>
#include <string>

namespace SoundProcessorExceptions
{
    class BadConverterName : virtual public std::exception
    {
    private:
        std::string name_;

    public:
        BadConverterName(std::string name);

        const char *what() const noexcept override;
    };
}