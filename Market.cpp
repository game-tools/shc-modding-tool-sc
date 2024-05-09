#include <map>

#include "pch.h"
#include "Market.h"
#include "Config/Instances.h"

typedef int(__cdecl* _MarketOperate)(int actionType);

_MarketOperate MarketOperate;

Market::Market()
{
	mSellResourcesInterval = Config::pResourcesConfig->m_data["sellResourcesInterval"];
	mCurrentResourcesTimer = 0;

	MarketOperate = (_MarketOperate)(modBase + 0x67040);
}

void Market::sell()
{
	DWORD resourceAmount;
	DWORD* resourceIdAddress = (DWORD*)(modBase + 0xd5f814);

	for (std::map<DWORD, DWORD>::iterator it = Config::pResourcesConfig->m_to_sell_map.begin(); it != Config::pResourcesConfig->m_to_sell_map.end(); it++) {
		resourceAmount = *(DWORD*)(modBase + 0xd5fcc4 + (0x4 * (it->first - 2)));

		while (resourceAmount > it->second) {
			*resourceIdAddress = it->first;
			MarketOperate(1);
			Sleep(25);
			resourceAmount = *(DWORD*)(modBase + 0xd5fcc4 + (0x4 * (it->first - 2)));
		}
	}

	printf("SOLD from class\n");
}