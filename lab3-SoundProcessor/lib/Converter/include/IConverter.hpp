#pragma once

#include <fstream>
#include <memory>

#include "WAVUtil.hpp"

class IConverter;

using ConverterParams = std::pair<int,int>;
using ConverterPtr = std::shared_ptr<IConverter>;

using ConverterPipeline = std::vector<ConverterPtr>;

class IConverter
{
public:
    ~IConverter() = default;

    virtual void convert(SampleBuffer &outputSample, SampleVector &inputSamples) = 0;
};

