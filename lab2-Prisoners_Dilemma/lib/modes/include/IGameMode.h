#pragma once

#include <vector>
#include <memory>

#include "PlayingField.h"
#include "IStrategy.h"


class IGameMode
{

public:
    virtual void run() = 0;

    virtual ~IGameMode() = default;
};


