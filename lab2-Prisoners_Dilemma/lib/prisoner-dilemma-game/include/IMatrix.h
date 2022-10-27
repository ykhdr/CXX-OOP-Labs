#pragma once

#include <vector>
#include <string>

class IMatrix
{
private:


public:
    virtual ~IMatrix() {}
    virtual void makeMatrix() = 0;
    virtual std::string getLine(int) const = 0;
};