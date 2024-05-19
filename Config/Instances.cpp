#include "Instances.h"

namespace Config {
	Resources* pResourcesConfig;
	Units* pUnitsConfig;

	Operation* pPricesConfig;
	Operation* pBotSettingsConfig;
	Operation* pStartGoodsConfig;
	Operation* pStartTroopsConfig;
	Operation* pMarketConfig;
	Operation* pUnitPropertiesConfig;

	void InitializeInstances() {
		pResourcesConfig = new Resources();
		pUnitsConfig = new Units();

		pPricesConfig = new Operation("Prices", false);
		pBotSettingsConfig = new Operation("BotSettings", false);
		pStartGoodsConfig = new Operation("StartGoods", false);
		pStartTroopsConfig = new Operation("StartTroops", false);
		pMarketConfig = new Operation("Market", true);
		pUnitPropertiesConfig = new Operation("UnitProperties", false);
	}

	void DeleteInstances() {
		delete pResourcesConfig;
		delete pUnitsConfig;

		delete pPricesConfig;
		delete pBotSettingsConfig;
		delete pStartGoodsConfig;
		delete pStartTroopsConfig;
		delete pMarketConfig;
		delete pUnitPropertiesConfig;
	}
}