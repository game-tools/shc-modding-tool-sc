#include <vector>

#include "ActionsGui.h"

void actionsGui::Render(std::map<DWORD, Player*> playerMap) noexcept {
	static ImGuiTableFlags actionsTableFlags = 0;
	actionsTableFlags |= ImGuiTableFlags_RowBg;
	actionsTableFlags |= ImGuiTableFlags_Borders;
	actionsTableFlags |= ImGuiTableFlags_SizingFixedFit;
	actionsTableFlags |= ImGuiTableFlags_ScrollX;

	if (ImGui::BeginTable("Player Actions", 2, actionsTableFlags))
	{
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 150.0f);
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
}