#include <map>

#include "BotSettingsGui.h"
#include "../Bot/BotInstances.h"
#include "../Bot/Character.h"
#include "../Config/Instances.h"

#include "../imgui/imgui.h"

std::basic_string<TCHAR> currentBotDifficulty = "Current: Normal";

void botSettingsGui::Render() noexcept {
	static ImGuiTableFlags botSettingsTableFlags = 0;
	botSettingsTableFlags |= ImGuiTableFlags_RowBg;
	botSettingsTableFlags |= ImGuiTableFlags_Borders;
	botSettingsTableFlags |= ImGuiTableFlags_SizingFixedFit;
	botSettingsTableFlags |= ImGuiTableFlags_ScrollX;

	const float textBaseHeight = ImGui::GetTextLineHeightWithSpacing();;
	ImVec2 size = ImVec2(0.0f, textBaseHeight * 24);
	if (ImGui::BeginTable("Bot Settings", 170, botSettingsTableFlags, size))
	{
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 150.0f);
		int i = 0;
		while (Bot::properties[i] != NULL) {
			ImGui::TableSetupColumn(Bot::properties[i], ImGuiTableColumnFlags_WidthFixed, 150.0f);
			i++;
		}
		ImGui::TableHeadersRow();

		DWORD step = 1;

		for (std::map<std::basic_string<TCHAR>, Bot::Character*>::iterator it = Bot::characters.begin(); it != Bot::characters.end(); it++) {
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(it->first.c_str());

			int i2 = 0;
			while (Bot::properties[i2] != NULL) {
				ImGui::TableSetColumnIndex(i2+1);
				ImGui::PushID(i2);
				ImGui::InputScalar(it->first.c_str(), ImGuiDataType_U32, &(it->second->mWallDecoration) + i2, &step, NULL, "%u");
				ImGui::PopID();
				i2++;
			}
		}
		ImGui::EndTable();
	}

	ImGui::SeparatorText("Quick Actions");
	if (ImGui::Button("Easy Bots")) {
		ModifyBots(2.0f, 0.5f);
		currentBotDifficulty = "Current: Easy";
	}
	ImGui::SameLine();
	if (ImGui::Button("Normal Bots")) {
		ModifyBots(1.0f, 1.0f);
		currentBotDifficulty = "Current: Normal";
	}
	ImGui::SameLine();
	if (ImGui::Button("Hard Bots")) {
		ModifyBots(0.5f, 2.0f);
		currentBotDifficulty = "Current: Hard";
	}
	ImGui::SameLine();
	if (ImGui::Button("Impossible Bots")) {
		ModifyBots(0.0f, 3.0f);
		currentBotDifficulty = "Current: Impossible";
	}
	ImGui::SameLine();
	ImGui::Text(currentBotDifficulty.c_str());

	ImGui::SeparatorText("Config");

	static int selected = -1;
	static char buf[64] = "";

	ImGui::Text("Default config:");
	ImGui::SameLine();
	ImGui::Text(Config::pBotSettingsConfig->mDefaultName.c_str());
	ImGui::SameLine();

	if (ImGui::Button("Load")) {
		Config::pBotSettingsConfig->Load(Config::pBotSettingsConfig->savedConfigNames[selected]);
		Bot::LoadConfig();
	}

	if (ImGui::Button("Save")) {
		Bot::PrepareConfig();
		Config::pBotSettingsConfig->Save((std::string)buf);
	}

	ImGui::SameLine();

	if (ImGui::Button("Save as Default")) {
		Bot::PrepareConfig();
		Config::pBotSettingsConfig->SaveDefault((std::string)buf);
	}

	ImGui::SameLine();

	if (ImGui::Button("Delete Selected")) {
		Config::pBotSettingsConfig->Delete(Config::pBotSettingsConfig->savedConfigNames[selected]);
	}

	ImGui::InputText("Save file name", buf, 64, ImGuiInputTextFlags_CharsNoBlank);

	byte n = 0;
	for (std::basic_string<TCHAR> configFileName : Config::pBotSettingsConfig->savedConfigNames) {
		if (ImGui::Selectable(configFileName.c_str(), selected == n))
			selected = n;
		n++;
	}
}

void botSettingsGui::ModifyBots(float coeff1, float coeff2) {
	for (std::map<std::basic_string<TCHAR>, Bot::Character*>::iterator it = Bot::characters.begin(); it != Bot::characters.end(); it++) {
		it->second->mBuildInterval = it->second->mBuildInterval * coeff1;
		it->second->mResourceRebuildDelay = it->second->mResourceRebuildDelay * coeff1;
		it->second->mRecruitInterval = it->second->mRecruitInterval * coeff1;
		it->second->mRecruitIntervalWeak = it->second->mRecruitIntervalWeak * coeff1;
		it->second->mRecruitIntervalStrong = it->second->mRecruitIntervalStrong * coeff1;
		it->second->mRaidRetargetDelay = it->second->mRaidRetargetDelay * coeff1;
		
		it->second->mDefWallPatrolGroups = it->second->mDefWallPatrolGroups * coeff2;
		it->second->mDefSiegeEngineBuildDelay = it->second->mDefSiegeEngineBuildDelay * coeff2;
		it->second->mDefDiggingUnitMax = it->second->mDefDiggingUnitMax * coeff2;
		it->second->mDefTotal = it->second->mDefTotal * coeff2;
		it->second->mOuterPatrolGroupsCount = it->second->mOuterPatrolGroupsCount * coeff2;
		it->second->mDefWalls = it->second->mDefWalls * coeff2;
		it->second->mAttMaxEngineers = it->second->mAttMaxEngineers * coeff2;
		it->second->mAttDiggingUnitMax = it->second->mAttDiggingUnitMax * coeff2;
		it->second->mAttUnitVanguardMax = it->second->mAttUnitVanguardMax * coeff2;
		it->second->mAttMaxAssassins = it->second->mAttMaxAssassins * coeff2;
		it->second->mAttMaxLaddermen = it->second->mAttMaxLaddermen * coeff2;
		it->second->mAttMaxTunnelers = it->second->mAttMaxTunnelers * coeff2;
		it->second->mAttUnitPatrolMax = it->second->mAttUnitPatrolMax * coeff2;
		it->second->mAttUnitBackupMax = it->second->mAttUnitBackupMax * coeff2;
		it->second->mAttUnitEngageMax = it->second->mAttUnitEngageMax * coeff2;
		it->second->mAttUnitSiegeDefMax = it->second->mAttUnitSiegeDefMax * coeff2;
		it->second->mAttMaxDefault = it->second->mAttMaxDefault * coeff2;
	}
}