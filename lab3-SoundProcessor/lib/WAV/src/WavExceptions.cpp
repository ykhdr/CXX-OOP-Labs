#include "WAVExceptions.hpp"

using namespace WAVExceptions;

BadFileFormat::BadFileFormat(std::string filePath) : filePath_(std::move(filePath))
{}

const char *BadFileFormat::what() const noexcept
{
    return std::string("Bad file format : " + filePath_).c_str();
}

BadFileOpening::BadFileOpening(std::string filePath) : filePath_(std::move(filePath))
{}

const char *BadFileOpening::what() const noexcept
{
    return std::string("Bad file opening : " + filePath_).c_str();
}

BadChunkHeaderFormat::BadChunkHeaderFormat(std::string filePath, uint32_t chunkName) :
        filePath_(std::move(filePath)), chunkName_(std::move(std::to_string(chunkName)))
{}

const char *BadChunkHeaderFormat::what() const noexcept
{
    return std::string("Bad " + chunkName_ + " chunk format: " + filePath_).c_str();
}

BadFormatHeader::BadFormatHeader(std::string filePath) : filePath_(std::move(filePath))
{}

const char *BadFormatHeader::what() const noexcept
{
    return std::string("Bad header field format : " + filePath_).c_str();
}

BadFMTChunkDataFormat::BadFMTChunkDataFormat(std::string filePath) : filePath_(std::move(filePath)){}

const char *BadFMTChunkDataFormat::what() const noexcept
{
    return std::string("Bad FMT chunk data format : " + filePath_).c_str();
}

BadReadingFile::BadReadingFile(std::string filePath) : filePath_(std::move(filePath)) {}

const char *BadReadingFile::what() const noexcept
{
    return std::string("Bad reading file : " + filePath_).c_str();
}

BadWritingFile::BadWritingFile(std::string filePath) : filePath_(std::move(filePath)) {}

const char *BadWritingFile::what() const noexcept
{
    return std::string("Bad writing in file : " + filePath_).c_str();
}