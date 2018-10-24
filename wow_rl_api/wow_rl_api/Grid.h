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

	class Point {
	public:
		float x;
		float y;
		float z;

		Point() {

		}

		Point(float x, float y) {
			this->x = x;
			this->y = y;
		}

		Point(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

	};

	Point terminal_start;
	Point terminal_end;
	Point init;

	int init_state;

	int size_x;
	int size_y;

	Grid(Point terminal_start, Point terminal_end, Point init, int init_state, int size_x, int size_y);

	std::vector<std::vector<Grid::Square>> CreateGrid();

	int GetInitState() {
		return init_state;
	}

	void SetGridIndex();
	void UpdateGridIndex(int action);

	bool IsTerminal(float player_x, float player_y);

	Grid::Square GetSquare();
	Grid::Square GetSquare(int i, int j);
	Grid::Square GetSquare(int state);

	Grid::Point GetAveragePoint();

private:

	std::vector<std::vector<Grid::Square>> matrix;

	const float square_size = 5.0;
};

