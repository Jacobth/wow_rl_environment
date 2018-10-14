#include "stdafx.h"
#include "Environment.h"
#include <algorithm>
#include <iterator>
#include <limits>

#define TERMINAL_STATE 961
#define INIT_STATE 53

#define START_X 415.0
#define START_Y -8980.0

#define END_X -385.0
#define END_Y -9480.0

#define SQUARE_SIZE 10.0

#define UP_ACTION 0
#define DOWN_ACTION 1
#define LEFT_ACTION 2
#define RIGHT_ACTION 3

#define INIT_X -115.0
#define INIT_Y -8980.0 
#define INIT_Z 85.0

#define SIZE_X 80
#define SIZE_Y 60

MemoryAction memory;

int current_state;
int current_y;
int current_x;

std::vector<std::vector<Environment::Square>> grid;

Environment::Environment()
{
	grid = CreateGrid();
	current_state = INIT_STATE;
	//SetGridIndex(current_state);
}

Environment::StepReturn Environment::Step(int action) {

	Square current_square = grid[current_y][current_x];

	current_state = current_square.state;

	int next_state = current_square.neighbours[action];
	float reward = 0.0;
	bool done = false;

	bool stuck = false;

	if (next_state == TERMINAL_STATE) {
		done = true;
		reward = 10.0;
	}

	else if (next_state != -1) {

		UpdateGridIndex(action);

		Square new_square = grid[current_y][current_x];

		stuck = memory.Move(action, new_square.pos_x, new_square.pos_y);

		reward = stuck ? -10.0 : -1.0;
	}

	else {
		next_state = current_state;
	}

	//next_state, reward, done
	current_state = next_state;

	return Environment::StepReturn(next_state, reward, done);
}

int Environment::Reset() {

	current_state = INIT_STATE;
	SetGridIndex(current_state);

	memory.SetPos(INIT_X, INIT_Y, INIT_Z);
	memory.SetAngle(0);

	return current_state;
}

std::vector<std::vector<Environment::Square>> Environment::CreateGrid()
{
	std::vector<std::vector<Environment::Square>> matrix(SIZE_Y, std::vector<Environment::Square>(SIZE_X));

	int state = 0;
	float x = START_X;
	float y = START_Y;

	for (int i = 0; i < SIZE_Y; i++) {

		x = START_X;

		for (int j = 0; j < SIZE_X; j++) {

			int up = i == 0 ? -1 : state - SIZE_X;
			int down = i == SIZE_X - 1 ? -1 : state + SIZE_X;
			int left = j == 0 ? -1 : state - 1;
			int right = j == SIZE_X - 1 ? -1 : state + 1;

			int neighbours[] = { up, down, left, right };
			std::vector<int> v(neighbours, neighbours + sizeof(neighbours) / sizeof(neighbours[0]));

			matrix[i][j] = Environment::Square(state, v, x, y);

			x -= SQUARE_SIZE;

			if (state == INIT_STATE) {
				current_y = i;
				current_x = j;
			}

			state++;
		}
		y -= SQUARE_SIZE;
	}

	return matrix;
}

void Environment::SetGridIndex(int state) {

	for (int i = 0; i < SIZE_Y; i++) {
		for (int j = 0; j < SIZE_X; j++) {

			int tmp_state = grid[i][j].state;

			if (state == tmp_state) {
				current_y = i;
				current_x = j;
				return;
			}
		}
	}
}

void Environment::UpdateGridIndex(int action) {

	switch (action)
	{
	case UP_ACTION:
		current_y--;
		break;

	case DOWN_ACTION:
		current_y++;
		break;

	case LEFT_ACTION:
		current_x--;
		break;

	case RIGHT_ACTION:
		current_x++;
		break;

	default:
		break;
	}
}

int Environment::GetCloseState() {

	MemoryAction mem;

	float min_distance = std::numeric_limits<float>::infinity();
	int min_state = 0;

	float x = 0;
	float y = 0;

	for (int i = 0; i < SIZE_Y; i++) {

		//std::cout << "New y:" << i << '\n' << std::endl;

		for (int j = 0; j < SIZE_X; j++) {

			Square square = grid[i][j];

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