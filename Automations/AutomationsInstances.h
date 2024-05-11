#pragma once

#include "MarketAutomations.h"

namespace Automations {
	extern MarketAutomations* pMarketAutomations;

	void InitializeInstances();
	void DeleteInstances();
}