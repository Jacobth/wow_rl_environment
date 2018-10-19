#pragma once
#include <vector>
#include "MemoryAction.h"
#include "Grid.h"
#include <algorithm>
#include <iterator>
#include <limits>
#include "Zones.h"
#include <string>

class Environment
{

public:
	Environment(std::string zone);

	float* Step(int action);
	int Reset();
	int GetCloseState();


private:
	Grid* grid;
	MemoryAction memory;

	float GetRemainingHp(int hp);
};

