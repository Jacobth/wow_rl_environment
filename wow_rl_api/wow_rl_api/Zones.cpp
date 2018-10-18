#include "stdafx.h"
#include "Zones.h"

Zones::Zones()
{
	// TERMINAL_STATE, INIT_STATE, START_X, START_Y, SIZE_X, SIZE_Y, Position vector with start x,y and z coordinates
	//zones.insert(std::make_pair("elwynn", new Grid(1158, 351, -2, -8940, 41, 31, GetPositionVector(-115, -8980, 84.5))));
	
	std::vector<int> terminal_states = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 81, 82, 289, 355 };

	zones.insert(std::make_pair("elwynn", new Grid(terminal_states, 3930, 400, -9150, 69, 71, GetPositionVector(70, -9430, 57))));
	//zones.insert(std::make_pair("eversong", new Grid(7484, 1180, -5960, 10400, 100, 80, GetPositionVector(-6360, 10345, 34.5))));
}

std::vector<float> Zones::GetPositionVector(float x, float y, float z) {

	float intit_states[] = { x, y, z };
	std::vector<float> intit_states_v(intit_states, intit_states + sizeof(intit_states) / sizeof(intit_states[0]));

	return intit_states_v;
}

std::vector<int> Zones::GetStateVector(int states[]) {

	std::vector<int> intit_states_v(states, states + sizeof(states) / sizeof(states[0]));

	return intit_states_v;
}

Grid * Zones::GetGrid(std::string zone) {
	return zones[zone];
}
