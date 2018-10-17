#include "stdafx.h"
#include "Zones.h"

Zones::Zones()
{
	// TERMINAL_STATE, INIT_STATE, START_X, START_Y, SIZE_X, SIZE_Y, Position vector with start x,y and z coordinates
	zones.insert(std::make_pair("elwynn", new Grid(1158, 351, -2, -8940, 41, 31, GetPositionVector(-115, -8980, 84.5))));
	zones.insert(std::make_pair("eversong", new Grid(7484, 1180, -5960, 10400, 100, 80, GetPositionVector(-6360, 10345, 34.5))));
}

std::vector<float> Zones::GetPositionVector(float x, float y, float z) {

	float intit_states[] = { x, y, z };
	std::vector<float> intit_states_v(intit_states, intit_states + sizeof(intit_states) / sizeof(intit_states[0]));

	return intit_states_v;
}

Grid * Zones::GetGrid(std::string zone) {
	return zones[zone];
}
