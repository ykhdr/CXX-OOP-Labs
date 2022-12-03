#pragma once

#include <fstream>
#include <string>

#include "WAVUtil.hpp"

class WAVReader;

using WAVReaderVector = std::vector<WAVReader>;

class WAVReader
{
private:
    std::ifstream inputFile_;

    void open(std::string filePath);

    void readHeader();
public:
    WAVReader() = default;

    WAVReader(std::string filePath);

    bool readSample(SampleBuffer & sampleBuffer);
};