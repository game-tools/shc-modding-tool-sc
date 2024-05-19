#include <windows.h>

#include "ActionsGates.h"
#include "../Globals.h"

namespace Actions {
	ActionsGates::ActionsGates() {
		mGateDistanceAddr = modBase + 0x22ace;
		mGateTimeAddr = modBase + 0x22b3c;
		ReadVanillaCode();
		InjectGateDistance();
		InjectGateTime();
	}

	ActionsGates::~ActionsGates() {
		SetVanillaCode();
	}

	void ActionsGates::ReadVanillaCode() {
		for (byte index = 0; index < 4; index++) {
			vanillaGateDistance[index] = *(char*)(mGateDistanceAddr + index);
		}

		for (byte index = 0; index < 2; index++) {
			vanillaGateTime[index] = *(char*)(mGateTimeAddr + index);
		}
	}

	void ActionsGates::SetVanillaCode() {
		DWORD oldProtect;
		VirtualProtect((LPVOID)(mGateDistanceAddr), sizeof(vanillaGateDistance), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mGateDistanceAddr), &vanillaGateDistance, sizeof(vanillaGateDistance));
		VirtualProtect((LPVOID)(mGateDistanceAddr), sizeof(vanillaGateDistance), oldProtect, &oldProtect);

		VirtualProtect((LPVOID)(mGateTimeAddr), sizeof(vanillaGateTime), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mGateTimeAddr), &vanillaGateTime, sizeof(vanillaGateTime));
		VirtualProtect((LPVOID)(mGateTimeAddr), sizeof(vanillaGateTime), oldProtect, &oldProtect);
	}

	void ActionsGates::InjectGateDistance() {
		char newCode[4] = { 0x8C, 0x00, 0x00, 0x00 };

		DWORD oldProtect;
		VirtualProtect((LPVOID)(mGateDistanceAddr), sizeof(newCode), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mGateDistanceAddr), &newCode, sizeof(newCode));
		VirtualProtect((LPVOID)(mGateDistanceAddr), sizeof(newCode), oldProtect, &oldProtect);
	}

	void ActionsGates::InjectGateTime() {
		char newCode[2] = { 0x64, 0x00 };

		DWORD oldProtect;
		VirtualProtect((LPVOID)(mGateTimeAddr), sizeof(newCode), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mGateTimeAddr), &newCode, sizeof(newCode));
		VirtualProtect((LPVOID)(mGateTimeAddr), sizeof(newCode), oldProtect, &oldProtect);
	}
}