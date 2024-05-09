#ifndef MARKET_H
#define MARKET_H

#include <windows.h>
#include <iostream>

#include "Globals.h"

class Market
{
public:
	Market();
	void sell();

	void setMCurrentResourcesTimer(DWORD currentResourcesTimer)
	{
		mCurrentResourcesTimer = currentResourcesTimer;
	}

	DWORD getMSellResourcesInterval() const { return mSellResourcesInterval; }
	DWORD getMCurrentResourcesTimer() const { return mCurrentResourcesTimer; }
private:
	DWORD mSellResourcesInterval; // in milliseconds
	DWORD mCurrentResourcesTimer;
};

#endif
