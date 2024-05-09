#pragma once

#include <vector>
#include <map>
#include <string>

#include "StartResources.h"
#include "StartGold.h"
#include "StartTroops.h"

namespace Start {
	extern std::vector<Resources*> startResources;
	extern Gold* startGold;
	extern std::map < std::basic_string<TCHAR>, Troops* > startTroops;

	extern const char* startResourcesLabels[];
	extern const char* startGoldLabels[];
	extern const char* startTroopsLabels[];

	void InitializeInstances();
	void DestroyInstances();
}