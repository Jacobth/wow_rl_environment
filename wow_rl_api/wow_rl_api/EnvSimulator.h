#pragma once
class EnvSimulator
{
public:
	EnvSimulator();
	
	float* Step_sim(int action);
	float* Reset_sim();


	float GetDistance(float x, float y);

private:
	float StepRewardSim(float dist);
};

