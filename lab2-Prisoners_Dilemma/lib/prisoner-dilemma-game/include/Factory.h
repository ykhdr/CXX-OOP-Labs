#pragma once

#include "IStrategy.h"
#include <memory>

class Factory
{
public:
	virtual ~Factory(){}
	virtual std::unique_ptr<IStrategy> create() = 0;
};