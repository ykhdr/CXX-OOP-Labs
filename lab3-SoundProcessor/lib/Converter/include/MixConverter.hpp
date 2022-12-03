#pragma once

#include "IConverter.hpp"

#include "WAVUtil.hpp"

class MixConverter : public IConverter
{
private:
    int idWAVForMix_;

    int secStart_;

    int currentSec_ = 0;

public:
    MixConverter(Params);

    void convert(SampleBuffer &outputSample, SampleVector &inputSamples) override;
};
