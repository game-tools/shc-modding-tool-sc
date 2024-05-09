#include "pch.h"
#include "Unit.h"
#include "Config/Instances.h"
#include "Functions/Definitions.h"

Unit::Unit()
{
	mAutoTaxesInterval = Config::pUnitsConfig->mData["autoTaxesInterval"];
	mCurrentTaxesTimer = 0;
}

void Unit::recruit(std::string numpadNumber)
{
	DWORD sthId = 0;
	for (int i = 0; i < 20; i++) {
		SetVariable((DWORD*)(modBase + 0x151d768), (int)&sthId, 2, 1, 1);
		RecruitUnit(*(int*)(modBase + 0x16275d8), Config::pUnitsConfig->mData["recruitIdNumpad" + numpadNumber], sthId);
		RecruitUnit(4, Config::pUnitsConfig->mData["recruitIdNumpad" + numpadNumber], sthId);
		Sleep(10);
	}

	printf("RECRUITED from class\n");
}