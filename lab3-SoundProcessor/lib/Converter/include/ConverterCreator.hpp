#pragma once

#include <memory>

#include "IConverter.hpp"

class ConverterCreator
{
public:
    virtual ~ConverterCreator() = default;

    virtual ConverterType create(Params params) const = 0;
};


class MuteConverterCreator : public ConverterCreator
{
public:
    ConverterType create(Params params) const override;
};

class MixConverterCreator : public ConverterCreator
{
public:
    ConverterType create(Params params) const override;
};