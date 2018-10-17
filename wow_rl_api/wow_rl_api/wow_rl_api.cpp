// wow_rl_api.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MemoryAction.h"
#include "Environment.h"
#include <vector>
#include <chrono>
#include <thread>
#include <random>

void test(Environment env);
void printState(Environment env, MemoryAction mem);

int main()
{
	MemoryAction mem;
	Environment env("elwynn");
	//env.Reset();
	//mem.MoveTest();

	//std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	//env.Reset();
	test(env);

	//printState(env, mem);

	return 0;
}

void test(Environment env) {

	env.Reset();

	for (int i = 0; i < 200; i++) {

		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(0, 3);

		int random_action = uni(rng);

		Environment::StepReturn step = env.Step(2);

		if (step.done)
			env.Reset();
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
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}