#include "MuteConverter.hpp"
#include "ConverterException.hpp"

MuteConverter::MuteConverter(ConverterParams params)
{
    if (params.first < 0)
   {
        throw ConverterExceptions::BadFirstArgumentMuteConverter(params.first);
    }
    if (params.second < 0 || params.second <= params.first)
    {
        throw  ConverterExceptions::BadSecondArgumentMuteConverter(params.second);
    }

    secStart_ = params.first;
    secEnd_ = params.second;
}

void MuteConverter::convert(SampleBuffer &outputSample, SampleVector &inputSamples)
{
    if (currentSec_ >= secStart_ && currentSec_ <= secEnd_)
    {
        outputSample.fill(0);
    }
    ++currentSec_;
}