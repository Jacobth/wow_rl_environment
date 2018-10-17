#include "stdafx.h"
#include "MemoryReader.h"

MemoryReader::MemoryReader() {
	InitReader();
}

void MemoryReader::InitReader() {
	hwnd = FindWindowA(NULL, "World of warcraft");

	if (hwnd == NULL) {

		std::cout << "Couldn't find the process" << std::endl;
		Sleep(3000);
		exit(-1);
	}

	else {
		GetWindowThreadProcessId(hwnd, &procID);
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(3000);
			exit(-1);
		}
	}
}

DWORD MemoryReader::ReadInt(LPVOID pointer) {

	LPVOID value = 0;
	ReadProcessMemory(handle, pointer, &value, sizeof(value), 0);

	return (INT)value;
}

INT MemoryReader::WriteInt(LPVOID pointer, INT value) {

	WriteProcessMemory(handle, pointer, &value, sizeof(value), 0);

	return value;
}

DWORD MemoryReader::ReadUInt32(LPVOID pointer) {

	LPVOID value = 0;
	ReadProcessMemory(handle, pointer, &value, sizeof(value), 0);

	return (DWORD)value;
}

DWORDLONG MemoryReader::ReadUInt64(LPVOID pointer) {

	LPVOID value = 0;
	ReadProcessMemory(handle, pointer, &value, sizeof(value), 0);

	return (DWORDLONG)value;
}

FLOAT MemoryReader::ReadFloat(LPVOID pointer) {

	FLOAT value;
	ReadProcessMemory(handle, pointer, &value, sizeof(value), 0);

	return value;
}

FLOAT MemoryReader::WriteFloat(LPVOID pointer, FLOAT value) {

	WriteProcessMemory(handle, pointer, &value, sizeof(value), 0);

	return value;
}

DWORD MemoryReader::WriteUInt32(LPVOID pointer, DWORD value) {

	WriteProcessMemory(handle, pointer, &value, sizeof(value), 0);

	return value;
}

BYTE MemoryReader::WriteByte(LPVOID pointer, BYTE value) {

	WriteProcessMemory(handle, pointer, &value, sizeof(value), 0);

	return value;
}

BYTE MemoryReader::ReadByte(LPVOID pointer) {

	BYTE value;
	ReadProcessMemory(handle, pointer, &value, sizeof(value), 0);

	return value;
}