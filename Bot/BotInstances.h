#pragma once

#include <map>
#include <iostream>

#include "Character.h"
#include "../Globals.h"

namespace Bot {
	extern std::map<std::basic_string<TCHAR>, Character*> characters;

	extern const char* properties[];

	void InitializeInstances();
	void LoadConfig();
	void PrepareConfig();
}
