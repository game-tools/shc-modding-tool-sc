#include "PlayerUnits.h"
#include "../Config/Instances.h"
#include "../Functions/Definitions.h"

DWORD firstPlayerEuropUnitOffset = 0xd618a4;
DWORD playerSizePU = 0x39f4;

PlayerUnits::PlayerUnits(DWORD playerNumber) {
	mPlayerNumber = playerNumber;
	setCurrentUnitsPointers();
}

void PlayerUnits::setCurrentUnitsPointers() {
	for (auto& it : Config::pUnitsConfig->mData["europeanUnitOrder"].items()) {
		mCurrentEuropeanUnitsMap[it.key()] = (DWORD*)(modBase + firstPlayerEuropUnitOffset + (playerSizePU * mPlayerNumber) + (it.value() * 0x4));
	}

	for (auto& it : Config::pUnitsConfig->mData["arabianUnitOrder"].items()) {
		mCurrentArabianUnitsMap[it.key()] = (DWORD*)(modBase + firstPlayerEuropUnitOffset); // fake count
	}
}

void PlayerUnits::Recruit(DWORD unitId, DWORD count) {
	DWORD sthId = 0;
	for (int i = 0; i < count; i++) {
		SetVariable((DWORD*)(modBase + 0x151d768), (int)&sthId, 2, 1, 1);
		RecruitUnit(mPlayerNumber + 1, unitId, sthId);
		Sleep(10);
	}
}