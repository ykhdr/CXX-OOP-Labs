#pragma once

#include "IStrategy.h"

#include <map>
#include <memory>

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

class Factory
{
private:
    Factory() = default;

    Factory(const Factory &)
    {}

    //Factory& operator=(Factory&) {}

    std::map<std::string, std::shared_ptr<ICreator>> factoryMap_;

public:
    static Factory &getInstance();

    void registerCreator(std::string strategy_name, std::shared_ptr<ICreator> creator);

    std::shared_ptr<IStrategy> create(const std::string &strategy_name);

};