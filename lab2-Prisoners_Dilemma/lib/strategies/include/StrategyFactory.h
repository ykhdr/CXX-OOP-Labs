#pragma once

#include <map>
#include <memory>

#include "IStrategy.h"
#include "DefaultStrategy.h"
#include "RandomStrategy.h"
#include "SimpleStrategy.h"
#include "SmartStrategy.h"
#include "PersonStrategy.h"

class ICreator
{
public:
    virtual ~ICreator() = default;

    virtual std::shared_ptr<IStrategy> create() = 0;
};

template<typename T>
class Creator : public ICreator
{
public:
    std::shared_ptr<IStrategy> create()
    {
        return std::make_shared<T>();
    }
};

class StrategyFactory
{
private:
    StrategyFactory() = default;

    StrategyFactory(const StrategyFactory &)
    {}

    std::map<std::string, std::shared_ptr<ICreator>> factoryMap_;

public:
    static StrategyFactory &getInstance();

    void registerCreator(std::string strategy_name, std::shared_ptr<ICreator> creator);

    std::shared_ptr<IStrategy> create(const std::string &strategy_name);

};