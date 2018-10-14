#pragma once
#include<iostream>
#include<Windows.h>

class MemoryReader
{

public:
	DWORD ReadUInt32(LPVOID pointer);
	DWORDLONG ReadUInt64(LPVOID pointer);
	FLOAT ReadFloat(LPVOID pointer);
	DWORD ReadInt(LPVOID pointer);
	FLOAT WriteFloat(LPVOID pointer, FLOAT value);
	DWORD WriteUInt32(LPVOID pointer, DWORD value);
	INT WriteInt(LPVOID pointer, INT value);

};

