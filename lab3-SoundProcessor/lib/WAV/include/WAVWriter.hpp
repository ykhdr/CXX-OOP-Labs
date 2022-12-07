#pragma once

#include <string>
#include <fstream>

#include "WAVUtil.hpp"

class WAVWriter
{
private:
    std::ofstream outputFile_;

    std::string outputFilePath_;

    void writeHeader();

public:
    WAVWriter() = default;

    WAVWriter(const std::string& path);

    ~WAVWriter();

    void fixHeader();

    void writeSample(SampleBuffer);
};