#pragma once
#include<Windows.h>

class MemoryReader
{

public:

	MemoryReader();

	int ReadUInt32(intptr_t pointer);
	long ReadUInt64(intptr_t pointer);
	float ReadFloat(intptr_t pointer);
	int ReadInt(intptr_t pointer);
	float WriteFloat(intptr_t pointer, float value);
	int WriteUInt32(intptr_t pointer, int value);
	int WriteInt(intptr_t pointer, int value);
	byte WriteByte(intptr_t pointer, byte value);
	byte ReadByte(intptr_t pointer);

	//DWORD dwGetModuleBaseAddress(DWORD dwProcessIdentifier, TCHAR *lpszModuleName);

	HWND hwnd;
	DWORD procID;
	HANDLE handle;
	DWORD hThread;

private:
	void InitReader();
};

