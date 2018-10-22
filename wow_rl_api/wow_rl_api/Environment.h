#pragma once
#include <string>

class Environment
{

public:
	Environment(std::string zone);

	float* Step(int action);
	float* Reset();
	int GetCloseState();

	int GetStateSize();
	int GetActionSize();

private:
	float GetRemainingHp(float hp);
	float StepReward(float dist);
};

