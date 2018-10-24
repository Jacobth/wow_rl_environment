#include "stdafx.h"
#include "EnvSimulator.h"
#include "Zones.h"
#include "Grid.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <iostream>
#include <thread>
#include <math.h>
#include <string>

#define _USE_MATH_DEFINES

#define TERMINATE_REWARD 100
#define STEP_REWARD -0.01
#define STUCK_REWARD -100
#define STATE_SIZE 5

Grid* grid_sim;

float t_x_sim;
float t_y_sim;

float player_x;
float player_y;

EnvSimulator::EnvSimulator()
{
	Zones zones;
	grid_sim = zones.GetGrid("elwynn");

	Grid::Point avg_point = grid_sim->GetAveragePoint();
	t_x_sim = avg_point.x;
	t_y_sim = avg_point.y;

	player_x = grid_sim->init.x;
	player_y = grid_sim->init.y;
}

float* EnvSimulator::Step_sim(int action)
{
	Grid::Square current_square = grid_sim->GetSquare();

	int current_state = current_square.state;
	int next_state = current_square.neighbours[action];

	float tmp_pos_x = player_x;
	float tmp_pos_y = player_y;

	player_x = current_square.pos_x;
	player_y = current_square.pos_y;

	float reward = 0.0;
	bool done = false;

	if (grid_sim->IsTerminal(player_x, player_y))
	{
		done = true;
		reward = TERMINATE_REWARD;
	}

	else if (next_state != -1)
	{
		grid_sim->UpdateGridIndex(action);
		Grid::Square new_square = grid_sim->GetSquare();

		bool stuck = grid_sim->IsStuck(player_x, player_y);

		float dist = EnvSimulator::GetDistance(player_x, player_y);
		reward = StepRewardSim(dist);

		if (stuck)
		{
			reward = STUCK_REWARD - (dist * dist * 10);
			done = true;
		}
	}

	else
	{
		player_x = tmp_pos_x;
		player_y = tmp_pos_y;

		reward = STUCK_REWARD * 100000;
		next_state = current_state;
		done = true;
	}

	float remaining_hp = 1;
	reward += ((1 - remaining_hp) * STUCK_REWARD);

	float done_val = done ? 1.0 : 0.0;

	float* vals = new float[7];

	vals[0] = player_x;
	vals[1] = player_y;
	vals[2] = player_x - t_x_sim;
	vals[3] = player_y - t_y_sim;
	vals[4] = remaining_hp;
	vals[5] = reward;
	vals[6] = done_val;

	delete vals;

	return vals;
}

float* EnvSimulator::Reset_sim()
{
	Grid::Point intit_point = grid_sim->init;

	player_x = intit_point.x;
	player_y = intit_point.y;

	int init = grid_sim->GetInitState();

	grid_sim->SetGridIndex();

	float* vals = new float[5];

	vals[0] = player_x;
	vals[1] = player_y;
	vals[2] = player_x - t_x_sim;
	vals[3] = player_y - t_y_sim;
	vals[4] = 1.0;

	delete vals;

	return vals;
}

float EnvSimulator::GetDistance(float x, float y)
{
	float a = t_x_sim - x;
	float b = t_y_sim - y;

	float distance = std::sqrt((a*a) + (b*b));

	return distance;
}

float EnvSimulator::StepRewardSim(float dist)
{
	float distance = dist / 100;

	return STEP_REWARD * distance;
}


extern "C" {

	EnvSimulator* Envs_new() { return new EnvSimulator(); }

	float* ResetSim(EnvSimulator* env) { return env->Reset_sim(); }
	float* StepSim(EnvSimulator* env, int action) { return env->Step_sim(action); }
}