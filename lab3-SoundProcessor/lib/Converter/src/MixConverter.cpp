#include "MixConverter.hpp"

#include <algorithm>

MixConverter::MixConverter(Params params)
{
    if (params.first < 1)
    {
        // throw exception about invalid id for mix
        throw std::exception();
    }
    if (params.second < 0)
    {
        // throw exception about invalid second start
        throw std::exception();
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

