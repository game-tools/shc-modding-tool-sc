#include "BotInstances.h"
#include "../Config/Instances.h"

namespace Bot {
	std::map<std::basic_string<TCHAR>, Character*> characters;

	const char* properties[] = { "WallDecoration", "Unknown001", "Unknown002", "Unknown003", "Unknown004", "Unknown005", "CriticalPopularity", "LowestPopularity", "HighestPopularity", "TaxesMin", "TaxesMax", "Unknown011", "Farm1", "Farm2", "Farm3", "Farm4", "Farm5", "Farm6", "Farm7", "Farm8", "PopulationPerFarm", "PopulationPerWoodcutter", "PopulationPerQuarry", "PopulationPerIronmine", "PopulationPerPitchrig", "MaxQuarries", "MaxIronmines", "MaxWoodcutters", "MaxPitchrigs", "MaxFarms", "BuildInterval", "ResourceRebuildDelay", "MaxFood", "MinimumApples", "MinimumCheese", "MinimumBread", "MinimumWheat", "MinimumHop", "TradeAmountFood", "TradeAmountEquipment", "AIRequestDelay", "MinimumGoodsRequiredAfterTrade", "DoubleRationsFoodThreshold", "MaxWood", "MaxStone", "MaxResourceOther", "MaxEquipment", "MaxBeer", "MaxResourceVariance", "RecruitGoldThreshold", "BlacksmithSetting", "FletcherSetting", "PoleturnerSetting", "SellResource01", "SellResource02", "SellResource03", "SellResource04", "SellResource05", "SellResource06", "SellResource07", "SellResource08", "SellResource09", "SellResource10", "SellResource11", "SellResource12", "SellResource13", "SellResource14", "SellResource15", "DefWallPatrolRallyTime", "DefWallPatrolGroups", "DefSiegeEngineGoldThreshold", "DefSiegeEngineBuildDelay", "Unknown072", "Unknown073", "RecruitProbDefDefault", "RecruitProbDefWeak", "RecruitProbDefStrong", "RecruitProbRaidDefault", "RecruitProbRaidWeak", "RecruitProbRaidStrong", "RecruitProbAttackDefault", "RecruitProbAttackWeak", "RecruitProbAttackStrong", "SortieUnitRangedMin", "SortieUnitRanged", "SortieUnitMeleeMin", "SortieUnitMelee", "DefDiggingUnitMax", "DefDiggingUnit", "RecruitInterval", "RecruitIntervalWeak", "RecruitIntervalStrong", "DefTotal", "OuterPatrolGroupsCount", "OuterPatrolGroupsMove", "OuterPatrolRallyDelay", "DefWalls", "DefUnit1", "DefUnit2", "DefUnit3", "DefUnit4", "DefUnit5", "DefUnit6", "DefUnit7", "DefUnit8", "RaidUnitsBase", "RaidUnitsRandom", "RaidUnit1", "RaidUnit2", "RaidUnit3", "RaidUnit4", "RaidUnit5", "RaidUnit6", "RaidUnit7", "RaidUnit8", "HarassingSiegeEngine1", "HarassingSiegeEngine2", "HarassingSiegeEngine3", "HarassingSiegeEngine4", "HarassingSiegeEngine5", "HarassingSiegeEngine6", "HarassingSiegeEngine7", "HarassingSiegeEngine8", "HarassingSiegeEnginesMax", "RaidRetargetDelay", "AttForceBase", "AttForceRandom", "AttForceSupportAllyThreshold", "AttForceRallyPercentage", "Unknown129", "AttAssaultDelay", "AttUnitPatrolRecommandDelay", "Unknown132", "SiegeEngine1", "SiegeEngine2", "SiegeEngine3", "SiegeEngine4", "SiegeEngine5", "SiegeEngine6", "SiegeEngine7", "SiegeEngine8", "CowThrowInterval", "Unknown142", "AttMaxEngineers", "AttDiggingUnit", "AttDiggingUnitMax", "AttUnitVanguard", "AttUnitVanguardMax", "AttMaxAssassins", "AttMaxLaddermen", "AttMaxTunnelers", "AttUnitPatrol", "AttUnitPatrolMax", "AttUnitPatrolGroupsCount", "AttUnitBackup", "AttUnitBackupMax", "AttUnitBackupGroupsCount", "AttUnitEngage", "AttUnitEngageMax", "AttUnitSiegeDef", "AttUnitSiegeDefMax", "AttUnitSiegeDefGroupsCount", "AttUnitMain1", "AttUnitMain2", "AttUnitMain3", "AttUnitMain4", "AttMaxDefault", "AttMainGroupsCount", "TargetChoice", NULL };

	DWORD firstBotCharacterAddress = modBase + 0x1ffcb8c;
	DWORD botCharacterSize = 0x2a4;

	void InitializeInstances() {
		byte index = 0;
		for (const std::basic_string<TCHAR> &characterName : characterNames)
		{
			characters[characterName] = (Character*)(modBase + firstBotCharacterAddress + botCharacterSize * index);
			index++;
		}

		LoadConfig();
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