#include "ConfigParser.hpp"
#include "ConfigParserExceptions.hpp"
#include "ConvertersConfigParsers.hpp"
#include <iostream>

/*
    # заглушить первые 30 секунд input1
    mute 0 30
    # смиксовать с input2, начиная с секунды 10
    mix $2 10
    # заглушить 3-ю минуту в миксованном потоке
    mute 120 180
    # применить ваш конвертер с нужными параметрами
    your_converter <parameters>
*/

ConfigParser::ConfigParser(const std::string &configPath_)
{
    configFile_.open(configPath_, std::ios_base::binary);

    if (!configFile_.good())
    {
        // exception about не открыт конфиг файл
        throw ConfigExceptions::BadOpeningConfig(configPath_);
    }

    configFilePath_ = std::move(configPath_);

    readConfig();
}

void ConfigParser::readConfig()
{
    std::string line;

    while (std::getline(configFile_, line, '\n'))
    {
        int i = 0;
        while (line[i] == ' ')
        {
            ++i;
        }
        if(i > 0)
        {
            line = line.substr(i);
        }

        if (line[0] == '#')
        {
            continue;
        }

        config_.push_back(ConfigParam());

        std::string::size_type posName = line.find(' ');
        if (posName == std::string::npos)
        {
            throw ConfigExceptions::BadReadingFile(configFilePath_);
        }

        config_.back().converterName_ = line.substr(0, posName);

        if (config_.back().converterName_ == "mute")
        {
            config_.back().converterParams_ =
                    MuteConverterParser().parseConverterConfig(std::move(line.substr(posName + 1)));
        }
        else if (config_.back().converterName_ == "mix")
        {
            config_.back().converterParams_ =
                    MixConverterParser().parseConverterConfig(std::move(line.substr(posName + 1)));

        }
        else if (config_.back().converterName_ == "dmix")
        {
            config_.back().converterParams_ =
                    DoubleMixConverterParser().parseConverterConfig(std::move(line.substr(posName + 1)));
        }
        else
        {
            throw std::invalid_argument("bad config arguments :" + line);
        }
    }
}

ConfigParamLine ConfigParser::getConfig()
{
    return config_;
}