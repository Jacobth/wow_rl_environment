#pragma once
#include <string>

class Environment
{

public:
	Environment(std::string zone);

	float* Step(int action);
	int Reset();
	int GetCloseState();

private:

	float GetRemainingHp(float hp);
};

