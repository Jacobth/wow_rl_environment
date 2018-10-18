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

		std::vector<float> next_state;
		double reward;
		bool done;

		StepReturn(std::vector<float> next_state, double reward, bool done)
		{
			this->next_state = next_state;
			this->reward = reward;
			this->done = done;
		}

	};

	Grid* grid;
	MemoryAction memory;

	Environment(std::string zone);

	StepReturn Step(int action);
	int Reset();
	int GetCloseState();


private:
	float GetRemainingHp(int hp);
};

