#include "Instances.h"

namespace Config {
	Resources* pResourcesConfig;
	Units* pUnitsConfig;

	Operation* pPricesConfig;
	Operation* pBotSettingsConfig;
	Operation* pStartGoodsConfig;
	Operation* pStartTroopsConfig;

	void InitializeInstances() {
		pResourcesConfig = new Resources();
		pUnitsConfig = new Units();

		pPricesConfig = new Operation("Prices");
		pBotSettingsConfig = new Operation("BotSettings");
		pStartGoodsConfig = new Operation("StartGoods");
		pStartTroopsConfig = new Operation("StartTroops");
	}

	void DeleteInstances() {
		delete pResourcesConfig;
		delete pUnitsConfig;

		delete pPricesConfig;
		delete pBotSettingsConfig;
		delete pStartGoodsConfig;
		delete pStartTroopsConfig;
	}
}