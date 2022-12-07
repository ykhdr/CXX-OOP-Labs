#pragma once

#include "IConverter.hpp"

#include "WAVUtil.hpp"

class DoubleMixConverter : public IConverter
{
private:
    int idFirstWAVForMix_;

    int idSecondWAVFormMix_;

public:
    DoubleMixConverter(ConverterParams);

    void convert(SampleBuffer &outputSample, SampleVector &inputSamples) override;
};

