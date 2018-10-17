#pragma once
#include <vector>

#define UP_ACTION 0
#define DOWN_ACTION 1
#define LEFT_ACTION 2
#define RIGHT_ACTION 3

class Grid
{
public:

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

	const float square_size = 5.0;

	int terminal_state;
	int init_state;

	float start_x;
	float start_y;

	int size_x;
	int size_y;

	std::vector<float> init_states;

	Grid(int terminal_state, int init_state, float start_x, float start_y, int size_x, int size_y, std::vector<float> init_states);

	std::vector<std::vector<Grid::Square>> CreateGrid();

	void SetGridIndex(int state);
	void UpdateGridIndex(int action);

	Grid::Square GetSquare();
	Grid::Square GetSquare(int i, int j);

	std::vector<std::vector<Grid::Square>> matrix;
};
