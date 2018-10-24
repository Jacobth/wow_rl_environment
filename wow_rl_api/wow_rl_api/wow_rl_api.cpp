#include "stdafx.h"
#include "MemoryAction.h"
#include "Environment.h"
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <iostream>
#include "Zones.h"
#include "Grid.h"

void test(Environment env);
void printState(Environment env, MemoryAction mem);
void testPos(Environment env, MemoryAction mem);
void testAvg(MemoryAction mem, Environment env);

int main()
{
	MemoryAction mem;
	Environment env("elwynn");
	//env.Reset();
	//mem.MoveTest();

	//std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	//std::cout << mem.GetHp() << std::endl;
	//env.Reset();
	//mem.Chat("h");
	//mem.checkTime();

	//env.Reset();
	//test(env);

	//mem.SetAngle(0);

	//env.Step(3);

	//testAvg(mem, env);

	//mem.SetPos(135, -9375, 65);

	//printState(env, mem);

	return 0;
}

void testAvg(MemoryAction mem, Environment env) {

	while (true) {

	//	std::cout << mem.GetDistance(env.t_x, env.t_y) << std::endl;

		Sleep(500);

	}

}

void test(Environment env) {

	float y = env.Reset()[0];

	std::cout << y << std::endl;

	for (int i = 0; i < 200; i++) {

		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(0, 3);

		int action = uni(rng);
		float done = env.Step(1)[3];

		Sleep(100);

		std::cout << done << std::endl;

		if (done == 1)
			env.Reset();

		//float arr2[4];

		//memcpy(arr, arr2, sizeof(arr));

		//Environment::StepReturn step = 

		//std::cout << (float)(*(arr + 2)) << std::endl;

	}
}

void printState(Environment env, MemoryAction mem) {
	while (true) {

		float x = mem.GetX();
		float y = mem.GetY();
		float z = mem.GetZ();

		std::cout << "x:" << x << std::endl;
		std::cout << "y:" << y << std::endl;
		std::cout << "z:" << z << '\n' << std::endl;

		std::cout << env.GetCloseState() << '\n' << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void testPos(Environment env, MemoryAction mem) {

	mem.Stop();
	Sleep(300);
	mem.SetPos(70, -9430, 56.6);
	//mem.SetPos(7, -9430, 57);
}