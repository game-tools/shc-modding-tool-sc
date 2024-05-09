#pragma once

#include <windows.h>
#include <iostream>
#include <map>

#include "../Globals.h"

class PlayerUnits {
public:
	DWORD mPlayerNumber;
	std::map<std::basic_string<TCHAR>, DWORD*> mCurrentEuropeanUnitsMap;
	std::map<std::basic_string<TCHAR>, DWORD*> mCurrentArabianUnitsMap;
public:
	PlayerUnits() {};
	PlayerUnits(DWORD playerNumber);
	void setCurrentUnitsPointers();
	void Recruit(DWORD unitId, DWORD count);
};