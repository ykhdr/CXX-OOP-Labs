#pragma once

#include "IConverter.hpp"


class MuteConverter : public IConverter
{
private:
    int secStart_;

    int secEnd_;

    int currentSec_ = 0;

public:
    MuteConverter(Params);

    void convert(SampleBuffer &outputSample, SampleVector &inputSamples) override;
};