#include "stdafx.h"
#include "MemoryAction.h"
#include <iostream>
#include <thread>
#include <math.h>
#include <string>
#include <vector>

#define _USE_MATH_DEFINES

#define EPSILON 0.5
#define DELAY 100
#define VK_KEY_1 0x31

enum ObjectOffsets : int
{
	Type = 0x14,
	Pos_X = 0x79C,
	Pos_Y = 0x798,
	Pos_Z = 0x7A0,
	Rot = 0x7A8,
	Guid = 0x30,
	UnitFields = 0x8,
	Corpse_Pos_X = 0xBD0A5C,
	Corpse_Pos_Y = 0xBD0A58,
	Corpse_Pos_Z = 0xBD0A60,
	Movement = 0x81C,
	Tick_Count = 0xB499A4
};

enum UnitOffsets : int
{
	Level = 0x36 * 4,
	Health = 0x18 * 4,
	Energy = 0x19 * 4,
	MaxHealth = 0x20 * 4,
	SummonedBy = 0xE * 4,
	MaxEnergy = 0x21 * 4
};

enum ClientOffsets : int
{
	StaticClientConnection = 0x00C79CE0,
	ObjectManagerOffset = 0x2ED0,
	FirstObjectOffset = 0xAC,
	LocalGuidOffset = 0xC0,
	NextObjectOffset = 0x3C,
	LocalPlayerGUID = 0xBD07A8,
	LocalTargetGUID = 0x00BD07B0
};

enum NameOffsets : long
{
	nameStore = 0x00C5D938 + 0x8,
	nameMask = 0x24,
	nameBase = 0x1C,
	nameString = 0x20,
	playerMask = 0x10,
};

enum Movements : int
{
	CtmABase = 0xCA11D8,
	CtmAction = CtmABase + 0x1C,
	FaceNorth = 0x2,
	MoveForwardStart = 0x4,
	MoveForwardStop = 0x3,
	MoveReset = 13,
	CtmX = CtmABase + 0x90,
	CtmY = CtmABase + 0x8C,
	CtmZ = CtmABase + 0x94,
	CtmDistance = CtmABase + 0xC,
	InitCtm_1 = CtmABase + 0x5,
	InitCtm_2 = CtmABase + 0x6,
	InitCtm_3 = CtmABase + 0x7,
	TurnCtm = CtmABase + 0x4,
	InitFloat = CtmABase + 0x8
};

//const float PI = atan(1) * 4;

MemoryAction::MemoryAction()
{
	LoadFromMemory();
}

int MemoryAction::GetObjectBaseByGuid(int firstObject, long guid)
{
	int baseTmp = firstObject;
	long tmpGuid;

	while (baseTmp != 0)
	{
		tmpGuid = mem.ReadUInt64((intptr_t)(baseTmp + ObjectOffsets::Guid));

		if (tmpGuid == guid) {
			return baseTmp;
		}

		baseTmp = mem.ReadUInt32((intptr_t)(baseTmp + ClientOffsets::NextObjectOffset));
	}

	return 0;
}

void MemoryAction::LoadFromMemory()
{
	clientConnection = mem.ReadUInt32((intptr_t)ClientOffsets::StaticClientConnection);
	objectManager = mem.ReadUInt32((intptr_t)(clientConnection + ClientOffsets::ObjectManagerOffset));
	firstObject = mem.ReadUInt32((intptr_t)(objectManager + ClientOffsets::FirstObjectOffset));
	targetGuid = mem.ReadUInt64((intptr_t)(ClientOffsets::LocalTargetGUID));
	playerGuid = mem.ReadUInt64((intptr_t)(objectManager + ClientOffsets::LocalGuidOffset));

	playerBase = GetObjectBaseByGuid(firstObject, playerGuid);
}

void MemoryAction::SetPos(float x, float y, float z)
{
	mem.WriteFloat((intptr_t)(playerBase + ObjectOffsets::Pos_X), x);
	mem.WriteFloat((intptr_t)(playerBase + ObjectOffsets::Pos_Y), y);
	mem.WriteFloat((intptr_t)(playerBase + ObjectOffsets::Pos_Z), z);
}

float MemoryAction::GetDistance(float x, float y)
{
	float a = GetX() - x;
	float b = GetY() - y;

	float distance = std::sqrt((a*a) + (b*b));

	return distance;
}

void MemoryAction::StartMoving(float x, float y, float z)
{
	const float init_float = 0.25;
	const float distance = 0.2f;
	const byte init_value_1 = 102;
	const byte init_value_2 = 95;
	const byte init_value_3 = 65;
	const byte turn_scale = 243;

	mem.WriteFloat((intptr_t)Movements::InitFloat, init_float);
	mem.WriteByte((intptr_t)Movements::InitCtm_1, init_value_1);
	mem.WriteByte((intptr_t)Movements::InitCtm_2, init_value_2);
	mem.WriteByte((intptr_t)Movements::InitCtm_3, init_value_3);
	mem.WriteByte((intptr_t)Movements::TurnCtm, turn_scale);

	mem.WriteFloat((intptr_t)(Movements::CtmX), x);
	mem.WriteFloat((intptr_t)(Movements::CtmY), y);
	mem.WriteFloat((intptr_t)(Movements::CtmZ), z);

	mem.WriteInt((intptr_t)(Movements::CtmAction), Movements::MoveForwardStart);
	mem.WriteFloat((intptr_t)(Movements::CtmDistance), distance);
}

bool MemoryAction::MoveToPoint(float x, float y, float z)
{
	const double max_time = 6000;

	StartMoving(x, y, z);

	clock_t start = clock();

	while (IsMoving()) {

		double elapsed = (double)(clock() - start);

		if (elapsed > max_time) {
			Stop();
			return true;
		}
	}

	return GetDistance(x, y) > EPSILON;
}

bool MemoryAction::IsMoving()
{
	int action = mem.ReadInt((intptr_t)(Movements::CtmAction));

	return action == Movements::MoveForwardStart;
}

void MemoryAction::SetAngle(float angle)
{
	mem.WriteFloat((intptr_t)(playerBase + ObjectOffsets::Rot), angle);
}

void MemoryAction::Stop()
{
	mem.WriteInt((intptr_t)(Movements::CtmAction), Movements::MoveForwardStop);
	Sleep(300);
}

void MemoryAction::MoveForward()
{
	mem.WriteInt((intptr_t)(Movements::CtmAction), Movements::MoveForwardStart);
}

float MemoryAction::GetAngle()
{
	float angle = mem.ReadFloat((intptr_t)(playerBase + ObjectOffsets::Rot));
	return angle;
}

float MemoryAction::GetX()
{
	float x = mem.ReadFloat((intptr_t)(playerBase + ObjectOffsets::Pos_X));
	return x;
}

float MemoryAction::GetY()
{
	float y = mem.ReadFloat((intptr_t)(playerBase + ObjectOffsets::Pos_Y));

	return y;
}

float MemoryAction::GetZ()
{
	float z = mem.ReadFloat((intptr_t)(playerBase + ObjectOffsets::Pos_Z));

	return z;
}

void MemoryAction::SetX(float x)
{
	SetPos(x, GetY(), GetZ());
}

void MemoryAction::SetY(float y)
{
	SetPos(GetX(), y, GetZ());
}

void MemoryAction::SetZ(float z)
{
	SetPos(GetX(), GetY(), z);
}

int MemoryAction::GetMaxHp()
{
	int unitFieldsAddress = mem.ReadUInt32((intptr_t)(playerBase + ObjectOffsets::UnitFields));
	int hp = mem.ReadUInt32((intptr_t)(unitFieldsAddress + UnitOffsets::MaxHealth));

	return hp;
}

int MemoryAction::GetHp()
{
	int unitFieldsAddress = mem.ReadUInt32((intptr_t)(playerBase + ObjectOffsets::UnitFields));
	int hp = mem.ReadUInt32((intptr_t)(unitFieldsAddress + UnitOffsets::Health));

	return hp;
}

void MemoryAction::SetHp(int hp)
{
	DWORD unitFieldsAddress = mem.ReadUInt32((intptr_t)(playerBase + ObjectOffsets::UnitFields));
	mem.WriteUInt32((intptr_t)(unitFieldsAddress + UnitOffsets::Health), hp);
}

float MemoryAction::ReadCorpsePos(int offset)
{
	float pos = mem.ReadFloat((intptr_t)(offset));
	return pos;
}

void MemoryAction::MoveToCorpse() {

	float x = ReadCorpsePos(ObjectOffsets::Corpse_Pos_X);
	float y = ReadCorpsePos(ObjectOffsets::Corpse_Pos_Y);
	float z = ReadCorpsePos(ObjectOffsets::Corpse_Pos_Z);

	SetPos(x, y, z);
}

void MemoryAction::SetSpeed(float speed)
{
	mem.WriteFloat((intptr_t)(playerBase + ObjectOffsets::Movement), speed);
}

float MemoryAction::GetSpeed()
{
	float speed = mem.ReadFloat((intptr_t)(playerBase + ObjectOffsets::Movement));

	return speed;
}

void MemoryAction::TurnOffAFK()
{
	int time = 20000000;

	mem.WriteInt((intptr_t)ObjectOffsets::Tick_Count, time);
}

bool MemoryAction::IsDead()
{
	return GetHp() == 0;
}

void MemoryAction::ResetGame()
{
	PostMessage(mem.hwnd, WM_KEYDOWN, VK_KEY_1, 0);
	PostMessage(mem.hwnd, WM_KEYUP, VK_KEY_1, 0);
}