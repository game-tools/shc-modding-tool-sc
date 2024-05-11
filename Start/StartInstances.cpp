#include "StartInstances.h"
#include "../Globals.h"
#include "../Config/Instances.h"

namespace Start {
	std::vector<Resources*> startResources;
	Gold* startGold;
	std::map < std::basic_string<TCHAR>, Troops* > startTroops;

	const char* startResourcesLabels[] = { "Wood", "Hop", "Stone", "Unknown1", "Iron", "Pitch", "Unknown2", "Wheat", "Bread", "Cheese", "Meat", "Apple", "Beer", "Gold (Not Used)", "Flour", "Bow", "Crossbow", "Spear", "Pike", "Mace", "Sword", "Leather Armor", "Armor", NULL};
	const char* startGoldLabels[] = { "N Huge Player Adv", "N Player Adv", "N Draw", "N AI Adv", "N Huge AI Adv", "C Huge Player Adv", "C Player Adv", "C Draw", "C AI Adv", "C Huge AI Adv", "S Huge Player Adv", "S Player Adv", "S Draw", "S AI Adv", "S Huge AI Adv", NULL};
	const char* startTroopsLabels[] = { "Archer Normal", "Crossbowman Normal", "Spearman Normal", "Pikeman Normal", "Maceman Normal", "Swordsman Normal", "Knight Normal", "Unknown1 Normal", "Engineer Normal", "Monk Normal", "Arabian Archer Normal", "Slave Normal", "Slinger Normal", "Assassin Normal", "Horse Archer Normal", "Arabian Swordsman Normal", "Fire Thrower Normal", "Unknown2 Normal", "Unknown3 Normal", "Unknown4 Normal", "Archer Crusade", "Crossbowman Crusade", "Spearman Crusade", "Pikeman Crusade", "Maceman Crusade", "Swordsman Crusade", "Knight Crusade", "Unknown1 Crusade", "Engineer Crusade", "Monk Crusade", "Arabian Archer Crusade", "Slave Crusade", "Slinger Crusade", "Assassin Crusade", "Horse Archer Crusade", "Arabian Swordsman Crusade", "Fire Thrower Crusade", "Unknown2 Crusade", "Unknown3 Crusade", "Unknown4 Crusade", "Archer Skirmish", "Crossbowman Skirmish", "Spearman Skirmish", "Pikeman Skirmish", "Maceman Skirmish", "Swordsman Skirmish", "Knight Skirmish", "Unknown1 Skirmish", "Engineer Skirmish", "Monk Skirmish", "Arabian Archer Skirmish", "Slave Skirmish", "Slinger Skirmish", "Assassin Skirmish", "Horse Archer Skirmish", "Arabian Swordsman Skirmish", "Fire Thrower Skirmish", "Unknown2 Skirmish", "Unknown3 Skirmish", "Unknown4 Skirmish",  NULL};

	void InitializeInstances() {
		startResources.push_back((Resources*)(modBase + 0x215200));
		startResources.push_back((Resources*)(modBase + 0x215264));
		startResources.push_back((Resources*)(modBase + 0x2152c8));

		startGold = (Gold*)(modBase + 0x216680);

		DWORD startTroopsSize = 0xf0;
		byte index = 0;
		for (const std::basic_string<TCHAR>& characterName : characterNames)
		{
			startTroops[characterName] = (Troops*)(modBase + 0x215448 + startTroopsSize * index);
			index++;
		}

		startTroops["Player"] = (Troops*)(modBase + 0x215448 + startTroopsSize * 17);

		LoadGoodsConfig();
		LoadTroopsConfig();
	};

	void LoadGoodsConfig() {
		if (Config::pStartGoodsConfig->mData.contains("normalResources")) {
			int i = 0;
			for (DWORD count : Config::pStartGoodsConfig->mData["normalResources"]) {
				*(DWORD*)(&startResources[0]->wood + i) = count;
				i++;
			}
		}

		if (Config::pStartGoodsConfig->mData.contains("crusadeResources")) {
			int i = 0;
			for (DWORD count : Config::pStartGoodsConfig->mData["crusadeResources"]) {
				*(DWORD*)(&startResources[1]->wood + i) = count;
				i++;
			}
		}

		if (Config::pStartGoodsConfig->mData.contains("skirmishResources")) {
			int i = 0;
			for (DWORD count : Config::pStartGoodsConfig->mData["skirmishResources"]) {
				*(DWORD*)(&startResources[2]->wood + i) = count;
				i++;
			}
		}

		if (Config::pStartGoodsConfig->mData.contains("startGold")) {
			int i = 0;
			for (DWORD count : Config::pStartGoodsConfig->mData["startGold"]) {
				*(DWORD*)(&startGold->gold1 + i) = count;
				i++;
			}
		}
	}

	void PrepareGoodsConfig() {
		Config::pStartGoodsConfig->mDataSave = {};

		DWORD start1[23];
		for (int i = 0; i < 23; i++) {
			start1[i] = *(DWORD*)(&startResources[0]->wood + i);
		}
		Config::pStartGoodsConfig->mDataSave["normalResources"] = start1;

		DWORD start2[23];
		for (int i = 0; i < 23; i++) {
			start2[i] = *(DWORD*)(&startResources[1]->wood + i);
		}
		Config::pStartGoodsConfig->mDataSave["crusaderResources"] = start2;

		DWORD start3[23];
		for (int i = 0; i < 23; i++) {
			start3[i] = *(DWORD*)(&startResources[2]->wood + i);
		}
		Config::pStartGoodsConfig->mDataSave["skirmishResources"] = start3;

		DWORD startGoldBuff[26];
		for (int i = 0; i < 26; i++) {
			startGoldBuff[i] = *(DWORD*)(&startGold->gold1 + i);
		}
		Config::pStartGoodsConfig->mDataSave["startGold"] = startGoldBuff;
	}

	void LoadTroopsConfig() {
		for (const std::basic_string<TCHAR>& characterName : characterNames)
		{
			if (Config::pStartTroopsConfig->mData.contains(characterName)) {
				int i = 0;
				for (DWORD value : Config::pStartTroopsConfig->mData[characterName]) {
					*(DWORD*)(&startTroops[characterName]->archerNormal + i) = value;
					i++;
				}
			}
		}
	}

	void PrepareTroopsConfig() {
		Config::pStartTroopsConfig->mDataSave = {};

		for (const std::basic_string<TCHAR>& characterName : characterNames) {
			DWORD values[60];
			for (int i = 0; i < 60; i++) {
				values[i] = *(DWORD*)(&startTroops[characterName]->archerNormal + i);
			}
			Config::pStartTroopsConfig->mDataSave[characterName] = values;
		}
	}
}