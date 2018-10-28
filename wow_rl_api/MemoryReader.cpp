#include "stdafx.h"
#include "MemoryReader.h"
#include <iostream>

//#include <tchar.h>
//#include <tlhelp32.h>

#define PROG_STRING "World of warcraft"

MemoryReader::MemoryReader() {
	InitReader();
}

void MemoryReader::InitReader() {

	int sleep = 3000;
	hwnd = FindWindowA(NULL, PROG_STRING);

	if (hwnd == 0) {

		std::cout << "Couldn't find the process" << std::endl;
		Sleep(sleep);
		exit(-1);
	}

	else {
		GetWindowThreadProcessId(hwnd, &procID);
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == 0) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(sleep);
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

/*
DWORD MemoryReader::dwGetModuleBaseAddress(DWORD dwProcessIdentifier, TCHAR *lpszModuleName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessIdentifier);
	DWORD dwModuleBaseAddress = 0;
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32 = { 0 };
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do
			{
				if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
				{
					dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}
	return dwModuleBaseAddress;
}*/