#pragma once

#include <windows.h>

namespace Actions {
	void SpeedUp();
	void SpeedDown();

	class ActionsGameSpeed {
	public:
		DWORD mSpeedUpAddr;
		DWORD mSpeedDownAddr;
		char vanillaSpeedUp[32];
		char vanillaSpeedDown[31];
	public:
		ActionsGameSpeed();
		~ActionsGameSpeed();
		void ReadVanillaCode();
		void SetVanillaCode();
		void InjectSpeedUp();
		void InjectSpeedDown();
	};
}