#include "BotInstances.h"
#include "../Config/Instances.h"

namespace Bot {
	DWORD* addAttackTroopsFactor;
	std::map<std::basic_string<TCHAR>, Character*> characters;

	const char* properties[] = { "WallDecoration", "Unknown001", "Unknown002", "Unknown003", "Unknown004", "Unknown005", "CriticalPopularity", "LowestPopularity", "HighestPopularity", "TaxesMin", "TaxesMax", "Unknown011", "Farm1", "Farm2", "Farm3", "Farm4", "Farm5", "Farm6", "Farm7", "Farm8", "PopulationPerFarm", "PopulationPerWoodcutter", "PopulationPerQuarry", "PopulationPerIronmine", "PopulationPerPitchrig", "MaxQuarries", "MaxIronmines", "MaxWoodcutters", "MaxPitchrigs", "MaxFarms", "BuildInterval", "ResourceRebuildDelay", "MaxFood", "MinimumApples", "MinimumCheese", "MinimumBread", "MinimumWheat", "MinimumHop", "TradeAmountFood", "TradeAmountEquipment", "AIRequestDelay", "MinimumGoodsRequiredAfterTrade", "DoubleRationsFoodThreshold", "MaxWood", "MaxStone", "MaxResourceOther", "MaxEquipment", "MaxBeer", "MaxResourceVariance", "RecruitGoldThreshold", "BlacksmithSetting", "FletcherSetting", "PoleturnerSetting", "SellResource01", "SellResource02", "SellResource03", "SellResource04", "SellResource05", "SellResource06", "SellResource07", "SellResource08", "SellResource09", "SellResource10", "SellResource11", "SellResource12", "SellResource13", "SellResource14", "SellResource15", "DefWallPatrolRallyTime", "DefWallPatrolGroups", "DefSiegeEngineGoldThreshold", "DefSiegeEngineBuildDelay", "Unknown072", "Unknown073", "RecruitProbDefDefault", "RecruitProbDefWeak", "RecruitProbDefStrong", "RecruitProbRaidDefault", "RecruitProbRaidWeak", "RecruitProbRaidStrong", "RecruitProbAttackDefault", "RecruitProbAttackWeak", "RecruitProbAttackStrong", "SortieUnitRangedMin", "SortieUnitRanged", "SortieUnitMeleeMin", "SortieUnitMelee", "DefDiggingUnitMax", "DefDiggingUnit", "RecruitInterval", "RecruitIntervalWeak", "RecruitIntervalStrong", "DefTotal", "OuterPatrolGroupsCount", "OuterPatrolGroupsMove", "OuterPatrolRallyDelay", "DefWalls", "DefUnit1", "DefUnit2", "DefUnit3", "DefUnit4", "DefUnit5", "DefUnit6", "DefUnit7", "DefUnit8", "RaidUnitsBase", "RaidUnitsRandom", "RaidUnit1", "RaidUnit2", "RaidUnit3", "RaidUnit4", "RaidUnit5", "RaidUnit6", "RaidUnit7", "RaidUnit8", "HarassingSiegeEngine1", "HarassingSiegeEngine2", "HarassingSiegeEngine3", "HarassingSiegeEngine4", "HarassingSiegeEngine5", "HarassingSiegeEngine6", "HarassingSiegeEngine7", "HarassingSiegeEngine8", "HarassingSiegeEnginesMax", "RaidRetargetDelay", "AttForceBase", "AttForceRandom", "AttForceSupportAllyThreshold", "AttForceRallyPercentage", "Unknown129", "AttAssaultDelay", "AttUnitPatrolRecommandDelay", "Unknown132", "SiegeEngine1", "SiegeEngine2", "SiegeEngine3", "SiegeEngine4", "SiegeEngine5", "SiegeEngine6", "SiegeEngine7", "SiegeEngine8", "CowThrowInterval", "Unknown142", "AttMaxEngineers", "AttDiggingUnit", "AttDiggingUnitMax", "AttUnitVanguard", "AttUnitVanguardMax", "AttMaxAssassins", "AttMaxLaddermen", "AttMaxTunnelers", "AttUnitPatrol", "AttUnitPatrolMax", "AttUnitPatrolGroupsCount", "AttUnitBackup", "AttUnitBackupMax", "AttUnitBackupGroupsCount", "AttUnitEngage", "AttUnitEngageMax", "AttUnitSiegeDef", "AttUnitSiegeDefMax", "AttUnitSiegeDefGroupsCount", "AttUnitMain1", "AttUnitMain2", "AttUnitMain3", "AttUnitMain4", "AttMaxDefault", "AttMainGroupsCount", "TargetChoice", NULL };

	DWORD firstBotCharacterAddress = modBase + 0x1ffcb8c;
	DWORD botCharacterSize = 0x2a4;

	void InitializeInstances() {
		addAttackTroopsFactor = new DWORD(10);

		byte index = 0;
		for (const std::basic_string<TCHAR> &characterName : characterNames)
		{
			characters[characterName] = (Character*)(modBase + firstBotCharacterAddress + botCharacterSize * index);
			index++;
		}

		InjectAddAttackTroopsCode();
		LoadConfig();
	}

	void DeleteInstances() {
		SetVanillaCode();
		delete addAttackTroopsFactor;
	}

	void InjectAddAttackTroopsCode() {
		DWORD addAttackCodeBeginning = modBase + 0xcde7c;

		char newCode[124] = {
			0x83, 0xE8, 0x1,  // sub eax,01 = > ai_index
			0x69, 0xC0, 0xA4, 0x02, 0x00, 0x00, // imul eax, 2A4 { 676 } = > ai_offset
			0x8B, 0x84, 0x28, 0xF4, 0x01, 0x00, 0x00, // mov eax,[eax + ebp + 0x1f4] = > initial attack troops
			0x8B, 0x8E, 0x1C, 0xF7, 0x15, 0x01,  // mov ecx,[esi + 0115f71c] = > attack number
			0xF7, 0xE9,  // imul ecx = > attack number * initial attack troops
			0x69, 0xC0, 0x00, 0x00, 0x00, 0x00, // imul eax, addAttackTroopsFactor
			0xB9, 0x0A, 0x00, 0x00, 0x00,  // mov ecx, 0A { 10 }
			0xF7, 0xF9,  // idiv ecx
			0x83, 0xC0, 0x5,  // add eax, 5 = > because in vanilla, attackNum was already 1 for first attack
			0x89, 0x86, 0x98, 0xF6, 0x15, 0x01, // mov [esi + 0115F698],eax = > addtroops = result
			0xFF, 0x86, 0x1C, 0xF7, 0x15, 0x01, // inc [esi + 0115F71C] = > attack number++
			0xEB, 0x46,  // jmp over nops
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
			0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
		};

		memcpy(&newCode[0x1a], &addAttackTroopsFactor, sizeof(DWORD));

		DWORD oldProtect;
		VirtualProtect((LPVOID)(addAttackCodeBeginning), sizeof(newCode), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(addAttackCodeBeginning), &newCode, sizeof(newCode));
		VirtualProtect((LPVOID)(addAttackCodeBeginning), sizeof(newCode), oldProtect, &oldProtect);
	}

	void SetVanillaCode() {
		DWORD addAttackCodeBeginning = modBase + 0xcde7c;

		char vanillaCode[124] = { 0x53, 0x57, 0x8D, 0x78, 0xFF, 0x0F, 0xBF, 0x05, 0xC2, 0x79, 0xA2, 0x01, 0x99, 0xB9, 0x64, 0x00, 0x00, 0x00, 0xF7, 0xF9, 0xB9, 0xC0, 0x79, 0xA2, 0x01, 0x8B, 0xDA, 0xE8, 0x34, 0xC9, 0xF9, 0xFF, 0x69, 0xFF, 0xA4, 0x02, 0x00, 0x00, 0x8B, 0xBC, 0x2F, 0xF8, 0x01, 0x00, 0x00, 0x83, 0x86, 0x1C, 0xF7, 0x15, 0x01, 0x01, 0x0F, 0xAF, 0xFB, 0xB8, 0x1F, 0x85, 0xEB, 0x51, 0xF7, 0xEF, 0xC1, 0xFA, 0x05, 0x8B, 0xC2, 0xC1, 0xE8, 0x1F, 0x03, 0xC2, 0x81, 0xBE, 0x04, 0xC3, 0x15, 0x01, 0x10, 0x27, 0x00, 0x00, 0x5F, 0x89, 0x86, 0x98, 0xF6, 0x15, 0x01, 0x8B, 0x86, 0x1C, 0xF7, 0x15, 0x01, 0x5B, 0x7E, 0x11, 0x8D, 0x0C, 0xC5, 0x00, 0x00, 0x00, 0x00, 0x2B, 0xC8, 0x01, 0x8E, 0x98, 0xF6, 0x15, 0x01, 0xEB, 0x09, 0x8D, 0x14, 0x80, 0x01, 0x96, 0x98, 0xF6, 0x15, 0x01 };
		DWORD oldProtect;
		VirtualProtect((LPVOID)(addAttackCodeBeginning), sizeof(vanillaCode), PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(addAttackCodeBeginning), &vanillaCode, sizeof(vanillaCode));
		VirtualProtect((LPVOID)(addAttackCodeBeginning), sizeof(vanillaCode), oldProtect, &oldProtect);
	}

	void LoadConfig() {
		for (const std::basic_string<TCHAR>& characterName : characterNames)
		{
			if (Config::pBotSettingsConfig->mData.contains(characterName)) {
				byte index = 0;
				for (DWORD value : Config::pBotSettingsConfig->mData[characterName]) {
					*(DWORD*)(&characters[characterName]->mWallDecoration + index) = value;
					index++;
				}
			}
		}
	}

	void PrepareConfig() {
		Config::pBotSettingsConfig->mDataSave = {};

		for (const std::basic_string<TCHAR>& characterName : characterNames) {
			DWORD values[169];
			for (int i = 0; i < 169; i++) {
				values[i] = *(DWORD*)(&characters[characterName]->mWallDecoration + i);
			}
			Config::pBotSettingsConfig->mDataSave[characterName] = values;
		}
	}
}