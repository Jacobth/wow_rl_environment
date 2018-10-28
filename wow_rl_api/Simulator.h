#pragma once
#include <math.h>
#include <vector>
#include "MemoryAction.h"

class Simulator
{
public:

	const float PI = atan(1) * 4;

	Simulator(float k, float m, float k_r, float m_r, float angle, float start_x, float start_y)
	{
		this->k = k;
		this->m = m;
		this->k_r = k_r;
		this->m_r = m_r;
		this->angle = angle;
		this->start_x = start_x;
		this->start_y = start_y;

		wow_angle = PI + angle;
	}

	void testGoal();
	void testDistanceToEdge();
	void testMove(int action);
	void reset(MemoryAction mem);

	std::vector<float> getNextPos(int action, float x, float y, float current_angle);
	bool isGoal(float x, float y);
	float getEdgeDist(float x, float y);

private:

	

	float k;
	float m;
	float k_r;
	float m_r;
	float angle;
	float start_x;
	float start_y;
	float wow_angle;
};

