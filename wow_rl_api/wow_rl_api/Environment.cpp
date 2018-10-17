#include "stdafx.h"
#include "Environment.h"

Environment::Environment(std::string zone)
{
	Zones zones;
	grid = zones.GetGrid(zone);
}

Environment::StepReturn Environment::Step(int action) {

	std::cout << "new step" << std::endl;

	Grid::Square current_square = grid->GetSquare();

	int next_state = current_square.neighbours[action];
	float reward = 0.0;
	bool done = false;
	bool stuck = false;

	if (next_state == grid->terminal_state) {
		done = true;
		reward = 10.0;
	}

	else if (next_state != -1) {

		grid->UpdateGridIndex(action);
		Grid::Square new_square = grid->GetSquare();

		stuck = memory.MoveToPoint(new_square.pos_x, new_square.pos_y, grid->init_states[2]);

		reward = -1.0;

		if (stuck)
		{
			std::cout << "missed next state" << std::endl;

			reward = -1000000.0;
			memory.Stop();

			done = true;
		}
	}

	return Environment::StepReturn(next_state, reward, done);
}

int Environment::Reset() {

	memory.Stop();

	std::this_thread::sleep_for(std::chrono::milliseconds(300));

	float x = grid->init_states[0];
	float y = grid->init_states[1];
	float z = grid->init_states[2];

	memory.SetPos(x, y, z);

	std::this_thread::sleep_for(std::chrono::milliseconds(300));

	int init = grid->init_state;

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