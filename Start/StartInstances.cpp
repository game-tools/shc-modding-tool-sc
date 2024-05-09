#include "StartInstances.h"
#include "../Globals.h"

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
	};

	void DestroyInstances() {

	};
}