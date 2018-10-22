#include "stdafx.h"
#include "Grid.h"

#define UP_ACTION 0
#define DOWN_ACTION 1
#define LEFT_ACTION 2
#define RIGHT_ACTION 3

Grid::Grid(Point terminal_start, Point terminal_end, int init_state, float start_x, float start_y, int size_x, int size_y, Point init)
{
	this->terminal_start = terminal_start;
	this->terminal_end = terminal_end;
	this->init_state = init_state;
	this->start_x = start_x;
	this->start_y = start_y;
	this->size_x = size_x;
	this->size_y = size_y;
	this->init = init;

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

Grid::Square Grid::GetSquare(int state) {

	for (int i = 0; i < sizeof(matrix); i++) {
		for (int j = 0; j < sizeof(matrix[0]); j++) {

			Square s = matrix[i][j];

			if (state == s.state)
				return s;
		}
	}

	return Square();
}

bool Grid::IsTerminal(float player_x, float player_y)
{
	bool within_x = (player_x >= terminal_start.x) && (player_x <= terminal_end.x);
	bool within_y = (player_y >= terminal_start.y) && (player_y <= terminal_end.y);

	return within_x && within_y;
}

Grid::Point Grid::GetAveragePoint()
{
	float avg_x = (this->terminal_start.x + this->terminal_end.x) / 2;
	float avg_y = (this->terminal_start.y + this->terminal_end.y) / 2;

	return Point(avg_x, avg_y);
}