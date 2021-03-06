#pragma once
#include "MemoryReader.h"
#include <string>
#include <vector>

class MemoryAction
{
public:
	MemoryAction();

	int clientConnection;
	int objectManager;
	int firstObject;
	int playerBase;

	long playerGuid;
	long targetGuid;

	MemoryReader mem;

	float GetDistance(float x, float y);

	void LoadFromMemory();
	void SetAngle(float angle);
	void SetPos(float x, float y, float z);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetHp(int hp);
	void SetSpeed(float speed);
	void MoveToCorpse();
	void Stop();
	void MoveForward();
	void PointNorth() {
		SetAngle(0);
	};
	void StartMoving(float x, float y, float z);
	void TurnOffAFK();

	bool WalkToPoint(float x, float y, float angle);
	bool MoveToPoint(float x, float y, float z);
	bool MoveToPoint(float x, float y, float z, float min_z);
	bool IsMoving();

	int GetHp();
	int GetMaxHp();
	float GetAngle();
	float GetX();
	float GetY();
	float GetZ();
	int GetObjectBaseByGuid(int firstObject, long guid);
	float GetSpeed();
	float ReadCorpsePos(int offset);
	bool IsDead();
	void ResetGame();

private:


};

