#include "stdafx.h"
#include "Zones.h"

Zones::Zones()
{
	// TERMINAL_STATE, INIT_STATE, START_X, START_Y, SIZE_X, SIZE_Y, Position vector with start x,y and z coordinates

	zones.insert(std::make_pair("elwynn", new Grid(Grid::Point(55, -9480), Grid::Point(74, -9440), 109, 185, -9315, 27, 38, Grid::Point(180, -9335, 61.8))));
}

Grid * Zones::GetGrid(std::string zone) {
	return zones[zone];
}
