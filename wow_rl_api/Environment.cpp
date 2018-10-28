#include "stdafx.h"
#include "Environment.h"
#include "MemoryAction.h"
#include <chrono>
#include <thread>
#include <random>
#include <iostream>

MemoryAction mem;

void Environment::Reset(float init_x, float init_y)
{
	const float init_z = 148.1;

	mem.SetPos(init_x, init_y, init_z);
	Sleep(400);
}

void Environment::Step(float new_x, float new_y)
{
	mem.MoveToPoint(new_x, new_y, mem.GetZ());
}

float* Environment::GetPos()
{
	float* vals = new float[2];

	vals[0] = mem.GetX();
	vals[1] = mem.GetY();

	delete vals;

	return vals;
}

extern "C" {

	Environment* Env() { return new Environment(); }

	void ResetTest(Environment* env, float init_x, float init_y) { env->Reset(init_x, init_y); }
	void StepTest(Environment* env, float new_x, float new_y) { env->Step(new_x, new_y); }
	float* GetPos(Environment* env) { return env->GetPos(); }
}