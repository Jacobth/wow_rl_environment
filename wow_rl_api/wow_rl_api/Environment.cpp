#include "stdafx.h"
#include "Environment.h"
#include "Zones.h"
#include "MemoryAction.h"
#include "Grid.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <iostream>

Grid* grid;
MemoryAction memory;

Environment::Environment(std::string zone)
{
	Zones zones;
	grid = zones.GetGrid(zone);
}

float Environment::GetRemainingHp(int hp) {

	return ((float)memory.GetHp() / hp);
}

float* Environment::Step(int action) {

	//std::cout << "new step" << std::endl;

	Grid::Square current_square = grid->GetSquare();

	int current_state = current_square.state;
	int next_state = current_square.neighbours[action];
	float reward = 0.0;
	bool done = false;
	bool stuck = false;

	int init_hp = memory.GetHp();

	std::vector<int> terminal_states = grid->terminal_state;

	if (std::find(terminal_states.begin(), terminal_states.end(), next_state) != terminal_states.end()) {
		done = true;
		reward = 100000;
		//std::cout << "terminal state" << std::endl;
	}

	else if (next_state != -1) {

		grid->UpdateGridIndex(action);
		Grid::Square new_square = grid->GetSquare();

		stuck = memory.MoveToPoint(new_square.pos_x, new_square.pos_y, grid->init_states[2]);

		reward = -1.0;

		if (stuck)
		{
			//std::cout << "missed next state" << std::endl;
			reward = -1000000;
			memory.Stop();

			done = true;
		}
	}

	//We reached the end of the grid
	else {
		reward = -100;
		next_state = current_state;
	}

	float remaining_hp = memory.IsDead() ? 0 : GetRemainingHp(init_hp);
	reward += (1 - remaining_hp) * -10000;

	float done_val = done ? 1.0 : 0.0;

	float* vals = new float[4];

	vals[0] = (float)next_state;
	vals[1] = remaining_hp;
	vals[2] = reward;
	vals[3] = done_val;

	delete vals;

	return vals;
}

int Environment::Reset() {

	memory.Stop();

	//std::this_thread::sleep_for(std::chrono::milliseconds(300));

	float x = grid->init_states[0];
	float y = grid->init_states[1];
	float z = grid->init_states[2];

	memory.SetPos(x, y, z);

	//std::this_thread::sleep_for(std::chrono::milliseconds(300));

	int init = grid->GetInitState();

	grid->SetGridIndex(init);

	return init;
}

int Environment::GetCloseState() {

	MemoryAction mem;

	float min_distance = std::numeric_limits<float>::infinity();
	int min_state = 0;

	float x = 0;
	float y = 0;

	for (int i = 0; i < grid->size_y; i++) {

		//std::cout << "New y:" << i << '\n' << std::endl;

		for (int j = 0; j < grid->size_x; j++) {

			Grid::Square square = grid->GetSquare(i, j);

			float dist = mem.GetDistance(square.pos_x, square.pos_y);

			if (dist < min_distance) {
				min_distance = dist;
				min_state = square.state;

				x = square.pos_x;
				y = square.pos_y;
			}
		}
	}

	std::cout << "x:" << x << std::endl;
	std::cout << "y:" << y << std::endl;

	return min_state;
}

extern "C" {

	Environment* Env_new() { return new Environment("elwynn"); }

	int Reset(Environment* env) { return env->Reset(); }
	float* Step(Environment* env, int action) { return env->Step(action); }

	//const char* GetS(Foo* foo) { return foo->getS(); }
}