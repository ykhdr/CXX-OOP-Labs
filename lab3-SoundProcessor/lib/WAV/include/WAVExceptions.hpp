#pragma once

#include <exception>
#include <string>
namespace WAVExceptions
{
    class BadFileFormat : virtual public std::exception
    {
    private:
        std::string filePath_;

    public:
        BadFileFormat(std::string filePath);

        const char *what() const noexcept override;
    };

    class BadFileOpening : virtual public std::exception
    {
    private:
        std::string filePath_;

    public:
        BadFileOpening(std::string filePath);

        const char *what() const noexcept override;
    };

    class BadChunkHeaderFormat : virtual public std::exception
    {
    private:
        std::string filePath_;

        std::string chunkName_;

    public:
        BadChunkHeaderFormat(std::string filePath, uint32_t chunkName);

        const char *what() const noexcept override;
    };

    class BadFormatHeader : virtual public std::exception
    {
    private:
        std::string filePath_;

    public:
        BadFormatHeader(std::string filePath);

        const char *what() const noexcept override;
    };

    class BadFMTChunkDataFormat : virtual public std::exception
    {
    private:
        std::string filePath_;

    public:
        BadFMTChunkDataFormat(std::string filePath);

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

    class BadWritingFile : virtual public std::exception
    {
    private:
        std::string filePath_;

    public:
        BadWritingFile(std::string filePath);

        const char *what() const noexcept override;
    };
}