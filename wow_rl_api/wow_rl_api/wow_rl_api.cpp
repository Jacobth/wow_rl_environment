#include "stdafx.h"
#include "MemoryAction.h"
#include "Environment.h"
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <iostream>

void test(Environment env);
void printState(Environment env, MemoryAction mem);
void testPos(Environment env, MemoryAction mem);

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
	testPos(env, mem);

	//env.Reset();
	//test(env);

	//printState(env, mem);

	return 0;
}

void test(Environment env) {

	int y = env.Reset();

	std::cout << y << std::endl;

	for (int i = 0; i < 200; i++) {

		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(0, 3);

		int action = uni(rng);
		float* arr = env.Step(0);

		//float arr2[4];

		//memcpy(arr, arr2, sizeof(arr));

		//Environment::StepReturn step = 

		//std::cout << (float)(*(arr + 2)) << std::endl;

		if (*(arr + 3) == 1) {
			int x = env.Reset();
			std::cout << x << std::endl;
		}
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