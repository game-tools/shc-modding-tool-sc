#include "PlayerResources.h"
#include "../Config/Instances.h"
#include "../Functions/Definitions.h"

DWORD firstPlayerResourceOffset = 0xd5fcc4;
DWORD firstPlayerEnqueuedResourceOffset = 0xd5fc60;
DWORD playerSizePR = 0x39f4;

PlayerResources::PlayerResources(DWORD playerNumber) {
	mPlayerNumber = playerNumber;
	SetCurrentResourcesPointers();
	SetEnqueuedResourcesPointers();
}

void PlayerResources::SetCurrentResourcesPointers() {
	for (auto& it: Config::pResourcesConfig->m_data["resources"].items())
	{
		mCurrentResourcesMap[it.key()] = (DWORD*)(modBase + firstPlayerResourceOffset + (playerSizePR * mPlayerNumber) + ((it.value() - 2) * 0x4));
	}
}

void PlayerResources::SetEnqueuedResourcesPointers() {
	for (auto& it : Config::pResourcesConfig->m_data["resources"].items())
	{
		mEnqueuedResourcesMap[it.key()] = (DWORD*)(modBase + firstPlayerEnqueuedResourceOffset + (playerSizePR * mPlayerNumber) + ((it.value() - 2) * 0x4));
	}
}

void PlayerResources::Add(DWORD amount, DWORD id) {
	AddResource((DWORD*)(modBase + 0xb98520), mPlayerNumber + 1, id, amount);
}