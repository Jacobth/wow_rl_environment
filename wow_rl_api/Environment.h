#pragma once
class Environment
{
public:
	Environment() {};

	void Step(float new_x, float new_y);
	void Reset(float init_x, float init_y);
	float* GetPos();
};

