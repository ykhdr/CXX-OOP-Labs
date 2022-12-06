#include "ConfigParser.hpp"
#include "ConfigParserExceptions.hpp"

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

ConfigParser::ConfigParser(const std::string& configPath_)
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

    while (configFile_ >> line)
    {
        if (line == "#")
        {
            while (!configFile_.eof() && configFile_.get() != '\n');
            continue;
        }

        config_.push_back(std::pair<std::string, ConverterParams>());

        config_[config_.size()-1].first = line;

        for (int i = 0; i < 2; ++i)
        {
            if (configFile_.eof())
            {
                // exception about file's end / incorrect configFile
                throw ConfigExceptions::BadReadingFile(configFilePath_);
            }

            configFile_ >> line;

            if(line[0] == '$')
            {
                line = line.substr(1);
            }

            if (i == 0)
            {
                config_[config_.size()-1].second.first = std::stoi(line);
            }
            else
            {
                config_[config_.size()-1].second.second = std::stoi(line);
            }
        }
    }
}

ConfigParamLine ConfigParser::getConfig()
{
    return config_;
}