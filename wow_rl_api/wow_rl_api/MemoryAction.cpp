#include "stdafx.h"
#include "MemoryAction.h"
#include <ctime>

#define _USE_MATH_DEFINES

#define EPSILON 0.5
#define DELAY 100

/*These are the offsets for the World of Warcraft client in version
*3.3.5, build 12340
*These offsets are always the same when the program launch.
*/

enum ObjectOffsets : DWORD
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

enum UnitOffsets : DWORD
{
	Level = 0x36 * 4,
	Health = 0x18 * 4,
	Energy = 0x19 * 4,
	MaxHealth = 0x20 * 4,
	SummonedBy = 0xE * 4,
	MaxEnergy = 0x21 * 4
};

enum ClientOffsets : DWORD
{
	StaticClientConnection = 0x00C79CE0,
	ObjectManagerOffset = 0x2ED0,
	FirstObjectOffset = 0xAC,
	LocalGuidOffset = 0xC0,
	NextObjectOffset = 0x3C,
	LocalPlayerGUID = 0xBD07A8,
	LocalTargetGUID = 0x00BD07B0
};

enum NameOffsets : DWORDLONG
{
	nameStore = 0x00C5D938 + 0x8,
	nameMask = 0x24,
	nameBase = 0x1C,
	nameString = 0x20,
	playerMask = 0x10,
};

enum Movements
{
	CtmABase = 0xCA11D8,
	CtmAction = CtmABase + 0x1C,
	FaceNorth = 0x2,
	MoveForwardStart = 0x4,
	MoveForwardStop = 13,
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

const float PI = atan(1) * 4;

MemoryAction::MemoryAction() {
	LoadFromMemory();
}

DWORD MemoryAction::GetObjectBaseByGuid(DWORD firstObject, DWORDLONG guid)
{
	DWORD baseTmp = firstObject;
	DWORDLONG tmpGuid;

	while (baseTmp != 0)
	{
		tmpGuid = mem.ReadUInt64((LPVOID)(baseTmp + ObjectOffsets::Guid));

		if (tmpGuid == guid) {
			return baseTmp;
		}

		baseTmp = mem.ReadUInt32((LPVOID)(baseTmp + ClientOffsets::NextObjectOffset));
	}

	return 0;
}

void MemoryAction::LoadFromMemory()
{
	clientConnection = mem.ReadUInt32((LPVOID)ClientOffsets::StaticClientConnection);
	objectManager = mem.ReadUInt32((LPVOID)(clientConnection + ClientOffsets::ObjectManagerOffset));
	firstObject = mem.ReadUInt32((LPVOID)(objectManager + ClientOffsets::FirstObjectOffset));
	targetGuid = mem.ReadUInt64((LPVOID)(ClientOffsets::LocalTargetGUID));
	playerGuid = mem.ReadUInt64((LPVOID)(objectManager + ClientOffsets::LocalGuidOffset));

	playerBase = GetObjectBaseByGuid(firstObject, playerGuid);
}

void MemoryAction::SetPos(float x, float y, float z)
{
	mem.WriteFloat((LPVOID)(playerBase + ObjectOffsets::Pos_X), x);
	mem.WriteFloat((LPVOID)(playerBase + ObjectOffsets::Pos_Y), y);
	mem.WriteFloat((LPVOID)(playerBase + ObjectOffsets::Pos_Z), z);
}

float MemoryAction::GetDistance(float x, float y) {

	float a = GetX() - x;
	float b = GetY() - y;

	float distance = std::sqrt((a*a) + (b*b));

	return distance;
}

void MemoryAction::StartMoving(float x, float y, float z) {

	const float init_float = 0.25;
	const float distance = 0.2f;
	const byte init_value_1 = 102;
	const byte init_value_2 = 95;
	const byte init_value_3 = 65;
	const byte turn_scale = 243;

	mem.WriteFloat((LPVOID)Movements::InitFloat, init_float);
	mem.WriteByte((LPVOID)Movements::InitCtm_1, init_value_1);
	mem.WriteByte((LPVOID)Movements::InitCtm_2, init_value_2);
	mem.WriteByte((LPVOID)Movements::InitCtm_3, init_value_3);
	mem.WriteByte((LPVOID)Movements::TurnCtm, turn_scale);

	mem.WriteFloat((LPVOID)(Movements::CtmX), x);
	mem.WriteFloat((LPVOID)(Movements::CtmY), y);
	mem.WriteFloat((LPVOID)(Movements::CtmZ), z);

	mem.WriteInt((LPVOID)(Movements::CtmAction), Movements::MoveForwardStart);
	mem.WriteFloat((LPVOID)(Movements::CtmDistance), distance);
}

bool MemoryAction::MoveToPoint(float x, float y, float z) {

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

	//std::cout << GetDistance(x, y) << std::endl;

	return GetDistance(x, y) > EPSILON;
}

bool MemoryAction::IsMoving() {

	int action = mem.ReadInt((LPVOID)(Movements::CtmAction));

	return action == Movements::MoveForwardStart;
}

void MemoryAction::SetAngle(FLOAT angle)
{
	mem.WriteFloat((LPVOID)(playerBase + ObjectOffsets::Rot), angle);
}

void MemoryAction::Stop() {
	if (IsMoving())
		mem.WriteInt((LPVOID)(Movements::CtmAction), Movements::MoveForwardStop);
}

void MemoryAction::MoveForward() {
	mem.WriteInt((LPVOID)(Movements::CtmAction), Movements::MoveForwardStart);
}

void MemoryAction::MoveBackwards() {

	FLOAT new_angle = GetAngle() - PI;

	SetAngle(new_angle);

	MoveForward();
}

void MemoryAction::MoveLeft() {

	FLOAT new_angle = GetAngle() + (PI / 2);

	SetAngle(new_angle);

	MoveForward();
}

void MemoryAction::MoveRight() {

	FLOAT new_angle = GetAngle() - (PI / 2);

	SetAngle(new_angle);

	MoveForward();
}

FLOAT MemoryAction::GetAngle()
{
	FLOAT angle = mem.ReadFloat((LPVOID)(playerBase + ObjectOffsets::Rot));
	return angle;
}

FLOAT MemoryAction::GetX()
{
	FLOAT x = mem.ReadFloat((LPVOID)(playerBase + ObjectOffsets::Pos_X));
	return x;
}

FLOAT MemoryAction::GetY()
{
	FLOAT y = mem.ReadFloat((LPVOID)(playerBase + ObjectOffsets::Pos_Y));

	return y;
}

FLOAT MemoryAction::GetZ()
{
	FLOAT z = mem.ReadFloat((LPVOID)(playerBase + ObjectOffsets::Pos_Z));

	return z;
}

void MemoryAction::SetX(FLOAT x)
{
	SetPos(x, GetY(), GetZ());
}

void MemoryAction::SetY(FLOAT y)
{
	SetPos(GetX(), y, GetZ());
}

void MemoryAction::SetZ(FLOAT z)
{
	SetPos(GetX(), GetY(), z);
}

DWORD MemoryAction::GetHp()
{
	DWORD unitFieldsAddress = mem.ReadUInt32((LPVOID)(playerBase + ObjectOffsets::UnitFields));
	DWORD hp = mem.ReadUInt32((LPVOID)(unitFieldsAddress + UnitOffsets::Health));

	return hp;
}

void MemoryAction::SetHp(DWORD hp)
{
	DWORD unitFieldsAddress = mem.ReadUInt32((LPVOID)(playerBase + ObjectOffsets::UnitFields));
	mem.WriteUInt32((LPVOID)(unitFieldsAddress + UnitOffsets::Health), hp);
}

FLOAT MemoryAction::ReadCorpsePos(DWORD offset)
{
	FLOAT pos = mem.ReadFloat((LPVOID)(offset));
	return pos;
}

void MemoryAction::MoveToCorpse() {

	FLOAT x = ReadCorpsePos(ObjectOffsets::Corpse_Pos_X);
	FLOAT y = ReadCorpsePos(ObjectOffsets::Corpse_Pos_Y);
	FLOAT z = ReadCorpsePos(ObjectOffsets::Corpse_Pos_Z);

	SetPos(x, y, z);
}

void MemoryAction::SetSpeed(FLOAT speed)
{
	mem.WriteFloat((LPVOID)(playerBase + ObjectOffsets::Movement), speed);
}

FLOAT MemoryAction::GetSpeed()
{
	FLOAT speed = mem.ReadFloat((LPVOID)(playerBase + ObjectOffsets::Movement));

	return speed;
}

void MemoryAction::TurnOffAFK() {

	int time = 20000000;

	mem.WriteInt((LPVOID)ObjectOffsets::Tick_Count, time);
}

bool MemoryAction::IsDead() {

	float dead_x = -119;
	float dead_y = -8921;

	return GetDistance(dead_x, dead_y) < 5;
}
/*
typedef struct {
	DWORD funcptr;
	char command[255];
} INJDATA;

__declspec(naked) DWORD codeasm() {
	__asm {
		nop
		push ebx //here we have address of funcptr, but I want the address of command on EAX so...
		pop eax // remove from stack and pass it to EAX
		add eax, 4 // add 4 to the address, therefore, now we have the address of char command[255]
		push 0
		push eax
		push eax
		mov edx, [ebx] //grab the content of EBX which is funcptr and pass to EDX
		call edx // call Lua_doString()
		add esp, 0xC //probably just "fixing" the stack pointer
		nop
		ret
	};
	//return 0;
}

static void after_codeasm(void) {
}

void convertToASCII(std::string letter, char x[255])
{
	for (int j = 0; j <= 255; j++) {
		x[j] = 0x0;
	}
	for (int i = 0; i < letter.size(); i++)
	{
		x[i] = letter.at(i);
	}
}

void MemoryAction::Lua_DoString(std::string cmd) {

	HINSTANCE mod = LoadLibrary(L"user32.dll");

	DWORD Framescript_ExecuteBuffer = 0x00819210;
	DWORD func = reinterpret_cast<unsigned int>(mod) + Framescript_ExecuteBuffer;

	DWORD cbCodeSize = ((PBYTE)after_codeasm - (PBYTE)codeasm);

	cbCodeSize = 200;

	INJDATA mydata;
	convertToASCII(cmd, mydata.command);
	mydata.funcptr = func;

	LPVOID pData = VirtualAllocEx(mem.handle, NULL, sizeof(func), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	LPVOID pLibRemote = VirtualAllocEx(mem.handle, NULL, cbCodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	WriteProcessMemory(mem.handle, pData, &mydata, sizeof(mydata), NULL);
	WriteProcessMemory(mem.handle, pLibRemote, &codeasm, cbCodeSize, NULL);

	HANDLE hThread = CreateRemoteThread(mem.handle, NULL, 0, (LPTHREAD_START_ROUTINE)pLibRemote, pData, 0, NULL);

	if (hThread != 0) {
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		VirtualFreeEx(mem.handle, pLibRemote, cbCodeSize, MEM_RELEASE);
		VirtualFreeEx(mem.handle, pData, sizeof(func), MEM_RELEASE);
	}
}
*/

/*
bool MemoryAction::Move(int action, float x, float y) {

MemoryAction::PointNorth();

std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));

switch (action)
{
case 0:
MoveForward();
break;

case 1:
MoveBackwards();
break;

case 2:
MoveLeft();
break;

case 3:
MoveRight();
break;

default:
break;
}

float inf = std::numeric_limits<float>::infinity();

float prev_distance = inf;
float current_distance = 0;
bool stuck = false;

int sleep = 40;

std::this_thread::sleep_for(std::chrono::milliseconds(sleep));

while ((current_distance = GetDistance(x, y)) > EPSILON) {

std::this_thread::sleep_for(std::chrono::milliseconds(sleep));

// If this is true we missed the next step
if (current_distance >= prev_distance) {

std::cout << "missed next state" << std::endl;
stuck = true;

break;
}

prev_distance = current_distance;
}

Stop();

std::this_thread::sleep_for(std::chrono::milliseconds(sleep));

PointNorth();

return stuck;
}
*/