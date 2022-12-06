#include "ConfigParserExceptions.hpp"

using namespace ConfigExceptions;

BadOpeningConfig::BadOpeningConfig(std::string filePath) : filePath_(std::move(filePath))
{}

const char *BadOpeningConfig::what() const noexcept
{
    return std::string("File didn't open : " + filePath_).c_str();
}

BadReadingFile::BadReadingFile(std::string filePath) : filePath_(std::move(filePath))
{}

const char *BadReadingFile::what() const noexcept
{
    return std::string("Bad config file reading : " + filePath_).c_str();
}