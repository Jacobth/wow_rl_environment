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

#define TERMINATE_REWARD 100
#define STEP_REWARD -0.01
#define STUCK_REWARD -100
#define STATE_SIZE 3

Grid* grid;
MemoryAction memory;

float t_x;
float t_y;

Environment::Environment(std::string zone)
{
	Zones zones;
	grid = zones.GetGrid(zone);

	Grid::Point avg_point = grid->GetAveragePoint();
	t_x = avg_point.x;
	t_y = avg_point.y;
}

float Environment::StepReward(float dist)
{
	float distance = dist / 100;

	return STEP_REWARD * distance;
}

float* Environment::Step(int action)
{
	Grid::Square current_square = grid->GetSquare();

	int current_state = current_square.state;
	int next_state = current_square.neighbours[action];
	float reward = 0.0;
	bool done = false;
	bool stuck = false;

	if (grid->IsTerminal(memory.GetX(), memory.GetY())) {
		done = true;
		reward = TERMINATE_REWARD;
	}

	else if (next_state != -1) {

		grid->UpdateGridIndex(action);
		Grid::Square new_square = grid->GetSquare();

		stuck = memory.MoveToPoint(new_square.pos_x, new_square.pos_y, memory.GetZ());

		float dist = memory.GetDistance(t_x, t_y);
		reward = StepReward(dist);

		if (stuck)
		{
			reward = STUCK_REWARD - (dist * dist * 10);
			memory.Stop();

			done = true;
		}
	}

	else
	{
		reward = STUCK_REWARD;
		next_state = current_state;
	}

	float remaining_hp = memory.IsDead() ? 0 : this->GetRemainingHp(memory.GetMaxHp());
	reward += ((1 - remaining_hp) * STUCK_REWARD);

	float done_val = done ? 1.0 : 0.0;
	float dist_s = memory.GetDistance(t_x, t_y);

	float* vals = new float[5];

	vals[0] = (float)next_state;
	vals[1] = remaining_hp;
	vals[2] = dist_s;
	vals[3] = reward;
	vals[4] = done_val;

	delete vals;

	return vals;
}

float* Environment::Reset()
{
	memory.Stop();

	Grid::Point intit_point = grid->init;

	memory.SetPos(intit_point.x, intit_point.y, intit_point.z);

	int init = grid->GetInitState();

	grid->SetGridIndex(init);

	memory.ResetGame();

	float* vals = new float[3];

	vals[0] = (float)init;
	vals[1] = 1.0;
	vals[2] = memory.GetDistance(t_x, t_y);

	delete vals;

	return vals;
}

int Environment::GetActionSize()
{
	return sizeof(grid->GetSquare().neighbours[0]);
}

int Environment::GetStateSize()
{
	return STATE_SIZE;
}

float Environment::GetRemainingHp(float hp)
{
	return ((float)memory.GetHp() / hp);
}

int Environment::GetCloseState()
{
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

	float* Reset(Environment* env) { return env->Reset(); }
	float* Step(Environment* env, int action) { return env->Step(action); }
	int GetStateSize(Environment* env) { return env->GetStateSize(); }
	int GetActionSize(Environment* env) { return env->GetActionSize(); }
}