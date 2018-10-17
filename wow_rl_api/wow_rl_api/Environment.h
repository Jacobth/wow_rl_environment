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
	class StepReturn {
	public:

		int next_state;
		double reward;
		bool done;

		StepReturn(int _next_state, double _reward, bool _done)
		{
			next_state = _next_state;
			reward = _reward;
			done = _done;
		}

	};

	Grid* grid;
	MemoryAction memory;

	Environment(std::string zone);
	
	StepReturn Step(int action);
	int Reset();
	int GetCloseState();
	
};

