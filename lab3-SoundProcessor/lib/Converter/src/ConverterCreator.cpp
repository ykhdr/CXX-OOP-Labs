#include "ConverterCreator.hpp"

#include "MuteConverter.hpp"
#include "MixConverter.hpp"

ConverterPtr MuteConverterCreator::create(ConverterParams params) const
{
    return std::make_shared<MuteConverter>(params);
}

ConverterPtr MixConverterCreator::create(ConverterParams params) const
{
    return std::make_shared<MixConverter>(params);
}
