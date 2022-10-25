#include "Factory.h"

//#include "DefaultStrategy.h"
#include "../strategies/include/SimpleStrategy.h"

Factory &Factory::getInstance()
{
    static Factory instance;
    return instance;
}

void Factory::registerCreator(std::string strategy_name, std::shared_ptr<ICreator> creator)
{
	factoryMap_.insert({std::move(strategy_name), std::move(creator)}); //TODO: прочитать про move семантику и понять почему не работает
}

std::shared_ptr<IStrategy> Factory::create(const std::string & strategy_name)
{
	auto it = factoryMap_.find(strategy_name);
	if (it == factoryMap_.end())
	{
		return nullptr;
	}

	return it->second->create();
}


