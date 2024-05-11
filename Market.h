#ifndef MARKET_H
#define MARKET_H

#include <windows.h>
#include <iostream>

class Market
{
public:
	DWORD* mSellResourcesInterval; // in milliseconds
	DWORD mCurrentResourcesTimer;
	bool mAutoSelling;
public:
	Market();
	void Sell();
};

#endif
