#include "stdafx.h"
#include "MemoryReader.h"

DWORD MemoryReader::ReadInt(LPVOID pointer) {

	LPVOID value = 0;

	HWND hwnd = FindWindowA(NULL, "World of warcraft");

	if (hwnd == NULL) {

		std::cout << "Couldn't find the process" << std::endl;
		Sleep(3000);
		exit(-1);
	}

	else {
		DWORD procID;

		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(3000);
			exit(-1);
		}

		else {
			ReadProcessMemory(handle, pointer, &value, sizeof(value), 0);

			return (INT)value;
		}
	}

}

INT MemoryReader::WriteInt(LPVOID pointer, INT value) {

	HWND hwnd = FindWindowA(NULL, "World of warcraft");

	if (hwnd == NULL) {

		std::cout << "Couldn't find the process" << std::endl;
		Sleep(3000);
		exit(-1);
	}

	else {
		DWORD procID;

		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(3000);
			exit(-1);
		}

		else {

			WriteProcessMemory(handle, pointer, &value, sizeof(value), 0);

			return value;
		}
	}
}

DWORD MemoryReader::ReadUInt32(LPVOID pointer) {

	LPVOID value = 0;

	HWND hwnd = FindWindowA(NULL, "World of warcraft");

	if (hwnd == NULL) {

		std::cout << "Couldn't find the windows" << std::endl;
		Sleep(3000);
		exit(-1);
	}

	else {
		DWORD procID;

		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(3000);
			exit(-1);
		}

		else {

			//printf("adress: %n", pointer);
			ReadProcessMemory(handle, pointer, &value, sizeof(value), 0);

			return (DWORD)value;
		}
	}

}

DWORDLONG MemoryReader::ReadUInt64(LPVOID pointer) {

	LPVOID value = 0;

	HWND hwnd = FindWindowA(NULL, "World of warcraft");

	if (hwnd == NULL) {

		std::cout << "Couldn't find the windows" << std::endl;
		Sleep(3000);
		exit(-1);
	}

	else {
		DWORD procID;

		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(3000);
			exit(-1);
		}

		else {
			ReadProcessMemory(handle, pointer, &value, sizeof(value), 0);

			return (DWORDLONG)value;

		}
	}

}

FLOAT MemoryReader::ReadFloat(LPVOID pointer) {

	FLOAT value;

	HWND hwnd = FindWindowA(NULL, "World of warcraft");

	if (hwnd == NULL) {

		std::cout << "Couldn't find the windows" << std::endl;
		Sleep(3000);
		exit(-1);
	}

	else {
		DWORD procID;

		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(3000);
			exit(-1);
		}

		else {
			ReadProcessMemory(handle, pointer, &value, sizeof(value), 0);

			return value;

		}
	}
}

FLOAT MemoryReader::WriteFloat(LPVOID pointer, FLOAT value) {

	HWND hwnd = FindWindowA(NULL, "World of warcraft");

	if (hwnd == NULL) {

		std::cout << "Couldn't find the windows" << std::endl;
		Sleep(3000);
		exit(-1);
	}

	else {
		DWORD procID;

		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(3000);
			exit(-1);
		}

		else {
			WriteProcessMemory(handle, pointer, &value, sizeof(value), 0);

			return value;

		}
	}
}

DWORD MemoryReader::WriteUInt32(LPVOID pointer, DWORD value) {

	HWND hwnd = FindWindowA(NULL, "World of warcraft");

	if (hwnd == NULL) {

		std::cout << "Couldn't find the windows" << std::endl;
		Sleep(3000);
		exit(-1);
	}

	else {
		DWORD procID;

		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL) {
			std::cout << "Couldn't find the process id" << std::endl;
			Sleep(3000);
			exit(-1);
		}

		else {

			WriteProcessMemory(handle, pointer, &value, sizeof(value), 0);

			return value;
		}
	}
}