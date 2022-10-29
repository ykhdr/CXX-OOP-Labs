#include "../include/StrategyFactory.h"

StrategyFactory &StrategyFactory::getInstance()
{
    static StrategyFactory instance;
    return instance;
}

void StrategyFactory::registerCreator(std::string strategy_name, std::shared_ptr<ICreator> creator)
{
	factoryMap_.insert({std::move(strategy_name), std::move(creator)});
}

std::shared_ptr<IStrategy> StrategyFactory::create(const std::string & strategy_name)
{
	auto it = factoryMap_.find(strategy_name);
	if (it == factoryMap_.end())
	{
		return nullptr;
	}

	return it->second->create();
}


