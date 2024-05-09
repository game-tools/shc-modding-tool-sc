#include "StartTroopsGui.h"
#include "../Start/StartInstances.h"

#include "../imgui/imgui.h"

void startTroopsGui::Render() noexcept {
	static ImGuiTableFlags startTroopsTableFlags = 0;
	startTroopsTableFlags |= ImGuiTableFlags_RowBg;
	startTroopsTableFlags |= ImGuiTableFlags_Borders;
	startTroopsTableFlags |= ImGuiTableFlags_SizingFixedFit;
	startTroopsTableFlags |= ImGuiTableFlags_ScrollX;

	const float textBaseHeight = ImGui::GetTextLineHeightWithSpacing();;
	ImVec2 size = ImVec2(0.0f, textBaseHeight * 25);
	if (ImGui::BeginTable("Start Troops", 61, startTroopsTableFlags, size))
	{
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 150.0f);
		int i = 0;
		while (Start::startTroopsLabels[i] != NULL) {
			ImGui::TableSetupColumn(Start::startTroopsLabels[i], ImGuiTableColumnFlags_WidthFixed, 150.0f);
			i++;
		}
		ImGui::TableHeadersRow();

		DWORD step = 1;

		for (std::map<std::basic_string<TCHAR>, Start::Troops*>::iterator it = Start::startTroops.begin(); it != Start::startTroops.end(); it++) {
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(it->first.c_str());

			int i2 = 0;
			while (Start::startTroopsLabels[i2] != NULL) {
				ImGui::TableSetColumnIndex(i2 + 1);
				ImGui::PushID(i2);
				ImGui::InputScalar(it->first.c_str(), ImGuiDataType_U32, &(it->second->archerNormal) + i2, &step, NULL, "%u");
				ImGui::PopID();
				i2++;
			}
		}
		ImGui::EndTable();
	}
}