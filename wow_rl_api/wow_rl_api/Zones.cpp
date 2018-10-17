#include "stdafx.h"
#include "Zones.h"

#define TERMINAL_STATE 1158
#define INIT_STATE 351

#define START_X -2.0 //415.0
#define START_Y  -8940.0 //-8980.0

#define END_X -385.0
#define END_Y -9480.0

#define SQUARE_SIZE 5.0 //10.0

#define UP_ACTION 0
#define DOWN_ACTION 1
#define LEFT_ACTION 2
#define RIGHT_ACTION 3

#define INIT_X -115.0
#define INIT_Y -8980.0 
#define INIT_Z 84.5

#define SIZE_X 41 //80
#define SIZE_Y 31 //60


Zones::Zones()
{
	zones.insert(std::make_pair("elwynn", new Grid(1158, 351, -2.0, -8940.0, 41, 31, GetPositionVector(-115.0, -8980.0, 84.5))));
}

std::vector<float> Zones::GetPositionVector(float x, float y, float z) {

	float intit_states[] = { x, y, z };
	std::vector<float> intit_states_v(intit_states, intit_states + sizeof(intit_states) / sizeof(intit_states[0]));

	return intit_states_v;
}

Grid * Zones::GetGrid(std::string zone) {
	return zones[zone];
}
