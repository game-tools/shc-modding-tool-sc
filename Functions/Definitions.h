#pragma once

#include <windows.h>

#include "../Globals.h"

typedef int(__thiscall* _AddResource)(DWORD* thisAddress, int playerNumber, int resource_id, int resource_amount);

extern _AddResource AddResource;

typedef int(__cdecl* _RecruitUnit)(int playerNumber, int unitId, int sth);
typedef int(__thiscall* _SetVariable)(DWORD* thisAddress, int a2, int a3, int a4, int a5);

extern _RecruitUnit RecruitUnit;
extern _SetVariable SetVariable;

namespace Functions {
	void InitializeDefinitions();
}
