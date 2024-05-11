#include <map>
#include <windows.h>

#include "pch.h"
#include "Market.h"
#include "Config/Instances.h"
#include "Automations/AutomationsInstances.h"

typedef int(__cdecl* _MarketOperate)(int actionType);

_MarketOperate MarketOperate;

Market::Market()
{
	mSellResourcesInterval = &Automations::pMarketAutomations->mSellResourcesInterval;
	mCurrentResourcesTimer = 0;
	mAutoSelling = false;

	MarketOperate = (_MarketOperate)(modBase + 0x67040);
}

void Market::Sell()
{
	DWORD resourceAmount;
	DWORD* resourceIdAddress = (DWORD*)(modBase + 0xd5f814);

	byte i = 0;
	while (Automations::resourceNames[i] != NULL) {
		if (Automations::pMarketAutomations->mAutoSelling[i * 2 + 1] == 1) {
			resourceAmount = *(DWORD*)(modBase + 0xd5fcc4 + (0x4 * i));

			while (resourceAmount > Automations::pMarketAutomations->mAutoSelling[i * 2]) {
				*resourceIdAddress = i + 2;
				MarketOperate(1);
				Sleep(25);
				resourceAmount = *(DWORD*)(modBase + 0xd5fcc4 + (0x4 * i));
			}
		}
		i++;
	}
}