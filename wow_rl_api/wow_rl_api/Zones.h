#pragma once
#include "Grid.h"
#include <map>
#include <string>
#include <vector>

class Zones
{
public:
	Zones();

	Grid * Zones::GetGrid(std::string zone);

private:

	std::vector<float> GetPositionVector(float x, float y, float z);
	std::vector<int> GetStateVector(int states[]);
	std::map<std::string, Grid*> zones;
};

