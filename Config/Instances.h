#pragma once

#include "Resources.h"
#include "Units.h"
#include "Operation.h"

namespace Config {
	extern Resources* pResourcesConfig;
	extern Units* pUnitsConfig;

	extern Operation* pPricesConfig;
	extern Operation* pBotSettingsConfig;
	extern Operation* pStartGoodsConfig;
	extern Operation* pStartTroopsConfig;

	void InitializeInstances();
	void DeleteInstances();
}