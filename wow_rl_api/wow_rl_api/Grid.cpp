#include "stdafx.h"
#include "Grid.h"
#include <algorithm>

#define UP_ACTION 0
#define DOWN_ACTION 1
#define LEFT_ACTION 2
#define RIGHT_ACTION 3

#define OBJECTS_X 2
#define OBJECTS_Y 14

Grid::Grid(Point terminal_start, Point terminal_end, Point init, int init_state, int size_x, int size_y)
{
	this->terminal_start = terminal_start;
	this->terminal_end = terminal_end;
	this->init_state = init_state;
	this->init = init;
	this->size_x = size_x;
	this->size_y = size_y;
	this->init = init;

	matrix = CreateGrid();
	objects = InitObjects();
}

int current_x = 0;
int current_y = 0;

int init_x = 0;
int init_y = 0;

std::vector<std::vector<Grid::Square>> Grid::CreateGrid()
{
	std::vector<std::vector<Square>> matrix(size_y, std::vector<Square>(size_x));

	int state = 0;
	float x = init.x;
	float y = init.y;

	for (int i = 0; i < size_y; i++) {

		x = init.x;

		for (int j = 0; j < size_x; j++) {

			int up = i == 0 ? -1 : state - size_x;
			int down = i == size_y - 1 ? -1 : state + size_x;
			int left = j == 0 ? -1 : state - 1;
			int right = j == size_x - 1 ? -1 : state + 1;

			std::vector<int> neighbours_v = { up, down, left, right };

			matrix[i][j] = Square(state, neighbours_v, x, y);

			x -= square_size;

			if (state == init_state) {
				current_y = i;
				current_x = j;

				init_x = current_x;
				init_y = current_y;
			}

			state++;
		}
		y -= square_size;
	}

	return matrix;
}

void Grid::SetGridIndex() {
	current_x = init_x;
	current_y = init_y;
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

std::vector<std::vector<Grid::Point>> Grid::InitObjects()
{
	std::vector<std::vector<Point>> matrix(OBJECTS_Y, std::vector<Point>(OBJECTS_X));

	//1
	matrix[0][0] = Point(132.7, -9389);
	matrix[0][1] = Point(120.8, -9399);

	//2
	matrix[1][0] = Point(119, -9418.8);
	matrix[1][1] = Point(110, -9426);

	//3
	matrix[2][0] = Point(110.8, -9418.8);
	matrix[2][1] = Point(117.9, -9426.3);

	//4
	matrix[3][0] = Point(104, -9410);
	matrix[3][1] = Point(98.5, -9414);

	//5
	matrix[4][0] = Point(102.46, -9404);
	matrix[4][1] = Point(96.3, -9416.6);

	//6
	matrix[5][0] = Point(90.4, -9394);
	matrix[5][1] = Point(81.5, -9407.3);

	//7
	matrix[6][0] = Point(87.1, -9389.4);
	matrix[6][1] = Point(73, -9393.7);

	//8
	matrix[7][0] = Point(71.5, -9422.7);
	matrix[7][1] = Point(31.9, -9407.2);

	//9
	matrix[8][0] = Point(143.1, -9454.4);
	matrix[8][1] = Point(130.8, -9468.2);

	//10
	matrix[9][0] = Point(134.1, -9472.6);
	matrix[9][1] = Point(118.7, -9475.3);

	//11
	matrix[10][0] = Point(108, -9471.3);
	matrix[10][1] = Point(74.2, -9447.2);

	//12
	matrix[11][0] = Point(129.4, -9446.9);
	matrix[11][1] = Point(120.5, -9441.9);

	//13
	matrix[12][0] = Point(116.3, -9430.2);
	matrix[12][1] = Point(108.2, -9437.2);

	//14
	matrix[13][0] = Point(101, -9436.6);
	matrix[13][1] = Point(121.15, -9437.5);

	return matrix;
}

bool Grid::IsTerminal(float player_x, float player_y)
{
	bool within_x = (player_x >= terminal_start.x) && (player_x <= terminal_end.x);
	bool within_y = (player_y >= terminal_start.y) && (player_y <= terminal_end.y);

	return within_x && within_y;
}

bool Grid::IsStuck(float player_x, float player_y)
{

	for (int i = 0; i < OBJECTS_Y; i++) {

		float x1 = objects[i][0].x;
		float x2 = objects[i][1].x;

		float y1 = objects[i][0].y;
		float y2 = objects[i][1].y;

		float start_x = std::min(x1, x2);
		float end_x = start_x == x1 ? x2 : x1;

		float start_y = std::min(y1, y2);
		float end_y = start_y == y1 ? y2 : y1;

		bool within_x = (player_x >= start_x) && (player_x <= end_x);
		bool within_y = (player_y >= start_y) && (player_y <= end_y);

		if (within_x && within_y)
			return true;
	}

	return false;
}

Grid::Point Grid::GetAveragePoint()
{
	float avg_x = (this->terminal_start.x + this->terminal_end.x) / 2;
	float avg_y = (this->terminal_start.y + this->terminal_end.y) / 2;

	return Point(avg_x, avg_y);
}