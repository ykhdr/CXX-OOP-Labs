#pragma once

#include <vector>
#include <string>

class IMatrix
{
public:
    virtual ~IMatrix() {}
    virtual std::string getLine(int) const = 0;
};