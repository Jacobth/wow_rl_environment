#include "stdafx.h"
#include "MemoryReader.h"
#include <iostream>

#define PROG_STRING "World of warcraft"

MemoryReader::MemoryReader() {
	InitReader();
}

void MemoryReader::InitReader() {
	hwnd = FindWindowA(NULL, PROG_STRING);

	if (hwnd == 0) {

		std::cout << "Couldn't find the process" << std::endl;
		Sleep(3000);
		exit(-1);
	}

	else {
		GetWindowThreadProcessId(hwnd, &procID);
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == 0) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(3000);
			exit(-1);
		}
	}
}

int MemoryReader::ReadInt(intptr_t pointer) {

	intptr_t value = 0;
	ReadProcessMemory(handle, (void *)pointer, &value, sizeof(value), 0);

	return (intptr_t)value;
}

int MemoryReader::WriteInt(intptr_t pointer, int value) {

	WriteProcessMemory(handle, (void *)pointer, &value, sizeof(value), 0);

	return value;
}

int MemoryReader::ReadUInt32(intptr_t pointer) {

	intptr_t value = 0;
	ReadProcessMemory(handle, (void *)pointer, &value, sizeof(value), 0);

	return (intptr_t)value;
}

long MemoryReader::ReadUInt64(intptr_t pointer) {

	intptr_t value = 0;
	ReadProcessMemory(handle, (void *)pointer, &value, sizeof(value), 0);

	return (DWORDLONG)value;
}

float MemoryReader::ReadFloat(intptr_t pointer) {

	float value;
	ReadProcessMemory(handle, (void *)pointer, &value, sizeof(value), 0);

	return value;
}

float MemoryReader::WriteFloat(intptr_t pointer, float value) {

	WriteProcessMemory(handle, (void *)pointer, &value, sizeof(value), 0);

	return value;
}

int MemoryReader::WriteUInt32(intptr_t pointer, int value) {

	WriteProcessMemory(handle, (void *)pointer, &value, sizeof(value), 0);

	return value;
}

byte MemoryReader::WriteByte(intptr_t pointer, byte value) {

	WriteProcessMemory(handle, (void *)pointer, &value, sizeof(value), 0);

	return value;
}

byte MemoryReader::ReadByte(intptr_t pointer) {

	byte value;
	ReadProcessMemory(handle, (void *)pointer, &value, sizeof(value), 0);

	return value;
}