#include "AutomationsInstances.h"

namespace Automations {
	MarketAutomations* pMarketAutomations;

	void InitializeInstances() {
		pMarketAutomations = new MarketAutomations();
	}

	void DeleteInstances() {
		delete pMarketAutomations;
	}
}