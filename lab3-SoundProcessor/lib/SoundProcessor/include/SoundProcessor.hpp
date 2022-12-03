#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "WAVReader.hpp"
#include "ConverterCreator.hpp"
#include "ConfigParser.hpp"
#include "WAVWriter.hpp"

class SoundProcessor
{
    std::string configFilePath_;

    std::string outputFIlePath_;

    std::vector<std::string> inputFilesPaths_;

    WAVReaderVector wavReaderVector_;

    static ConverterPipeline createPipeline(ConfigParams &params);

    WAVReaderVector createWAVReaderVector();

    bool updateSamples(SampleVector &defaultSamples);

public:
    SoundProcessor(int &argc, char const *argv[]);

    void run();
};
