#pragma once

#include <windows.h>
#include <vector>

namespace Automations {
	const char* resourceNames[];

	class MarketAutomations {
	public:
		DWORD mSellResourcesInterval;
		std::vector<DWORD> mAutoSelling;
	public:
		MarketAutomations();
		void LoadConfig();
		void PrepareConfig();
	};
}