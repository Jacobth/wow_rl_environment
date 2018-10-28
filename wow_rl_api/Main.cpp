#include "stdafx.h"
#include "MemoryAction.h"
#include "Environment.h"
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <iostream>

void printCurrentPosition(MemoryAction mem);


int main()
{
	MemoryAction mem;

	printCurrentPosition(mem);

	return 0;
}

void printCurrentPosition(MemoryAction mem) {

	while (true) {

		float x = mem.GetX();
		float y = mem.GetY();
		float z = mem.GetZ();

		std::cout << "x:" << x << std::endl;
		std::cout << "y:" << y << std::endl;
		std::cout << "z:" << z << '\n' << std::endl;
		Sleep(100);
	}
}