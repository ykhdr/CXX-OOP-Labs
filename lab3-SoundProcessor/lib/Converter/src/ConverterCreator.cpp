#include "ConverterCreator.hpp"

#include "MuteConverter.hpp"
#include "MixConverter.hpp"



ConverterType MuteConverterCreator::create(Params params) const
{
    return std::make_shared<MuteConverter>(params);
}

ConverterType MixConverterCreator::create(Params params) const
{
    return std::make_shared<MixConverter>(params);
}
