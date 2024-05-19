#pragma once

#include <windows.h>

namespace Actions {
	class ActionsGates {
	public:
		DWORD mGateDistanceAddr;
		DWORD mGateTimeAddr;
		char vanillaGateDistance[4];
		char vanillaGateTime[2];
	public:
		ActionsGates();
		~ActionsGates();
		void ReadVanillaCode();
		void SetVanillaCode();
		void InjectGateDistance();
		void InjectGateTime();
	};
}