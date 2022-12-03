#include "MuteConverter.hpp"

MuteConverter::MuteConverter(Params params)
{
    if (params.first < 0)
   {
        throw std::exception();
    }
    if (params.second < 0 || params.second <= params.first)
    {
        throw std::exception();
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