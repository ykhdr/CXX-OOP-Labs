#pragma once

#include "ConverterCreator.hpp"
#include <vector>
/*
 * КОНФИГ ПАРСЕР ВЫДАЕТ НА ВЫХОДЕ СТУКТУРУ
 * ConfigParams = std::vector<std::pair<CONVERTER_CRETOR_I, PARAMS>>,
 * Где PARAMS = std::pair<int(param1),int(param2)>
 * CONVERTER_CREATOR - shared_ptr на конвертер нужный
 * */


using ConfigParams = std::vector<std::pair<std::string,Params>>;

// Надо реализовать pipeline
// что если создать класс, который будет принимать выходной файл в себя

// 

class ConfigParser
{
private:
    std::ifstream configFile_;

    ConfigParams config_;

    void readConfig();

public:
    ConfigParser(const std::string& configPath);

    ConfigParams getConfig();
};