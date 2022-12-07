#include "DoubleMixConverter.hpp"

#include "ConverterException.hpp"

DoubleMixConverter::DoubleMixConverter(ConverterParams params)
{
    if (params.first < 1)
    {
        throw ConverterExceptions::BadFirstArgumentDoubleMixConverter(params.first);
    }
    if (params.second < 1)
    {
        throw ConverterExceptions::BadSecondArgumentDoubleMixConverter(params.second);
    }
    if (params.second == params.first)
    {
        throw ConverterExceptions::RecurringSecondArgumentDoubleMixConverter(params.second);
    }

    idFirstWAVForMix_ = params.first;
    idSecondWAVFormMix_ = params.second;
}

void DoubleMixConverter::convert(SampleBuffer &outputSample, SampleVector &inputSamples)
{
    for (int i = 0; i < outputSample.size(); ++i)
    {
        outputSample[i] =
                outputSample[i] / 3
                + inputSamples[idFirstWAVForMix_ -1][i] / 3
                + inputSamples[idSecondWAVFormMix_ -1][i] / 3;
    }
}