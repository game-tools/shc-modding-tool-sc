#include <windows.h>

#include "ActionsGameSpeed.h"
#include "../Globals.h"

namespace Actions {
	ActionsGameSpeed::ActionsGameSpeed() {
		mSpeedUpAddr = modBase + 0xb4748;
		mSpeedDownAddr = modBase + 0xb47c2;
		ReadVanillaCode();
		InjectSpeedUp();
		InjectSpeedDown();
	}

	ActionsGameSpeed::~ActionsGameSpeed() {
		SetVanillaCode();
	}

	void ActionsGameSpeed::ReadVanillaCode() {
		for (byte index = 0; index < 32; index++) {
			vanillaSpeedUp[index] = *(char*)(mSpeedUpAddr + index);
		}

		for (byte index = 0; index < 31; index++) {
			vanillaSpeedDown[index] = *(char*)(mSpeedDownAddr + index);
		}
	}

	void ActionsGameSpeed::SetVanillaCode() {
		DWORD oldProtect;
		VirtualProtect((LPVOID)(mSpeedUpAddr), sizeof(vanillaSpeedUp), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mSpeedUpAddr), &vanillaSpeedUp, sizeof(vanillaSpeedUp));
		VirtualProtect((LPVOID)(mSpeedUpAddr), sizeof(vanillaSpeedUp), oldProtect, &oldProtect);

		VirtualProtect((LPVOID)(mSpeedDownAddr), sizeof(vanillaSpeedDown), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mSpeedDownAddr), &vanillaSpeedDown, sizeof(vanillaSpeedDown));
		VirtualProtect((LPVOID)(mSpeedDownAddr), sizeof(vanillaSpeedDown), oldProtect, &oldProtect);
	}

	void SpeedUp() {
		DWORD* pCurrentSpeed = (DWORD*)(modBase + 0x1be7dd8);

		if (*pCurrentSpeed < 100) {
			*pCurrentSpeed += 5;
		}
		else if (*pCurrentSpeed < 200) {
			*pCurrentSpeed += 10;
		}
		else if (*pCurrentSpeed < 1000) {
			*pCurrentSpeed += 100;
		}
	}

	void ActionsGameSpeed::InjectSpeedUp() {
		char newCode[32] = { 
			0x51, // push ecx
			0x50, // push eax
			0xB8, 0x00, 0x00, 0x00, 0x00, // mov eax, 0
			0xFF, 0xD0, // call eax
			0x58, // pop eax
			0x59, // pop ecx
			0xEB, 0x13, // jmp current + 0x13
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
		};

		void(*speedUpAddr)(void);
		speedUpAddr = &Actions::SpeedUp;
		memcpy(&newCode[0x3], &speedUpAddr, sizeof(uintptr_t));

		DWORD oldProtect;
		VirtualProtect((LPVOID)(mSpeedUpAddr), sizeof(newCode), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mSpeedUpAddr), &newCode, sizeof(newCode));
		VirtualProtect((LPVOID)(mSpeedUpAddr), sizeof(newCode), oldProtect, &oldProtect);
	}

	void SpeedDown() {
		DWORD* pCurrentSpeed = (DWORD*)(modBase + 0x1be7dd8);

		if (*pCurrentSpeed > 200) {
			*pCurrentSpeed -= 100;
		}
		else if (*pCurrentSpeed > 100) {
			*pCurrentSpeed -= 10;
		}
		else if (*pCurrentSpeed > 10) {
			*pCurrentSpeed -= 5;
		}
	}

	void ActionsGameSpeed::InjectSpeedDown() {
		char newCode[31] = {
			0x51, // push ecx
			0x50, // push eax
			0xB8, 0x00, 0x00, 0x00, 0x00, // mov eax, 0
			0xFF, 0xD0, // call eax
			0x58, // pop eax
			0x59, // pop ecx
			0xEB, 0x12, // jmp current + 0x12
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
		};

		void(*speedDownAddr)(void);
		speedDownAddr = &Actions::SpeedDown;
		memcpy(&newCode[0x3], &speedDownAddr, sizeof(uintptr_t));

		DWORD oldProtect;
		VirtualProtect((LPVOID)(mSpeedDownAddr), sizeof(newCode), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mSpeedDownAddr), &newCode, sizeof(newCode));
		VirtualProtect((LPVOID)(mSpeedDownAddr), sizeof(newCode), oldProtect, &oldProtect);
	}
}