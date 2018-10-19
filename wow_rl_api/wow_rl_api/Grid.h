#pragma once
#include <vector>

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

	std::vector<int> terminal_state;
	int init_state;

	float start_x;
	float start_y;

	int size_x;
	int size_y;

	std::vector<float> init_states;

	Grid(std::vector<int> terminal_state, int init_state, float start_x, float start_y, int size_x, int size_y, std::vector<float> init_states);

	std::vector<std::vector<Grid::Square>> CreateGrid();

	int GetInitState() {
		return init_state;
	}

	void SetGridIndex(int state);
	void UpdateGridIndex(int action);

	Grid::Square GetSquare();
	Grid::Square GetSquare(int i, int j);

private:

	std::vector<std::vector<Grid::Square>> matrix;

	const float square_size = 5.0;
};

