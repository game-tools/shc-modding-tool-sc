#pragma once

#include <windows.h>
#include <iostream>
#include <map>

#include "../Globals.h"

class PlayerResources
{
public:
	DWORD mPlayerNumber;
	std::map<std::basic_string<TCHAR>, DWORD*> mCurrentResourcesMap;
	std::map<std::basic_string<TCHAR>, DWORD*> mEnqueuedResourcesMap;
public:
	PlayerResources() {};
	PlayerResources(DWORD playerNumber);
	void SetCurrentResourcesPointers();
	void SetEnqueuedResourcesPointers();
	void Add(DWORD amount, DWORD id);
};