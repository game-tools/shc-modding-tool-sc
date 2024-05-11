#include "MarketAutomations.h"
#include "../Config/Instances.h"

namespace Automations {
	const char* resourceNames[] = { "Wood", "Hop", "Stone", "Unknown1", "Iron", "Unknown2", "Pitch", "Wheat", "Bread", "Cheese", "Meat", "Apple", "Beer", "Gold (Not Used)", "Flour", "Bow", "Crossbow", "Spear", "Pike", "Mace", "Sword", "Leather Armor", "Armor", NULL};

	MarketAutomations::MarketAutomations() {
		LoadConfig();
	}

	void MarketAutomations::LoadConfig() {
		mAutoSelling.clear();
		for (DWORD value : Config::pMarketConfig->mData["autoSelling"]) {
			mAutoSelling.push_back(value);
		}

		mSellResourcesInterval = Config::pMarketConfig->mData["sellResourcesInterval"];
	}

	void MarketAutomations::PrepareConfig() {
		Config::pMarketConfig->mDataSave = {};
		Config::pMarketConfig->mDataSave["autoSelling"] = mAutoSelling;
		Config::pMarketConfig->mDataSave["sellResourcesInterval"] = mSellResourcesInterval;
	}
}