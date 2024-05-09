#pragma once

#include "Resources.h"
#include "Units.h"

namespace Config {
	extern Resources* pResourcesConfig;
	extern Units* pUnitsConfig;

	void InitializeInstances();
	void DeleteInstances();
}