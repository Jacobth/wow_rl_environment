#include "stdafx.h"
#include "Zones.h"

Zones::Zones()
{
	// TERMINAL_STATE, INIT_STATE, START_X, START_Y, SIZE_X, SIZE_Y, Position vector with start x,y and z coordinates

	zones.insert(std::make_pair("elwynn", new Grid(Grid::Point(55, -9480), Grid::Point(74, -9440), Grid::Point(135, -9375, 61.8), 0, 22, 26)));
	//zones.insert(std::make_pair("elwynn", new Grid(Grid::Point(55, -9480), Grid::Point(74, -9440), 706, 185, -9315, 27, 38, Grid::Point(165, -9445, 55))));
}

Grid * Zones::GetGrid(std::string zone) {
	return zones[zone];
}
