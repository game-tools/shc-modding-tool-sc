#include "windows.h"

#include "ActionsTents.h"
#include "../Globals.h"

namespace Actions {
	ActionsTents::ActionsTents() {
		mDeselectingTentAddr = modBase + 0x4612b;
		ReadVanillaCode();
		NopDeselectingTent();
	}

	ActionsTents::~ActionsTents() {
		SetVanillaCode();
	}

	void ActionsTents::ReadVanillaCode() {
		for (byte index = 0; index < 6; index++) {
			vanillaCode[index] = *(char*)(mDeselectingTentAddr + index);
		}
	}

	void ActionsTents::NopDeselectingTent() {
		char newCode[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

		DWORD oldProtect;
		VirtualProtect((LPVOID)(mDeselectingTentAddr), sizeof(newCode), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mDeselectingTentAddr), &newCode, sizeof(newCode));
		VirtualProtect((LPVOID)(mDeselectingTentAddr), sizeof(newCode), oldProtect, &oldProtect);
	}

	void ActionsTents::SetVanillaCode() {
		DWORD oldProtect;
		VirtualProtect((LPVOID)(mDeselectingTentAddr), sizeof(vanillaCode), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(mDeselectingTentAddr), &vanillaCode, sizeof(vanillaCode));
		VirtualProtect((LPVOID)(mDeselectingTentAddr), sizeof(vanillaCode), oldProtect, &oldProtect);
	}
}