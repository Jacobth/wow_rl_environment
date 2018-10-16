#pragma once
#include<iostream>
#include<Windows.h>
#include "MemoryReader.h"
#include <math.h>
#include <chrono>
#include <thread>

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
	void StartMoving(float x, float y);
	void MoveCorpseToPlayer();
	void SetCorpsePos(DWORD offset, FLOAT pos);

	bool MoveToPoint(float x, float y);
	bool IsMoving();

	DWORD GetHp();
	FLOAT GetAngle();
	FLOAT GetX();
	FLOAT GetY();
	FLOAT GetZ();
	DWORD GetObjectBaseByGuid(DWORD firstObject, DWORDLONG guid);
	FLOAT GetSpeed();
	FLOAT ReadCorpsePos(DWORD offset);

private:


};

