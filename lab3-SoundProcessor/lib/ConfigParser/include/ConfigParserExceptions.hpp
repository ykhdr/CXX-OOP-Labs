#pragma once

#include <exception>
#include <string>

namespace ConfigExceptions
{
    class BadOpeningConfig : virtual public std::exception
    {
    private:
        std::string filePath_;

    public:
        BadOpeningConfig(std::string filePath);

        const char *what() const noexcept override;
    };

    class BadReadingFile : virtual public std::exception
    {
    private:
        std::string filePath_;

    public:
        BadReadingFile(std::string filePath);

        const char *what() const noexcept override;
    };
}