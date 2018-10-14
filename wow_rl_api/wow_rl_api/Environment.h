#pragma once
#include <vector>
#include "MemoryAction.h"

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

	class Square {
	public:

		int state;
		std::vector<int> neighbours;
		float pos_x;
		float pos_y;

		Square() {

		}

		Square(int _state, std::vector<int> _neighbours, float _pos_x, float _pos_y)
		{
			state = _state;
			neighbours = _neighbours;
			pos_x = _pos_x;
			pos_y = _pos_y;
		}

	};

public:
	Environment();

	StepReturn Step(int action);
	int Reset();	
	int GetCloseState();

private:
	void SetGridIndex(int state);
	std::vector<std::vector<Environment::Square>> CreateGrid();
	void UpdateGridIndex(int action);
};

