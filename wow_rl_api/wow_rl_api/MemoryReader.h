#pragma once
#include<iostream>
#include<Windows.h>

class MemoryReader
{

public:

	MemoryReader();

	DWORD ReadUInt32(LPVOID pointer);
	DWORDLONG ReadUInt64(LPVOID pointer);
	FLOAT ReadFloat(LPVOID pointer);
	DWORD ReadInt(LPVOID pointer);
	FLOAT WriteFloat(LPVOID pointer, FLOAT value);
	DWORD WriteUInt32(LPVOID pointer, DWORD value);
	INT WriteInt(LPVOID pointer, INT value);
	BYTE WriteByte(LPVOID pointer, BYTE value);
	BYTE ReadByte(LPVOID pointer);

private:
	HWND hwnd;
	DWORD procID;
	HANDLE handle;

	void InitReader();
};

