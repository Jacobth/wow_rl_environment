#pragma once
#include<iostream>
#include<Windows.h>
#include "MemoryReader.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <string>
#include <time.h>
#include <algorithm>
#include <vector>

class MemoryAction
{
public:
	MemoryAction();

	DWORD clientConnection;
	DWORD objectManager;
	DWORD firstObject;
	DWORD playerBase;

	DWORDLONG playerGuid;
	DWORDLONG targetGuid;

	MemoryReader mem;

	float GetDistance(float x, float y);

	void LoadFromMemory();
	void SetAngle(FLOAT angle);
	bool Move(int action, float x, float y);
	void SetPos(FLOAT x, FLOAT y, FLOAT z);
	void SetX(FLOAT x);
	void SetY(FLOAT y);
	void SetZ(FLOAT z);
	void SetHp(DWORD hp);
	void SetSpeed(FLOAT speed);
	void MoveToCorpse();
	void Stop();
	void MoveForward();
	void MoveBackwards();
	void MoveLeft();
	void MoveRight();
	void PointNorth() {
		SetAngle(0);
	};
	void StartMoving(float x, float y, float z);
	void MoveCorpseToPlayer();
	void SetCorpsePos(DWORD offset, FLOAT pos);
	void TurnOffAFK();

	bool MoveToPoint(float x, float y, float z);
	bool IsMoving();

	DWORD GetHp();
	FLOAT GetAngle();
	FLOAT GetX();
	FLOAT GetY();
	FLOAT GetZ();
	DWORD GetObjectBaseByGuid(DWORD firstObject, DWORDLONG guid);
	FLOAT GetSpeed();
	FLOAT ReadCorpsePos(DWORD offset);

	bool IsDead();

	void chat(std::string message);
	void Lua_DoString(std::string cmd);

private:
	

};

