#include <vector>

#include "ActionsGui.h"
#include "../Bot/BotInstances.h"
#include "../Globals.h"

void actionsGui::Render(std::map<DWORD, Player*> playerMap) noexcept {
	static ImGuiTableFlags actionsTableFlags = 0;
	actionsTableFlags |= ImGuiTableFlags_RowBg;
	actionsTableFlags |= ImGuiTableFlags_Borders;
	actionsTableFlags |= ImGuiTableFlags_SizingFixedFit;
	actionsTableFlags |= ImGuiTableFlags_ScrollX;

	const float textBaseHeight = ImGui::GetTextLineHeightWithSpacing();
	ImVec2 size = ImVec2(0.0f, textBaseHeight * 12);
	if (ImGui::BeginTable("Player Actions", 2, actionsTableFlags, size))
	{
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 200.0f);
		ImGui::TableSetupColumn("Instant Recruits", ImGuiTableColumnFlags_WidthFixed, 150.0f);
		ImGui::TableHeadersRow();

		BYTE step = 1;

		for (std::map<DWORD, Player*>::iterator it = playerMap.begin(); it != playerMap.end(); it++) {
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(it->second->mPlayerName);

			ImGui::TableSetColumnIndex(1);
			ImGui::PushID(it->first);
			ImGui::InputScalar(it->second->mPlayerName, ImGuiDataType_U8, &(it->second->mInstantRecruits), &step, NULL, "%u");
			ImGui::PopID();
		}
		ImGui::EndTable();
	}

	static float f1 = 1.0f;
	*Bot::addAttackTroopsFactor = (DWORD)(f1 * 10);
	ImGui::Text("Bot will send * factor more troops each attack");
	ImGui::SliderFloat("Additional Attack Factor", &f1, 1.0f, 10.0f, "%.1f");

	ImGui::SeparatorText("Experimental - not sure if the game will be stable all the time");
	DWORD step2 = 1;
	ImGui::PushItemWidth(300.0f);
	ImGui::Text("Max Units on map - to count how many units you can recruit just divide the value by a number of alive players and subtract 40 from the result");
	ImGui::Text("Example: 8000 / 8 (because 8 players alive) - 40 = 960");
	ImGui::InputScalar("Max Units", ImGuiDataType_U32, pMaxUnits, &step2, NULL, "%u");
	ImGui::PopItemWidth();
}