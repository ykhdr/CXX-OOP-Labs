#pragma once

#include <string>
#include <fstream>

#include "WAVUtil.hpp"

class WAVWriter
{
private:
    std::ofstream outputFile_;

    void writeHeader();

public:
    WAVWriter() = default;

    WAVWriter(std::string path);

    void fixHeader();

    void writeSample(SampleBuffer);
};