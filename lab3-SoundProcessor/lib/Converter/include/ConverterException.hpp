#pragma once

#include <string>

namespace ConverterExceptions
{

    class BadFirstArgumentMixConverter : virtual public std::exception
    {
    private:
        int argument_;

    public:
        BadFirstArgumentMixConverter(int argument);

        const char *what() const noexcept override;
    };

    class BadSecondArgumentMixConverter : virtual public std::exception
    {
    private:
        int argument_;

    public:
        BadSecondArgumentMixConverter(int argument);

        const char *what() const noexcept override;
    };

    class BadFirstArgumentMuteConverter : virtual public std::exception
    {
    private:
        int argument_;

    public:
        BadFirstArgumentMuteConverter(int argument);

        const char *what() const noexcept override;
    };

    class BadSecondArgumentMuteConverter : virtual public std::exception
    {
    private:
        int argument_;

    public:
        BadSecondArgumentMuteConverter(int argument);

        const char *what() const noexcept override;
    };
}