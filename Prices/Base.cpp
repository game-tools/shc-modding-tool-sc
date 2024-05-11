#include "Base.h"
#include "../Globals.h"
#include "../Config/Instances.h"

DWORD Prices::ArabCost(DWORD unitId) {
	DWORD cost = 100000;
	switch (unitId) {
	case 0x46: {
		cost = prices->arabian->arabianArcher;
		break;
	}
	case 0x47: {
		cost = prices->arabian->slave;
		break;
	}
	case 0x48: {
		cost = prices->arabian->slinger;
		break;
	}
	case 0x49: {
		cost = prices->arabian->assassin;
		break;
	}
	case 0x4a: {
		cost = prices->arabian->horseArcher;
		break;
	}
	case 0x4b: {
		cost = prices->arabian->arabianSwordsman;
		break;
	}
	case 0x4c: {
		cost = prices->arabian->fireThrower;
		break;
	}
	}

	return cost;
}

Prices::Base::Base() {
	arabian = (Arabian*)(modBase + 0x6b913c);
	european = (European*)(modBase + 0x6b9114);
	resource = (Resource*)(modBase + 0xd7cfe4);
	globalResource = (GlobalResource*)(modBase + 0x2171c8);
	InjectArabCost();
	LoadConfig();
}

void Prices::Base::InjectArabCost() {
	DWORD arabCostBeginning = modBase + 0x12ec46;

	char newCode[72] = {
		0x51, // push ecx
		0x50, // push eax
		0xB8, 0x00, 0x00, 0x00, 0x00, // mov eax, 0
		0xFF, 0xD0, // call eax
		0x3D, 0xA0, 0x86, 0x01, 0x00, // cmp eax, 0x186a0
		0x74, 0x31, // je "Stronghold Crusader.exe"+0x12ec87
		0x89, 0xC5, // mov ebp, eax
		0x58, // pop eax
		0x59, // pop ecx
		0xEB, 0x32, // jmp "Stronghold Crusader.exe"+0x12ec8e
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
		0x90, 0x90, 0x90,
		0x58, // pop eax
		0x59, // pop ecx
		0xE9, 0x00, 0x00, 0x00, 0x00 // jmp "Stronghold Crusader.exe"+0x12edb9
	};

	DWORD (*arabCostAddr)(DWORD);
	arabCostAddr = &Prices::ArabCost;
	memcpy(&newCode[0x3], &arabCostAddr, sizeof(uintptr_t));

	int jmpOffset = 0xffffffff - (arabCostBeginning + 0x48) + modBase + 0x12edb9 + 0x1;

	memcpy(&newCode[0x44], &jmpOffset, sizeof(uintptr_t));

	DWORD oldProtect;
	VirtualProtect((LPVOID)(modBase + 0x12ec46), sizeof(newCode), PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)(modBase + 0x12ec46), &newCode, sizeof(newCode));
	VirtualProtect((LPVOID)(modBase + 0x12ec46), sizeof(newCode), oldProtect, &oldProtect);
}

void Prices::Base::SetVanillaCode() {
	char vanillaCode[72] = {0x83, 0xF8, 0x46, 0x75, 0x05, 0x8D, 0x68, 0x05, 0xEB, 0x3E, 0x83, 0xF8, 0x47, 0x75, 0x05, 0x8D, 0x68, 0xBE, 0xEB, 0x34, 0x83, 0xF8, 0x48, 0x75, 0x05, 0x8D, 0x68, 0xC4, 0xEB, 0x2A, 0x83, 0xF8, 0x49, 0x75, 0x05, 0x8D, 0x68, 0xF3, 0xEB, 0x20, 0x83, 0xF8, 0x4A, 0x75, 0x05, 0x8D, 0x68, 0x06, 0xEB, 0x16, 0x83, 0xF8, 0x4B, 0x75, 0x05, 0x8D, 0x68, 0x05, 0xEB, 0x0C, 0x83, 0xF8, 0x4C, 0x0F, 0x85, 0x2E, 0x01, 0x00, 0x00, 0x8D, 0x68, 0x18};
	DWORD oldProtect;
	VirtualProtect((LPVOID)(modBase + 0x12ec46), sizeof(vanillaCode), PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)(modBase + 0x12ec46), &vanillaCode, sizeof(vanillaCode));
	VirtualProtect((LPVOID)(modBase + 0x12ec46), sizeof(vanillaCode), oldProtect, &oldProtect);
}

void Prices::Base::LoadConfig() {
	if (Config::pPricesConfig->mData.contains("european")) {
		int i = 0;
		for (DWORD price : Config::pPricesConfig->mData["european"]) {
			*(DWORD*)(&european->archer + i) = price;
			i++;
		}
	}

	if (Config::pPricesConfig->mData.contains("arabian")) {
		int i = 0;
		for (DWORD price : Config::pPricesConfig->mData["arabian"]) {
			*(DWORD*)(&arabian->arabianArcher + i) = price;
			i++;
		}
	}

	if (Config::pPricesConfig->mData.contains("resources")) {
		int i = 0;
		for (DWORD price : Config::pPricesConfig->mData["resources"]) {
			*(DWORD*)(&resource->woodBuy + i) = price;
			i++;
		}
	}

	if (Config::pPricesConfig->mData.contains("globalResources")) {
		int i = 0;
		for (DWORD price : Config::pPricesConfig->mData["globalResources"]) {
			*(DWORD*)(&globalResource->woodBuy + i) = price;
			i++;
		}
	}
}

void Prices::Base::PrepareConfig() {
	Config::pPricesConfig->mDataSave = {};

	DWORD europCost[7];
	for (int i = 0; i < 7; i++) {
		europCost[i] = *(DWORD*)(&european->archer + i);
	}
	Config::pPricesConfig->mDataSave["european"] = europCost;

	DWORD arabCost[7];
	for (int i = 0; i < 7; i++) {
		arabCost[i] = *(DWORD*)(&arabian->arabianArcher + i);
	}
	Config::pPricesConfig->mDataSave["arabian"] = arabCost;

	DWORD resourceCost[46];
	for (int i = 0; i < 46; i++) {
		resourceCost[i] = *(DWORD*)(&resource->woodBuy + i);
	}
	Config::pPricesConfig->mDataSave["resources"] = resourceCost;

	DWORD globalResourceCost[49];
	for (int i = 0; i < 49; i++) {
		globalResourceCost[i] = *(DWORD*)(&globalResource->woodBuy + i);
	}
	Config::pPricesConfig->mDataSave["globalResources"] = globalResourceCost;
}