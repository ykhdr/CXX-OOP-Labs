#pragma once

#include <vector>
#include <string_view>

class Matrix
{
private:


public:
	virtual ~Matrix(){}
    virtual void makeMatrix() {}
    //virtual std::vector<std::string_view> getLine(int height_) {}
};