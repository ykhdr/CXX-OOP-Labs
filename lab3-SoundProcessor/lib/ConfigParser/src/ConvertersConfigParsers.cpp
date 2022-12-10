#include "ConvertersConfigParsers.hpp"

ConverterParams MuteConverterParser::parseConverterConfig(const std::string &&line)
{
    ConverterParams params {};

    std::string::size_type firstParamPos = line.find(' ');

    if (firstParamPos == std::string::npos)
    {
        throw std::invalid_argument("bad config argument for mute converter");
    }

    params.firstParam_ = std::stoi(line.substr(0, firstParamPos));
    params.secondParam_ = std::stoi(line.substr(firstParamPos));

    return params;
}

ConverterParams MixConverterParser::parseConverterConfig(const std::string &&line)
{
    ConverterParams params {};

    std::string::size_type firstParamPos = line.find(' ');

    if (firstParamPos == std::string::npos || line[0] != '$')
    {
        throw std::invalid_argument("bad config argument for mix converter");
    }

    params.firstParam_ = std::stoi(line.substr(1, firstParamPos)) - 1;
    params.secondParam_ = std::stoi(line.substr(firstParamPos));

    return params;
}

ConverterParams DoubleMixConverterParser::parseConverterConfig(const std::string &&line)
{
    ConverterParams params {};

    std::string::size_type firstParamPos = line.find(' ');

    if (firstParamPos == std::string::npos || line[0] != '$')
    {
        throw std::invalid_argument("bad first config argument for double mix converter");
    }


    params.firstParam_ = std::stoi(line.substr(1, firstParamPos)) - 1;

    std::string secondArg = line.substr(firstParamPos + 1);

    if (secondArg[0] != '$')
    {
        throw std::invalid_argument("bad second config argument for double mix converter");
    }

    params.secondParam_ = std::stoi(secondArg.substr(1)) - 1;

    return params;
}
