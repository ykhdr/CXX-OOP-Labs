#include "SoundProcessor.hpp"
#include "SoundProcessorExceptions.hpp"

#include <iostream>

SoundProcessor::SoundProcessor(int &argc, const char **argv)
{

    if (argc < 5)
    {
        throw std::invalid_argument("incorrect number of parameters");
    }
    if (std::string_view(argv[1]) != "-c")
    {
        throw std::invalid_argument("-c Argument was not found");
    }

    configFilePath_ = std::string(argv[2]);
    outputFilePath_ = std::string(argv[3]);

    for (int i = 4; i < argc; ++i)
    {
        inputFilesPaths_.emplace_back(argv[i]);
    }
}

void SoundProcessor::run()
{
    try
    {
        ConfigParser configParser(configFilePath_);

        ConfigParamLine configParams = configParser.getConfig();

        ConverterPipeline pipeline = createPipeline(configParams);

        wavReaderVector_ = createWAVReaderVector();

        WAVWriter wavOutputWriter(outputFilePath_);

        SampleBuffer outputSample;

        SampleVector defaultSamples(inputFilesPaths_.size());

        while (updateSamples(defaultSamples))
        {
            outputSample = defaultSamples[0];

            for (const auto &converter: pipeline)
            {
                converter->convert(outputSample,defaultSamples);
            }

            wavOutputWriter.writeSample(outputSample);
        }

        wavOutputWriter.fixHeader();
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

ConverterPipeline SoundProcessor::createPipeline(ConfigParamLine &params)
{
    ConverterPipeline pipeline;

    for (const auto &param: params)
    {
        if (param.first == "mute")
        {
            pipeline.push_back(MuteConverterCreator().create(param.second));
        }
        else if (param.first == "mix")
        {
            pipeline.push_back(MixConverterCreator().create(param.second));
        }
        else
        {
            // throw exception about invalid convertor name
            throw SoundProcessorExceptions::BadConverterName(param.first);
        }
    }
    return pipeline;
}

WAVReaderVector SoundProcessor::createWAVReaderVector()
{
    WAVReaderVector wavReaderVector;

    for (const auto &inputFilesPath: inputFilesPaths_)
    {
        wavReaderVector.emplace_back(inputFilesPath);
    }

    return wavReaderVector;
}

bool SoundProcessor::updateSamples(SampleVector &defaultSamples)
{
    if (!wavReaderVector_[0].readSample(defaultSamples[0]))
    {
        return false;
    }

    for (int i = 1; i < defaultSamples.size(); ++i)
    {
        wavReaderVector_[i].readSample(defaultSamples[i]);
    }

    return true;

}