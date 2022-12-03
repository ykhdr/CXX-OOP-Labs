#pragma once

#include <fstream>
#include <memory>

#include "WAVUtil.hpp"

class IConverter;

using Params = std::pair<int,int>;
using ConverterType = std::shared_ptr<IConverter>;

using ConverterPipeline = std::vector<ConverterType>;

// TODO: при создании конвертера сразу же инициализировать его параметры и передавтаь в него два сэмпла:
// буферный выходной рабочий и вектор сэмплов
// при


class IConverter
{
public:
    ~IConverter() = default;

    virtual void convert(SampleBuffer &outputSample, SampleVector &inputSamples) = 0;
};

