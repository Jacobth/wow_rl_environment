// wow_rl_api.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MemoryAction.h"
#include "Environment.h"
#include <vector>
#include <chrono>
#include <thread>



int main()
{
	MemoryAction mem;
	Environment env;
		env.Reset();
		env.Step(1);
		env.Step(2);
		env.Step(2);
		env.Step(2);
		env.Step(0);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		env.Step(3);
		

//	while (true) {
	/*
		float x = mem.GetX();
		float y = mem.GetY();
		float z = mem.GetZ();

		std::cout << "x:" << x << std::endl;
		std::cout << "y:" << y << std::endl;
		std::cout << "z:" << z << '\n' << std::endl;

		std::cout << env.GetCloseState() << '\n' << std::endl	;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	//}

		while (true);
		*/
	return 0;
}

