#ifndef UNIT_H
#define UNIT_H

#include <windows.h>
#include <iostream>

#include "Globals.h"

class Unit
{
public:
	DWORD mAutoTaxesInterval; // milliseconds
	DWORD mCurrentTaxesTimer;
public:
	Unit();
	void recruit(std::string numpadNumber);
};

#endif