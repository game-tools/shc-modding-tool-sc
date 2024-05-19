#pragma once

#include <vector>

#include "UnitsBase.h"

namespace Units {
	extern UnitsBase* pUnitHps;
	extern std::vector<UnitsBase*> pUnitDamage;

	void InitializeInstances();
	void LoadConfig();
	void PrepareConfig();
}