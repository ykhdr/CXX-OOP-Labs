#include "ConfigParser.hpp"
#include "ConfigParserExceptions.hpp"

class ConverterParser
{
public:
    virtual ConverterParams parseConverterConfig(const std::string &&line) = 0;
};

class MuteConverterParser : virtual public ConverterParser
{
public:
    ConverterParams parseConverterConfig(const std::string &&line) override;
};

class MixConverterParser : virtual public ConverterParser
{
public:
    ConverterParams parseConverterConfig(const std::string &&line) override;
};

class DoubleMixConverterParser : virtual public ConverterParser
{
public:
    ConverterParams parseConverterConfig(const std::string &&line) override;
};