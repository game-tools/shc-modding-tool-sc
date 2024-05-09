#ifndef UNIT_H
#define UNIT_H

#include <windows.h>
#include <iostream>

#include "Globals.h"

class Unit
{
public:
	Unit();
	void recruit(std::string numpadNumber);

	void setMCurrentTaxesTimer(DWORD currentTaxesTimer)
	{
		mCurrentTaxesTimer = currentTaxesTimer;
	}

	DWORD getMAutoTaxesInterval() const { return mAutoTaxesInterval; }
	DWORD getMCurrentTaxesTimer() const { return mCurrentTaxesTimer; }
private:
	DWORD mAutoTaxesInterval; // milliseconds
	DWORD mCurrentTaxesTimer;
};

#endif