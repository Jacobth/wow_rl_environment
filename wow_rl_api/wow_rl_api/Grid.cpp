#include "stdafx.h"
#include "Grid.h"

Grid::Grid(int terminal_state, int init_state, float start_x, float start_y, int size_x, int size_y, std::vector<float> init_states)
{
	this->terminal_state = terminal_state;
	this->init_state = init_state;
	this->start_x = start_x;
	this->start_y = start_y;
	this->size_x = size_x;
	this->size_y = size_y;
	this->init_states = init_states;

	matrix = CreateGrid();
}

int current_x = 0;
int current_y = 0;

std::vector<std::vector<Grid::Square>> Grid::CreateGrid()
{
	std::vector<std::vector<Square>> matrix(size_y, std::vector<Square>(size_x));

	int state = 0;
	float x = start_x;
	float y = start_y;

	for (int i = 0; i < size_y; i++) {

		x = start_x;

		for (int j = 0; j < size_x; j++) {

			int up = i == 0 ? -1 : state - size_x;
			int down = i == size_x - 1 ? -1 : state + size_x;
			int left = j == 0 ? -1 : state - 1;
			int right = j == size_x - 1 ? -1 : state + 1;

			int neighbours[] = { up, down, left, right };
			std::vector<int> neighbours_v(neighbours, neighbours + sizeof(neighbours) / sizeof(neighbours[0]));

			matrix[i][j] = Square(state, neighbours_v, x, y);

			x -= square_size;

			if (state == init_state) {
				current_y = i;
				current_x = j;
			}

			state++;
		}
		y -= square_size;
	}

	return matrix;
}

void Grid::SetGridIndex(int state) {

	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {

			int tmp_state = matrix[i][j].state;

			if (state == tmp_state) {
				current_y = i;
				current_x = j;
				return;
			}
		}
	}
}

void Grid::UpdateGridIndex(int action) {

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

Grid::Square Grid::GetSquare() {
	return matrix[current_y][current_x];
}

Grid::Square Grid::GetSquare(int i, int j) {
	return matrix[i][j];
}
