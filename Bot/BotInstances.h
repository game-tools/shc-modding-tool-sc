#pragma once

#include <map>
#include <iostream>

#include "Character.h"
#include "../Globals.h"

namespace Bot {
	extern DWORD* addAttackTroopsFactor;
	extern std::map<std::basic_string<TCHAR>, Character*> characters;

	extern const char* properties[];

	void InitializeInstances();
	void DeleteInstances();
	void InjectAddAttackTroopsCode();
	void SetVanillaCode();
	void LoadConfig();
	void PrepareConfig();
}
