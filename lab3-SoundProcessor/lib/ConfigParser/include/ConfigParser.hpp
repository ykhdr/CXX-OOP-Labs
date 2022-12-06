#pragma once

#include "ConverterCreator.hpp"
#include <vector>
/*
 * КОНФИГ ПАРСЕР ВЫДАЕТ НА ВЫХОДЕ СТУКТУРУ
 * ConfigParamLine = std::vector<std::pair<CONVERTER_CRETOR_I, PARAMS>>,
 * Где PARAMS = std::pair<int(param1),int(param2)>
 * CONVERTER_CREATOR - shared_ptr на конвертер нужный
 * */


using ConfigParamLine = std::vector<std::pair<std::string,ConverterParams>>;

// Надо реализовать pipeline
// что если создать класс, который будет принимать выходной файл в себя

// 

class ConfigParser
{
private:
    std::ifstream configFile_;

    std::string configFilePath_;

    ConfigParamLine config_;

    void readConfig();

public:
    ConfigParser(const std::string& configPath);

    ConfigParamLine getConfig();
};