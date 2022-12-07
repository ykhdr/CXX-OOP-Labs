#include "MixConverter.hpp"
#include "ConverterException.hpp"

#include <algorithm>

MixConverter::MixConverter(ConverterParams params)
{
    if (params.first < 1)
    {
        // throw exception about invalid id for mix
        throw  ConverterExceptions::BadFirstArgumentMixConverter(params.first);
    }
    if (params.second < 0)
    {
        // throw exception about invalid second start
        throw  ConverterExceptions::BadSecondArgumentMixConverter(params.second);
    }

    idWAVForMix_ = params.first;
    secStart_ = params.second;
}

void MixConverter::convert(SampleBuffer &outputSample, SampleVector &inputSamples)
{
    if (currentSec_ >= secStart_)
    {
        for (int i = 0; i < outputSample.size(); ++i)
        {
            outputSample[i] = outputSample[i] / 2 + inputSamples[idWAVForMix_ - 1][i] / 2;
        }
    }
    ++currentSec_;
}