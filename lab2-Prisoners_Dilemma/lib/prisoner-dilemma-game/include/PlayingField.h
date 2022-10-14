#pragma once

#include "MoveMatrix.h"
#include "ResultMatrix.h"

class PlayingField
{
public:
	PlayingField();
	~PlayingField();
	
private: 
	MoveMatrix moveMatrix;
	ResultMatrix resultMatrix;	
};