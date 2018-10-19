#pragma once
#include "Grid.h"
#include <map>
#include <string>
#include <vector>

class Zones
{
public:
	Zones();

	Grid * GetGrid(std::string zone);

private:

	std::vector<float> GetPositionVector(float x, float y, float z);
	std::map<std::string, Grid*> zones;
};

